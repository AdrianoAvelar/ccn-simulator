/*
 * WriteMP4.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef WRITEMP4_H_
#define WRITEMP4_H_

#include "commons.h"


int WriteMP4(char *, char *, data_t *, unsigned int);


class WriteMP4 {
public:
    WriteMP4();
    virtual ~WriteMP4();
};

#endif /* WRITEMP4_H_ */
