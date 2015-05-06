/**
\date 2015
\copyright Oleander Software, Ltd.
\author Oleander Software, Ltd.
\details This program is free software; you can redistribute it and/or modify
it under the terms of the BSD License.
*/

#ifndef __SAFE_MATH_H__
#define __SAFE_MATH_H__

#include <cmath>

///Modulus operation that checks for division by zero or into zero (returns zero for those situations).
template<typename T>
inline T safe_modulus(const T val1, const T val2)
    {
    if (val1 == 0 || val2 == 0)
        { return 0; }
    return val1 % val2;
    }

///Division operation that checks for division by zero or into zero (returns zero for those situations).
template<typename T>
inline T safe_divide(const T val1, const T val2)
    {
    if (val1 == 0 || val2 == 0)
        { return 0; }
    return val1/static_cast<T>(val2);
    }

///Division operation (returning as a double) that checks for division by zero or into zero (returns zero for those situations).
template<typename T>
inline double safe_divided(const T val1, const T val2)
    {
    if (val1 == 0 || val2 == 0)
        { return 0; }
    return val1/static_cast<double>(val2);
    }

///Division operation (returning as a floating point value) that checks for division by zero or into zero (returns zero for those situations).
template<typename T>
inline float safe_dividef(const T val1, const T val2)
    {
    if (val1 == 0 || val2 == 0)
        { return 0; }
    return val1/static_cast<float>(val2);
    }

#endif //__SAFE_MATH_H__
