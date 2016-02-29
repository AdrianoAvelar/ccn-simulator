/* DumpFile.cc
 *
 *  Created on: Feb 6, 2014
 *      Author: adriano
 */

#include "DumpFile.h"

DumpFile::DumpFile() {
    this->filename = NULL;
    this->fp = NULL;
    is_open = false;
}

void DumpFile::setFileName(const char* filename) {

    //FIXME:[EAMA] Remover lixo


    this->filename = new char[strlen(filename) + 1];
    memcpy(this->filename, filename, strlen(filename)) ;
    this->filename[strlen(filename)] = '\0';


   // strncpy(this->filename, filename, strlen(filename));
}

const char* DumpFile::getFileName() {

    return (const char*) filename;
}

int DumpFile::open(const char* option) {

    if ((fp = fopen(filename, option)) == NULL) {
        fprintf(stderr, "DumpFile::open: can't open file %s\n", filename);
        exit(-1);
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
                    filename);

        }
    }
}

void DumpFile::add(char* buf) {

    if (!is_open) {
        fprintf(stderr, "Can't add line file %s is not open\n", filename);
        exit(-1);
    }

    fwrite(buf, strlen(buf), 1, fp);
    fflush(fp);
}

bool DumpFile::isOpen() {
    return is_open;
}
DumpFile::~DumpFile() {

    delete filename;
    delete fp;
    close();

}

