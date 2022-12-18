#pragma once

#include <string>
#include <vector>

std::vector<std::string> read_file(std::string& file_name);

std::vector<std::string> split(const std::string& string, const char separator);