/*
 * rvUtils.h
 *
 *  Created on: 4 Feb 2018
 *      Author: dan
 */

#ifndef RVUTILS_H_
#define RVUTILS_H_

#include <stdint.h>

class Utils
{
public:
    static long int GetTimems();
    static long int GetTimeus();

    static int16_t ArrayAverage(int16_t* p_array, int arraySize);
};

#endif /* RVUTILS_H_ */
