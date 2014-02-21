// Copyright (C) 2011 - Tencent Inc.
// Author: Liu Shaohui (struggleliu@tencent.com)
//
// Created: 08/16/2011 09:29:54
// Description:

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

typedef unsigned int      uint32_t;

//#include "thirdparty/google/profiler.h"

#define BUFSIZE 1<<12

char buf[BUFSIZE];

int main(int argc, char** argv) {
    //ProfilerStart("./missile.prof");
    uint32_t altitude = 0, read_len;
    FILE * pFile = fopen(argv[1], "r");
    std::vector<uint32_t> seqs;
    seqs.push_back(0);
    while ((read_len = fread(buf, sizeof(char), BUFSIZE, pFile)) > 0) {
        for (uint32_t i = 0;  i < read_len; i ++) {
            if (buf[i] != '\n') {
                altitude = altitude * 10 + buf[i] - '0';
            } else {
                if (seqs.back() > altitude) {
                    *upper_bound(seqs.begin(), seqs.end(), altitude) = altitude;
                } else {
                    seqs.push_back(altitude);
                }
                altitude = 0;
            }
        }
    }
    printf("%zu\n", seqs.size() - 1);
    fclose(pFile);
    //ProfilerStop();
    return 0;
}
