#include "Day_05.h"

#include <chrono>



inline void read_entries(const std::string& filename, instructions_t& instructions) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_05\\" + filename };

    int stage = 0;
    int num_stacks = 0;
    std::vector<std::vector<char>> create_lists;

    std::string line;
    while (std::getline(file, line)) {
        if (num_stacks == 0) {
            num_stacks = (int)ceil(line.size() / 4.0f);
            create_lists.resize(num_stacks);
        }

        if (line == "" || line[1] == '1') {
            stage = 1;
            continue;
        }

        if (stage == 0)
        {
            for (int i = 0; i < num_stacks; ++i) {
                char crate = line[1 + (i * 4)];
                if (crate != ' ') {
                    create_lists[i].push_back(crate);
                }
            }
        }
        else
        {
            move_t move;
            sscanf_s(line.c_str(), "move %d from %d to %d\n", &move.num, &move.from, &move.to);
            instructions.moves.push_back(move);
        }
    }

    instructions.stacks.resize(num_stacks);
    for (int i = 0; i < num_stacks; ++i) {
        for (int j = (int)create_lists[i].size() - 1; j >= 0; --j) {
            instructions.stacks[i].push(create_lists[i][j]);
        }
    }
}

inline auto crate_mover_9000(instructions_t instructions) {
    for (auto& move : instructions.moves) {
        for (int i = 0; i < move.num; ++i) {
            instructions.stacks[move.to - 1].push(instructions.stacks[move.from - 1].top());
            instructions.stacks[move.from - 1].pop();
        }
    }

    std::string ret(instructions.stacks.size(), ' ');
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = instructions.stacks[i].top();
    }

    return ret;
}


inline auto crate_mover_9001(instructions_t instructions) {
    for (auto& move : instructions.moves) {
        std::vector<char> to_move;
        for (int i = 0; i < move.num; ++i) {
            to_move.push_back(instructions.stacks[move.from - 1].top());
            instructions.stacks[move.from - 1].pop();
        }

        for (int i = (int)to_move.size() - 1; i >= 0; --i) {
            instructions.stacks[move.to - 1].push(to_move[i]);
        }
    }

    std::string ret(instructions.stacks.size(), ' ');
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = instructions.stacks[i].top();
    }

    return ret;
}




int main() {
	instructions_t instructions;



	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_05\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", instructions);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Crate Mover 9000: " << crate_mover_9000(instructions) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";
    
    start = std::chrono::high_resolution_clock::now();
	std::cout << "Crate Mover 9001: " << crate_mover_9001(instructions) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";

	file_time.close();
}

