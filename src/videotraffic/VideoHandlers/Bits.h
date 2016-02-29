/*
 * Bits.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef BITS_H_
#define BITS_H_



#include <limits.h>
#include <gpac/setup.h>

#define GETBIT(x, n) ((unsigned) !!((x) & 1U << (n)))
#define SETBIT(x, n) ((x) |= 1U << (n))
#define TGLBIT(x, n) ((x) ^= 1U << (n))
#define CLRBIT(x, n) ((x) &= ~(1U << (n)))



void resetbits(unsigned);
unsigned nextbits(unsigned char *, unsigned);
unsigned skipbits(unsigned char *, unsigned);
unsigned currentpos();
unsigned currentbit();

/* MPEG-4 */

#define SC_VOP  0x1b6
#define SC_GVOP 0x1b3

//int mark_not_coded(unsigned char *p, unsigned n, unsigned nti);
int mark_not_coded(unsigned char *p, u32 n, u8 nti);


class Bits {
public:
    Bits();
    virtual ~Bits();
};

#endif /* BITS_H_ */
