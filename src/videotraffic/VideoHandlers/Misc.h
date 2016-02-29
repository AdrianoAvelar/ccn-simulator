/*
 * Misc.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef MISC_H_
#define MISC_H_




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int casecmp(const char *, const char *);
char *dupstr(const char *);
char *skips(char *, const char *, int);
char *skipc(char *, const char *);
char *getstr(char *, const char *, char **);
unsigned getuint(char *, const char *, unsigned *);
double getdbl(char *, const char *, double *);
unsigned neededbits(unsigned long);
int copyfile(char *, char *);

#ifdef __cplusplus
}
#endif


class Misc {
public:
    Misc();
    virtual ~Misc();
};

#endif /* MISC_H_ */
