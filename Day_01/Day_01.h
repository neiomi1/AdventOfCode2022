#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

inline void read_entries(const std::string& filename, std::vector<int>& entries);

inline int highest_sum(std::vector<std::vector<int>&>& calorielist);

inline int highest_sum_top_three(std::vector<std::vector<int>>& calorielist);