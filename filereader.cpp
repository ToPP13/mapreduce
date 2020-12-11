//
// Created by kirill on 12.12.2020.
//

#include "filereader.h"

void FileReader::operator ()(std::string file, const readInterval & read_interval, std::vector<std::string> & lines)
{
    std::string line;
    std::ifstream file_stream (file, std::ifstream::binary);
    if (file_stream)
    {
        file_stream.seekg(read_interval.first);
        while(file_stream.tellg() < read_interval.second)
        {
            std::getline(file_stream, line);
            if (!line.empty())
            {
                lines.emplace_back(line);
            }
        }
    }
    file_stream.close();
    std::sort(lines.begin(), lines.end());
}