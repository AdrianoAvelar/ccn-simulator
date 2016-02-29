/*
 * File:   VideoTrafficGenerator.h
 * Author: adriano
 *
 * Created on 5 de Fevereiro de 2014, 16:55
 */

#ifndef VIDEOTRAFFICGENERATOR_H
#define	VIDEOTRAFFICGENERATOR_H

#include "FileHandlers/SenderTrace.h"
#include "VideoPacket_m.h"
#include <unistd.h>
#include <stdio.h>

#include "Ccnr.h"

#define BUFFER_SIZE 256


class VideoTrafficGenerator {
public:
    VideoTrafficGenerator();
    ~VideoTrafficGenerator();
    virtual double next_interval(int &);
    void setTraceFile(SenderTrace *traceFile);
    void init();
    double timeout(VideoPacket * packet);
    bool running_;
    bool fillchunk(datachunk* );
private:

    SenderTrace *tfile_;
    struct tracerec trec_;
    int ndx_;
    long int f_, p_, max_;

    int pktsize_;
    double totalTime;
    double nextPkttime_ ;
    int framepktid_;
    unsigned long fragment;
    int    debugLevel;
    char output[BUFFER_SIZE];
};

#endif	/* VIDEOTRAFFICGENERATOR_H */

