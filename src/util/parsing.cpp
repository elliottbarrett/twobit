#include "parsing.h"

#include <vector>
#include <sstream>
#include <string>
#include <iterator>

std::vector<float> parse_floats(std::string numbers)
{
    std::vector<float> v;

    std::istringstream iss(numbers);

    std::copy(std::istream_iterator<float>(iss),
        std::istream_iterator<float>(),
        std::back_inserter(v));

    return v;

}

std::vector<int> parse_ints(std::string numbers)
{
    std::vector<int> v;

    std::istringstream iss(numbers);

    std::copy(std::istream_iterator<int>(iss),
        std::istream_iterator<int>(),
        std::back_inserter(v));

    return v;   
}