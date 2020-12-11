#include <vector>
#include <algorithm>
#include "iostream"
#include <string>
#include <fstream>
#include <map>
#include "mapreducer.h"


int main(int argc, char *argv[])
{
    if (argc != 4)
        return -1;

    std::string src = argv[1];
    if (filesize(src.c_str()) <= 0)
        return -2;


    int mnum = atoi(argv[2]);
    if (mnum<=0)
        return -3;

    int rnum = atoi(argv[3]);
    if (rnum<=0)
        return -4;


    auto mr = MapReducer(mnum, rnum);
    mr.process(src);
}