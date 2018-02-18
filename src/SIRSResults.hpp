#ifndef SIRSResults_hpp
#define SIRSResults_hpp
#include <iostream>
#include <iomanip>

/**
 *\file 
 *\class SIRSResults
 *\brief Class for easily handling results of SIRS simulation.
 *
 * This class essentially just holds some values and has an operator to easily output
 * them to a stream.
 */
class SIRSResults
{
public:
	/// Order parameter.
	double orderParameter;
	/// Order parameter error.
	double orderParameterError; 

	/** 
	 *\brief operator<< overload for outputting the results.
	 *\param out std::ostream reference that is the stream being outputted to.
	 *\param results constant SIRSResults instance to be output.
	 *\return std::ostream reference so the operator can be chained.
	 *
	 * Results will be output in a formatted table for easy viewing in the command line or a file.
	 */
	friend std::ostream& operator<<(std::ostream& out, const SIRSResults &results);
};

#endif /* SIRSResults_hpp */
