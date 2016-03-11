/*
 * BaseFileHandler.h
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#ifndef BASEFILEHANDLER_H_
#define BASEFILEHANDLER_H_

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "shared.h"
class DumpFile {

public:
    DumpFile();
    ~DumpFile();

    void setFileName(const char* filename);
    const char* getFileName();

    void setFilePath(const char* filename);
    const char* getFilePath();

    int  open(const char* option = "r");
    void close();
    void add(char* line);
    FILE * getFP();
    bool isOpen();

private :
    bool is_open;
    char *filePath;
    char *fileName;
    FILE *fp;

};


#endif /* BASEFILEHANDLER_H_ */
