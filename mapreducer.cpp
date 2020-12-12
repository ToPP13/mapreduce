//
// Created by kirill on 11.12.2020.
//

#include "mapreducer.h"

using namespace std;

void MapReducer::process(string & src)
{
    vector<thread> map_threads;
    dataBatch data_batches;

    vector<thread> reduce_threads;
    auto split_positions = get_read_interval(src, _mnum);

    map_threads.reserve(_mnum);
    reduce_threads.reserve(_rnum);


    for (int i=0;i<_mnum;i++)
    {
        dataSequence empty_list = {};
        data_batches.insert({i,empty_list});
        map_threads.emplace_back(thread(FileReader(), src, split_positions[i], ref(data_batches[i])));
    }

    for (int i=0;i<_mnum;i++)
        map_threads[i].join();

    dataBatch splitted_parts;
    shuffle(data_batches, splitted_parts);


    for (int i=0;i<_rnum;i++)
    {
        reduce_threads.emplace_back(thread(MinUnique(), i, ref(splitted_parts[i])));
    }

    for (int i=0;i<_rnum;i++)
        reduce_threads[i].join();
}

void MapReducer::shuffle(dataBatch & inDataBatch, dataBatch & outDataBatch)
{

    vector<string> sorted_lines;
    set_sorted_data(sorted_lines, inDataBatch);
    SplitVector(outDataBatch, sorted_lines, _rnum);
}


vector<readInterval> MapReducer::get_read_interval(string & src, uint num_positions)
{
    vector<readInterval> positions;
    vector<uint> approx_positions;

    positions.reserve(num_positions);
    approx_positions.reserve(num_positions);

    ifstream file_stream (src, ifstream::binary);
    if (!file_stream)
    {
        file_stream.close();
        return positions;
    }


    auto file_size = filesize(src.c_str());

    double approx_interval = ((double)file_size) / num_positions;
    // all except last
    for (uint i=0;i<(num_positions-1);i++)
    {
        approx_positions.emplace_back(((int)approx_interval*(i+1)));

    }
    // last one for sure last
//    approx_positions.emplace_back(file_size);

    uint ex_pos=0;
    for (uint approx_pos : approx_positions)
    {
        readInterval cur_read_interval;
        cur_read_interval.first = ex_pos;
        cur_read_interval.second = approx_pos;
        file_stream.seekg(approx_pos);
        char ele;
        while (file_stream.peek() != '\n')
        {
            file_stream >> ele;
            cur_read_interval.second++;
        }
        positions.emplace_back(cur_read_interval);
        ex_pos = cur_read_interval.second+1;
    }
    file_stream.close();

    readInterval last_interval{ex_pos, file_size};
    positions.emplace_back(last_interval);

    return positions;
}


std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void map_fun(std::string file, const readInterval & read_interval, std::vector<std::string> & lines)
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

void MapReducer::set_sorted_data(std::vector<std::string> & sorted_lines, std::map<size_t, std::vector<std::string>> & data_batches)
{

    //    for (auto el: email_list)
    //    {
    //        for (auto e : el.second)
    //            cout << e << endl;
    //        cout << endl;
    //    }
    if (data_batches.size() == 1)
    {
        sorted_lines = data_batches[0];
        data_batches.erase(0);
    }
    else
    {
        sorted_lines.reserve(data_batches[0].size()*(data_batches.size()+1));
        for (auto & v_pair : data_batches)
        {
            for (auto & e : v_pair.second)
                insert_sorted(sorted_lines, e);
        }
    }
}

