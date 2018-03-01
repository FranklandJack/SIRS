#include "Susceptibility.hpp"

Susceptibility::Susceptibility(){}

double Susceptibility::operator()(const DataArray &data) const
{
	return (data.squareMean() - data.mean() * data.mean());
}