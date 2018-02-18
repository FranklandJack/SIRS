#include "SIRSArray.hpp"
#include "getTimeStamp.hpp"
#include "makeDirectory.hpp"
#include "SIRSInputParameters.hpp"
#include "DataArray.hpp"
#include "SIRSResults.hpp"
#include "Timer.hpp"
#include <random>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>
#include <string>

int main(int argc, char const *argv[])
{
/*************************************************************************************************************************
************************************************* Preparations **********************************************************
*************************************************************************************************************************/

    // Start the clock so execution time can be calculated. 
    Timer timer;

    // Seed the pseudo random number generator using the system clock.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a generator that can be fed to any distribution to produce pseudo random numbers according to that distribution. 
    std::default_random_engine generator(seed);

    // Input parameters.
    int rowCount;
    int colCount;
    double probSI;
    double probIR;
    double probRS;
    int burnPeriod;
    int totalSweeps;
    int measurementInterval;
    std::string outputName;

    // Set up optional command line arguments.
    boost::program_options::options_description desc("Options for SIRS simulation");

    // Add all optional command line arguments.
    desc.add_options()
        
        ("column-count,c", boost::program_options::value<int>(&rowCount)->default_value(50), "The number of rows in the lattice.")
        ("row-count,r", boost::program_options::value<int>(&colCount)->default_value(50), "The number of columns in the lattice.")
        ("prob-SI,p", boost::program_options::value<double>(&probSI)->default_value(1.0), "The probability of going from susceptible to infected upon contact.")
        ("prob-IR,q", boost::program_options::value<double>(&probIR)->default_value(1.0), "The probability of going from infected to recovered.")
        ("prob-RS,g", boost::program_options::value<double>(&probRS)->default_value(1.0), "The probability of going from recovered to susceptible.")
        ("burn-period,b", boost::program_options::value<int>(&burnPeriod)->default_value(5000), "Burn period for the simulation.")
        ("sweeps,s", boost::program_options::value<int>(&totalSweeps)->default_value(10000), "The number of sweeps in the simulation.")
        ("output,o",boost::program_options::value<std::string>(&outputName)->default_value(getTimeStamp()), "Name of output directory to save output files into.")
        ("measurement-interval,i", boost::program_options::value<int>(&measurementInterval)->default_value(10), "Number of sweeps between output/measurements")
        ("animate,a","Animate the program by printing the current state of the lattice to an output file during simulation")
        ("help,h", "Produce help message");

    // Make arguments available to program.
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc), vm);
    boost::program_options::notify(vm);

    // If the user asks for help display it then exit.
    if(vm.count("help"))
    {
        std::cout << desc << '\n';
        return 1;
    }

    // Create an output directory from either the default time stamp or the user defined string.
    makeDirectory(outputName);

    // Create an output file for the lattice so it can be animated.
    std::fstream latticeOutput(outputName+"/Lattice.dat", std::ios::out);

    // Create an output file for the order parameter which in this case is the fraction of infected states.
    std::fstream orderParameterOutput(outputName+"/OrderParameter.dat", std::ios::out);

    // Create an output file for the input parameters.
    std::fstream inputParametersOutput(outputName+"/Input.txt", std::ios::out);

    // Create an output file for the results.
    std::fstream resultsOutput(outputName+"/Results.txt", std::ios::out);

    // Create a SIRS lattice that will be used in the simulation.
    SIRSArray lattice(generator,rowCount, colCount, probSI, probIR, probRS);

    // Print the initial lattice to an output file.
    latticeOutput << lattice;

    // Create an object to hold the input parameters.
    SIRSInputParameters inputParameters
    {
	    rowCount,
		colCount,
		probSI,
		probIR,
		probRS,
		burnPeriod,
		totalSweeps,
		measurementInterval,
		outputName
    };

    // Print the input parameters to the command line and to the output file.
   	std::cout << inputParameters << '\n';
   	inputParametersOutput << inputParameters << '\n';

   	// Create an array to store the value of the order parameter on each recorded sweep.
   	DataArray orderParameterData(totalSweeps/measurementInterval);

/*************************************************************************************************************************
************************************************* Main Loop *************************************************************
*************************************************************************************************************************/
   // The program contains two loops, one if the user specified animation, the other if the simulation is to be done
   // without animation.

   // Loop for doing animation.
   if(vm.count("animate"))
   {
         while(true)
         {
            // Update the lattice. 
            lattice.update(generator);

            // Move to the top of the file.
            latticeOutput.seekg(0,std::ios::beg);

            // Output the current state of the lattice.
            latticeOutput << lattice << std::flush;

            // Sleep the thread so output isn't too fast to animate.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

         }  
   }
   // Otherwise we only want measurements so there is no point animating.
   else
   {
       for(int sweep = 0; sweep < totalSweeps+burnPeriod; ++sweep )
       {
       		// Update the lattice by performing row*col sweeps.
       		for(int i = 0; i < lattice.getSize(); ++i)
       		{
       			lattice.update(generator);
       		}

       		// If we are on a measurement sweep then do any measurement/output.
       		if((0 == sweep%measurementInterval) && (sweep >= burnPeriod))
       		{
       			// Calculate the fraction of infected sites on this sweep.
       			double orderParameter = lattice.stateFraction(SIRSArray::Infected);

       			// Output the fraction of infected states and the current sweep.
       			orderParameterOutput << sweep << ' ' <<  orderParameter << '\n';

       			// Record the order parameter on this sweep.
       			orderParameterData.push_back(orderParameter);
       		}
       }
    }

/*************************************************************************************************************************
******************************************** Output/Clean Up *************************************************************
**************************************************************************************************************************/

   // Average the order parameter and calculate the error.
   double orderParameterAverage = orderParameterData.mean();
   double orderParameterError   = orderParameterData.error();

   // Create an object to hold the results.
   SIRSResults results
   {
   		orderParameterAverage,
   		orderParameterError
   };
   
   // Output the results to the command line.
   std::cout << results << '\n';

   // Output the results to the output file.
   resultsOutput << results << '\n';

   // Report how long the program took to execute.
   std::cout << std::setw(30) << std::setfill(' ') << std::left << "Time take to execute(s) =    " << 
   std::right << timer.elapsed() << '\n';



   return 0;
}
