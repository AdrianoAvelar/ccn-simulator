/*
 * Read.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef READ_H_
#define READ_H_

#include "commons.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Misc.h"
#include "Read.h"


#ifdef __cplusplus
extern "C" {
#endif

int ReadDump(char **, data_t *, unsigned int, int);
int GetNumB(dump_t *, unsigned);
int ReOrder(data_t *, int);
unsigned long MaxPackSize(dump_t *, unsigned);

#ifdef __cplusplus
}
#endif

class Read {
public:
    Read();
    virtual ~Read();
};

#endif /* READ_H_ */
