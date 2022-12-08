#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>

#include <vector>

inline void read_entries(const std::string& filename, std::vector<std::vector<int>>& trees);

inline void calculate_visibility(std::vector<std::vector<int>>& trees, std::vector<std::vector<bool>>& visible);

inline int count_visible(std::vector<std::vector<bool>>& visible);
