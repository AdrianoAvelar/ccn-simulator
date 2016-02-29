/*
 * EvaluateTrace.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef EVALUATETRACE_H_
#define EVALUATETRACE_H_


#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "WriteMP4.h"
#include "Read.h"
#include "Stat.h"
#include "commons.h"
#include "DumpFile.h"



//#define JITTER_RATE_LOSS
#define SIZE_BUFFER 512

//#define __NO_SUBDIR

class EvaluateTrace{

public:
    EvaluateTrace();
    int evaluate();

    void setSDump(DumpFile *sd);
    void setRDump(DumpFile *rd);
    void setSenderTrace(const char* senderTrace);
    void setMP4file(const char* mp4file);
    void setMP4Output( const char* mp4output);

private:
    DumpFile *sd;
    DumpFile *rd;
    char* senderTrace;
    char* mp4file;
    char* mp4output;

};


#endif /* EVALUATETRACE_H_ */
