/*
 * Stat.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef STAT_H_
#define STAT_H_


#include "commons.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Stat.h"

#ifdef __cplusplus
extern "C" {
#endif

void CalcTime(dump_t *, unsigned, char *);
void CalcLoss(dump_t *, unsigned, loss_t *, char *);
void CalcDist(dump_t *, unsigned, loss_t *);
void CalcJitter(dump_t *, unsigned);
void PoBLoss(dump_t *, unsigned, unsigned, unsigned int);
void OutJitter(dump_t *, unsigned, char *);
void CalcSRate(dump_t *, unsigned, double, char *);
void CalcRRate(dump_t *, unsigned, double, char *);

void Hist(double *, unsigned, double, double, unsigned);

#ifdef __cplusplus
}
#endif


class Stat {
public:
    Stat();
    virtual ~Stat();
};

#endif /* STAT_H_ */
