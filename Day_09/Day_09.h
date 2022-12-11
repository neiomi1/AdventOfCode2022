#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

#include <vector>

std::pair<int, int> operator +(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::pair<int, int> operator -(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return std::make_pair(x.first - y.first, x.second - y.second);
}

inline void read_entries(const std::string& filename, std::vector<std::pair<int, std::pair<int, int>>>& instructions);

inline int tail_visited(std::vector<std::pair<int, std::pair<int, int>>>& instructions);
