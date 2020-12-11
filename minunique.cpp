//
// Created by kirill on 12.12.2020.
//

#include "minunique.h"



void MinUnique::operator() (int i, const std::vector<std::string> & lines)
{
    std::string file_name = std::to_string(i) + ".txt";
    std::ofstream file_stream (file_name, std::ifstream::out);
    if (file_stream)
    {
        file_stream << get_min_unique_seq(lines);
    }
    file_stream.close();
}

int MinUnique::get_common_symbols(std::string str1, std::string str2)
{
    uint i = 0;
    for (;i<str1.size()&&i<str2.size();i++)
    {
        if (str1[i]!=str2[i])
            break;
    }
    return (i+1);
}

int MinUnique::get_min_unique_seq(const std::vector<std::string> & lines)
{
    uint max_common_symbols = 1;
    for (size_t iter1 = 0; iter1 < lines.size(); iter1++)
    {
        for (size_t iter2 = iter1+1; iter2 < lines.size(); iter2++)
        {
            if (iter1==iter2)
                continue;

            uint common_symbols = get_common_symbols(lines[iter1], lines[iter2]);
            if (common_symbols > max_common_symbols)
                max_common_symbols = common_symbols;
        }
    }
    return max_common_symbols;
}

