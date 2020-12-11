//
// Created by kirill on 11.12.2020.
//

#pragma once

#include "algorithm"
#include "thread"
#include <vector>
#include "iostream"
#include <string>
#include <fstream>
#include <map>
#include "filereader.h"
#include "minunique.h"



class MapReducer
{
public:
    MapReducer(int mnum, int rnum): _mnum(mnum), _rnum(rnum){};
    void process(std::string & src);

private:
    std::vector<readInterval> get_read_interval(std::string & src, uint num_positions);
    int _mnum;
    int _rnum;
};



template< typename T >
typename std::vector<T>::iterator
insert_sorted( std::vector<T> & vec, T const& item )
{
    return vec.insert
            (
                    std::upper_bound( vec.begin(), vec.end(), item ),
                    item
            );
}


template<typename T>
void SplitVector(std::map<size_t, std::vector<std::string>> & outMap, const std::vector<T>& vec, size_t n)
{

    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;
        outMap.insert({i, std::vector<T>(vec.begin() + begin, vec.begin() + end)});
        begin = end;
    }
}

std::ifstream::pos_type filesize(const char* filename);

int get_common_symbols(std::string str1, std::string str2);


void set_sorted_data(std::vector<std::string> & sorted_lines, std::map<uint, std::vector<std::string>> & email_list);