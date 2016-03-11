/*
 * EvaluateTrace.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#include <EvaluateTrace.h>

/**
 * Evaluation will work only if you put "export MALLOC_CHECK_=0;"
 *   into your environment. This suppress double free messages.
 * @see "man malloc"
 **/

EvaluateTrace::EvaluateTrace() {

}

void EvaluateTrace::setSDump(DumpFile *sd) {
    this->sd = sd;
}
void EvaluateTrace::setRDump(DumpFile *rd) {
    this->rd = rd;
}

void EvaluateTrace::setSenderTrace(const char* senderTrace) {
    this->senderTrace = new char[strlen(senderTrace)];
    strncpy(this->senderTrace, senderTrace, strlen(senderTrace));
    this->senderTrace[strlen(senderTrace)] = '\0';
}

void EvaluateTrace::setMP4file(const char* mp4file) {
    this->mp4file = new char[strlen(mp4file)];
    strncpy(this->mp4file, mp4file, strlen(mp4file));
    this->mp4file[strlen(mp4file)] = '\0';
}

void EvaluateTrace::setMP4Output(const char* mp4output) {
    this->mp4output = new char[strlen(mp4output)];
    strncpy(this->mp4output, mp4output, strlen(mp4output));
    this->mp4output[strlen(mp4output)] = '\0';
}

int EvaluateTrace::evaluate() {

    char *buf[8];

    for (int i = 0; i < 8; i++)
        buf[i] = new char[SIZE_BUFFER];

    strncpy(buf[1], "0", SIZE_BUFFER);
    strncpy(buf[1], "-p", SIZE_BUFFER);
    strncpy(buf[2], "-0", SIZE_BUFFER);
    strncpy(buf[3], sd->getFilePath(), SIZE_BUFFER);
    strncpy(buf[4], rd->getFilePath(), SIZE_BUFFER);
    strncpy(buf[5], this->senderTrace, SIZE_BUFFER);
    strncpy(buf[6], this->mp4file, SIZE_BUFFER);
    strncpy(buf[7], this->mp4output, SIZE_BUFFER);

    char **cl = buf;
    int cn = 8;

    unsigned PoB = 0, num;
    char id[1024] = { 0 }, *p;
    static data_t D;

    memset(&D, 0, sizeof(data_t));

    static loss_t loss;
    dump_t *dump;
    //MODE mode = INVALID;
    unsigned mode = INVALID;
    int l, n = 0, o = 2;

    while (++n < cn - 1) {
        p = cl[n];
        if (*p++ != '-')
            break;
        switch (*p) {
        case 'p':
            mode |= PACKET;
            break;
        case 'f':
            mode |= FRAME;
            break;
        case 'F':
            mode |= COMPLETE;
            break;
        case '0':
            mode |= FILL;
            break;
        case 'x':
            mode |= TRUNC;
            break;
        case 'c':
            o++;
            mode |= ASYNC;
            break;

        }
    }

    if (cn == o + 7) {
        PoB = strtoul(cl[o + 6], 0, 10);
        if (PoB < 1 || PoB > 1000000)
            PoB = 1000000;
    }

#ifdef __NO_SUBDIR

    l = (int) strlen(cl[o + 5]);
    while (l-- && cl[o + 5][l] != '\\' && cl[o + 5][l] != '/');

#endif

    /*std::cerr << cl[o + 5] << std::endl;
     strncpy(id, cl[o + 5] , sizeof id);
     std::cerr << id << std::endl;
     */

#ifdef __NO_SUBDIR
    if ( (p = strrchr(strncpy(id, cl[o + 5] + l + 1, sizeof id - 10), '.')))
#else
    if ((p = strrchr(strncpy(id, cl[o + 5], sizeof id), '.')))
#endif
        *p = 0;

    if (!ReadDump(cl + o, &D, mode, 0))
        return EXIT_FAILURE;

    if (D.F[0].type == 'A')
        mode |= AUDIO;

    dump = mode & FRAME || mode & COMPLETE ? D.F : D.P;
    num = mode & FRAME || mode & COMPLETE ? D.nF : D.nP;

#ifdef JITTER_RATE_LOSS

    CalcJitter(dump, num);

    if (PoB)
    PoBLoss(dump, num, PoB, mode);

    CalcLoss(dump, num, &loss, id);
    OutJitter(dump, num, id);
    CalcSRate(dump, num, 1.0, id);
    CalcRRate(dump, num, 1.0, id);
#endif

    if (!WriteMP4(cl[o + 4], id, &D, mode))
        return EXIT_FAILURE;

    free(D.P);
    free(D.F);

    return 0;
}

