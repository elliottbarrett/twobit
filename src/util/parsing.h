#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include <vector>
#include <sstream>
#include <string>

std::vector<float> parse_floats(std::string numbers) 
{
    std::vector<float> v;

    std::istringstream iss(numbers);

    std::copy(std::istream_iterator<float>(iss),
        std::istream_iterator<float>(),
        std::back_inserter(v));

    return v;

}

#endif