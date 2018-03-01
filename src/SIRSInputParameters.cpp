#include "SIRSInputParameters.hpp"

std::ostream& operator<<(std::ostream& out, const SIRSInputParameters& params)
{
	int outputColumnWidth = 30;
    out << "Input-Parameters..." << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Rows: " << std::right << params.rowCount << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Columns: " << std::right << params.colCount << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "p_1: " << std::right << params.probSI << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "p_2: " << std::right << params.probIR << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "p_3: " << std::right << params.probRS << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Immune-Fraction: " << std::right << params.immuneFraction << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Burn-Period: " << std::right << params.burnPeriod << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Sweeps: " << std::right << params.sweeps << '\n';
    out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Measurement-Interval: " << std::right << params.measurementInterval << '\n';
	out << std::setw(outputColumnWidth) << std::setfill(' ') << std::left << "Output-Directory: " << std::right << params.outputDirectory << '\n';
    return out;
}