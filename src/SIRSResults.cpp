#include "SIRSResults.hpp"

std::ostream& operator<<(std::ostream &out, const SIRSResults &results)
{	
	int outputColumnWidth = 30;
	out << "Results..." << '\n';
   	out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Order-Parameter: " << 
   	std::right << results.orderParameter << " +/- " << results.orderParameterError << '\n';
   	out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Susceptibility: " << 
   	std::right << results.susceptibility << " +/- " << results.susceptibilityError << '\n';
	return out;
}