//
// Created by kirill on 12.12.2020.
//

#pragma once

#include "algorithm"
#include "thread"
#include <vector>
#include "iostream"
#include <string>
#include <fstream>
#include <map>


typedef std::pair<uint, uint> readInterval;

class FileReader
{
public:
    void operator ()(std::string file, const readInterval & read_interval, std::vector<std::string> & lines);
};
