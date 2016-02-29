/*
 * QoEMetric.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: adriano
 */

#include "QoEMetric.h"

QoEMetric::QoEMetric(string ref_trace_name) {

    this->ref_trace_name = ref_trace_name;

    char name[32];
    sprintf(name,"psnr_%s",ref_trace_name.c_str());
    psnr_vec.setName(name);

    sprintf(name,"ssim_%s",ref_trace_name.c_str());
    ssim_vec.setName(name);
}

QoEMetric::~QoEMetric() {
    // TODO Auto-generated destructor stub
}


double QoEMetric::getMean(char* cmd) {

    FILE* pipe = popen(cmd, "r");

    if (!pipe)
        return 0;

    char buffer[128];
    //std::string result = "";

    int count = 0;
    double sum = 0;

    while (!feof(pipe)) {

        if (fgets(buffer, 128, pipe) != NULL) {

            //result += buffer;
            sum += atof(buffer);

            count++;
        }
    }

    pclose(pipe);
    return sum/count;
}

double QoEMetric::getMeanPSNR() {

    char cmd[128];

    sprintf(cmd, "psnr %d %d %d %s %s.yuv ", FRAME_WIDTH,
            FRAME_HEIGHT, YUV_FORMAT, YUV_REF, ref_trace_name.c_str());
    cout << "getMeanPSNR: " << cmd << endl;


    return getMean(cmd);
}

double QoEMetric::calculatePSNR() {
    double psnr = getMeanPSNR();

    if(psnr > 0)
        psnr_vec.record(psnr);
    else
        psnr_vec.record(0);
    return psnr;
}


double QoEMetric::calculateSSIM() {

    double ssim = getMeanSSIM();
    if(ssim > 0)
        ssim_vec.record(ssim);
    else
        ssim_vec.record(0);
    return ssim;
}

double QoEMetric::getMeanSSIM(){

     char cmd[128];

    sprintf(cmd, "psnr %d %d %d %s %s.yuv ssim "
            , FRAME_WIDTH, FRAME_HEIGHT, YUV_FORMAT, YUV_REF, ref_trace_name.c_str());

   cout << "getMeanSSIM: " << cmd << endl;

   return getMean(cmd);
}
