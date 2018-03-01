#ifndef jackKnife_hpp
#define jackKnife_hpp
#include "DataArray.hpp"
/**
 *\file
 *\brief Function calculate jack-knife error of any function of a DataArray.
 *\param fcn a IDataFunctor reference that acts on the data (this is the function).
 *\param data a DataArray reference the function is a function of.
 *\return floating point value representing the bootstrap error.
 *
 * Jack-Knife error is calculated by removing one data point at a time from the data (re-sampling) and evaluating the 
 * corresponding function then averaging over these values. This function is versatile since it will work with any
 * IDataFunctor reference (which the user can inherit from and define since its operator() is virtual)  and
 * the corresponding bootstrap error can be calculated.
 *
 */
double jackKnife(const DataArray::IDataFunctor &fcn, const DataArray &data);

#endif /* jackKnife_hpp */