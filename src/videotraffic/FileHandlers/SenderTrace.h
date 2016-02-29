/*
 * File:   FileHander.h
 * Author: adriano
 *
 * Created on 5 de Fevereiro de 2014, 16:42
 */

#ifndef TRACEHANDLER_H
#define	TRACEHANDLER_H

#include <cstring>
#include <cstdio>
#include <stdlib.h>

#include "commons.h"
#include "DumpFile.h"
class SenderTrace : public DumpFile {
 public:
	SenderTrace();
	void get_next(int&, tracerec_t&); /* called by TrafficGenerator
						* to get next record in trace.					*/
	int setup();  /* initialize the trace file */
	int command(int argc, const char*const* argv);
	int get_a();
	int convertSenderTrace(const char* src,const char* dst);
 private:

    int status_;
	int nrec_;    /* number of records in the trace file */
	struct tracerec *trace_; /* array holding the trace */
	int a_;

};

#endif	/* TRACEHANDLER_H */

