/*
 * File:   SenderTrace.cpp
 * Author: adriano
 *
 * Created on 5 de Fevereiro de 2014, 16:42
 */

#include "SenderTrace.h"

SenderTrace::SenderTrace()
{
    status_ = 0;
	a_=0;
}

int SenderTrace::get_a()
{
	return a_;
}

void SenderTrace::get_next(int& ndx, tracerec_t& t)
{
	t.trec_time = trace_[ndx].trec_time;
	t.trec_size = trace_[ndx].trec_size;
	t.trec_type = trace_[ndx].trec_type;
	t.trec_prio = trace_[ndx].trec_prio;
	t.trec_max = trace_[ndx].trec_max;

	if (ndx++ == nrec_){
		ndx = 0;
		a_= 1;

	}
}

int SenderTrace::convertSenderTrace(const char* src,const char* dst) {

    DumpFile* trace = new DumpFile();
    trace->setFilePath(src);
    trace->open();

    DumpFile* video = new DumpFile();
    video->setFilePath(dst);
    video->open("w");

    unsigned long no_ , length_ ;
    double tmp1_, tmp2_;
    char frametype_;
    nrec_ = 0;

    double pre_time =0;
    int time ,type_v,prio_p;
    char buf[100];
    while (!feof(trace->getFP())) {
        fscanf(trace->getFP(), "%ld %c %ld %lf %lf",  &no_, &frametype_, &length_, &tmp1_, &tmp2_);

        time = (int)((tmp2_ - pre_time) *1000000.0) ;

        switch(frametype_){
            case 'I':
                type_v = 1;
                prio_p = 0;
                break;
            case 'P':
                type_v = 2;
                prio_p = 0;
                break;
            case 'B':
                type_v = 3;
                prio_p = 0;
                break;
            case 'H':
                type_v = 1;
                prio_p = 0;
                break;
        }


        memset(buf,0,sizeof(buf));
        sprintf(buf, "%-16d %-16ld %-16d %-16d %-16d\n", time, length_, type_v, prio_p, MAX_FRAGMENTED_SIZE);
        fprintf(stderr,"%s",buf);
        video->add(buf);

        pre_time = tmp2_;
    }

    delete video;
    delete trace;
}



int SenderTrace::setup()
{
	tracerec* t;

	int i;
	unsigned long time, size, type, prio, max;

	open();
	nrec_ = 0;

	while (!feof( getFP())){
		fscanf(getFP(), "%ld%ld%ld%ld%ld", &time, &size, &type, &prio, &max);
		nrec_++;
	}

	nrec_=nrec_-2;
	//printf("%d records\n", nrec_);

	rewind(getFP());
	trace_ = new struct tracerec[nrec_];

	for (i = 0, t = trace_; i < nrec_; i++, t++){
		fscanf(getFP(), "%ld%ld%ld%ld%ld", &time, &size, &type, &prio, &max);
		t->trec_time = time;
		t->trec_size = size;
		t->trec_type = type;
		t->trec_prio = prio;
		t->trec_max = max;
	}

	return 0;
}
