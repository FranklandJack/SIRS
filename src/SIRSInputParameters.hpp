#ifndef SIRSInputParameters_hpp
#define SIRSInputParameters_hpp
#include <iostream>
#include <iomanip>
#include <string>
/**
 *\file 
 *\class SIRSInputParameters
 *\brief Class for easily handling input parameters of SIRS simulation.
 *
 * This class essentially just holds some values and has an operator to easily output
 * them to a stream.
 */
class SIRSInputParameters 
{
public:
	
	/// Number of rows in lattice.
	int rowCount;
	/// Number of columns in lattice.
	int colCount;
	/// Probability of cell going from susceptible to infected upon contact.
	double probSI;
	/// Probability of cell going from infected to recovered.
	double probIR;
	/// Probability of cell going from recovered to susceptible.
	double probRS;
	/// Number of discarded sweeps before recording starts.
	int burnPeriod;
	/// Total number of sweeps in the simulation.
	int sweeps;
	/// Interval at which measurements are made.
	int measurementInterval;
	/// Output directory.
	std::string outputDirectory;



    /** 
	 *\brief operator<< overload for outputting the results.
	 *\param out std::ostream reference that is the stream being outputted to.
	 *\param params constant SIRSInputParameters instance to be output.
	 *\return std::ostream reference so the operator can be chained.
	 *
	 * Results will be output in a formatted table for easy viewing in the command line or a file.
	 */
    friend std::ostream& operator<<(std::ostream& out, const SIRSInputParameters& params);

};
#endif /* SIRSInputParameters_hpp */