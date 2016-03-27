/* DumpFile.cc
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#include "DumpFile.h"

DumpFile::DumpFile() {
    this->filePath = NULL;
    this->fp = NULL;
    is_open = false;
    fileName = 0;
    filePath= 0;
    fp = 0;

}

void DumpFile::setFilePath(const char* filePath) {

    this->filePath = new char[strlen(filePath) + 1];
    memcpy(this->filePath, filePath, strlen(filePath)) ;
    this->filePath[strlen(filePath)] = '\0';
}


void DumpFile::setFileName(const char* filename) {
    this->fileName = new char[strlen(filename) + 1];
    memcpy(this->fileName, filename, strlen(filename));
    this->fileName[strlen(filename)] = '\0';
}

const char* DumpFile::getFilePath() {

    return (const char*) filePath;
}

const char* DumpFile::getFileName() {

    return (const char*) fileName;
}

int DumpFile::open(const char* option) {

    if ((fp = fopen(filePath, option)) == NULL) {
        std::cerr << "DumpFile::open: can't open file " << filePath << std::endl;
       return -1;
    }

    is_open = true;

    return 0;

}

FILE * DumpFile::getFP() {
    return fp;
}

void DumpFile::close() {

    if (is_open){
        if (fclose(fp) == 0) { //close was successful
            fp = 0;
            is_open = false;
        } else {
            fprintf(stderr, "DumpFile::close(): Can't close file %s\n",
                    filePath);

        }
    }
}

void DumpFile::add(char* buf) {

    if (!is_open) {
        fprintf(stderr, "Can't add line file %s is not open\n", filePath);
        exit(-1);
    }

    fwrite(buf, strlen(buf), 1, fp);
    fflush(fp);
}

bool DumpFile::isOpen() {
    return is_open;
}
DumpFile::~DumpFile() {

    if(filePath != 0)
        delete filePath;

    if(fileName != 0)
        delete fileName;
    if(fp != 0)
        delete fp;

    close();

}

