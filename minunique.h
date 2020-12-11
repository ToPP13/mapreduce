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

class MinUnique
{
public:
    void operator() (int i, const std::vector<std::string> & lines);
private:
    int get_common_symbols(std::string str1, std::string str2);
    int get_min_unique_seq(const std::vector<std::string> & lines);
};
