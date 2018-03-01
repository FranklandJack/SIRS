#ifndef Susceptibility_hpp
#define Susceptibility_hpp
#include "DataArray.hpp"

class Susceptibility : public DataArray::IDataFunctor
{
private:

public:
	Susceptibility();

	double operator()(const DataArray &data) const;

};

#endif /* Susceptibility_hpp */