#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::string> read_file(const std::string& file_name)
{
    std::vector<std::string> result{};

    std::ifstream ifs{"Resources/" + file_name};

    std::string line;
    while (std::getline(ifs, line))
    {
        result.push_back(line);
    }

    return result;
}

std::vector<std::string> split(const std::string& string, const char separator)
{
    std::vector<std::string> result{};

    std::stringstream ss{};
    bool has_token{false};

    for (const char c : string)
    {
        if (c == separator)
        {
            if (has_token)
            {
                result.push_back(ss.str());
                ss.str("");
                has_token = false;
            }
        }
        else
        {
            ss << c;
            has_token = true;
        }
    }

    if (has_token)
    {
        result.push_back(ss.str());
    }

    return result;
}
