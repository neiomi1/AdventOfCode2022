#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>


using stacks_t = std::vector<std::stack<char>>;

struct move_t {
    int num;
    int from;
    int to;
};

struct instructions_t {
    stacks_t stacks;
    std::vector<move_t> moves;
};


inline void read_entries(const std::string& filename, instructions_t& instructions);

inline auto crate_mover_9000(instructions_t instructions);

inline auto crate_mover_9001(instructions_t instructions);

