/*
 * QoEMetric.h
 *
 *  Created on: Mar 7, 2014
 *      Author: adriano
 */

#ifndef QOEMETRIC_H_
#define QOEMETRIC_H_

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <omnetpp.h>
using namespace std;


//FIXME[EAMA] Move to ini configuration
#define FRAME_WIDTH     352
#define FRAME_HEIGHT    288
#define YUV_FORMAT      420
#define YUV_REF         "results/akiyo_cif.yuv"

class QoEMetric {
public:
    QoEMetric(string ref_trace_nam);
    virtual ~QoEMetric();

    double getMean(char* cmd);
    double getMeanPSNR();
    double getMeanSSIM();

    //calculate with statistic record
    double calculateSSIM();
    double calculatePSNR();

private:
    string ref_trace_name;

    cOutVector psnr_vec;
    cOutVector ssim_vec;

};

#endif /* QOEMETRIC_H_ */
