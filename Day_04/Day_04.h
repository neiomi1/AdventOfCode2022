#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <tuple>


inline void read_entries(const std::string& filename, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>&  elf_pairs);

inline int full_contains(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& elf_pairs);

inline int overlaps(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& elf_pairs);

