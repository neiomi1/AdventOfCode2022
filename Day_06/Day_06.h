#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

inline void read_entries(const std::string& filename, std::vector<char>& message);


inline int sliding_window(std::vector<char>& message, int window);

inline int part_1(std::vector<char>& message);


inline auto part_2(std::vector<char>& message);

