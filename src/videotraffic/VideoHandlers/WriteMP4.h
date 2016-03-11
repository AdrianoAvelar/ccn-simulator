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

//static GF_HintSample *gf_isom_hint_sample_new2(u32 ProtocolType);

class WriteMP4 {
public:
    WriteMP4();
    virtual ~WriteMP4();
};

#endif /* WRITEMP4_H_ */
