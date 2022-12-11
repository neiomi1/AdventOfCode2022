#include "Day_09.h"

#include <chrono>
#include <map>

const std::map<char, std::pair<int, int>> directionmapping{
	{'L', std::make_pair(-1, 0)},
	{'R', std::make_pair(1, 0)},
	{'U', std::make_pair(0, 1)},
	{'D', std::make_pair(0,-1)},
};



inline void print_position(const std::pair<int, int>& pos) {
	std::cout << std::format("({}, {})", pos.first, pos.second) << "\n";
}


inline void read_entries(const std::string& filename, std::vector<std::pair<int, std::pair<int, int>>>& instructions) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_09\\" + filename};

	char direction;
	int amount;

	while (file >> direction >> amount) {
		std::pair<int, std::pair<int, int>> instruction;
		instruction.first = amount;
		instruction.second = directionmapping.at(direction);
		instructions.push_back(instruction);
	}
}


inline int tail_visited(std::vector<std::pair<int, std::pair<int, int>>>& instructions) {
	std::map<std::pair<int, int>, bool> visited;
	std::pair<int, int> head_position{ 0,0 };
	std::pair<int, int> tail_position{ 0,0 };

	auto instruction = instructions.begin();
	auto steps = instruction->first;
	head_position = head_position + instruction->second;
	auto prev_head_pos = head_position;
	steps--;
	visited[tail_position] = true;
	auto distance = head_position - tail_position;

	do {
		for (; steps > 0; steps--) {
			distance = head_position - tail_position;
			if (abs(distance.first) > 1 || abs(distance.second) > 1) {
				tail_position = prev_head_pos;
				visited[tail_position] = true;				
			}
			prev_head_pos = head_position;
			head_position = head_position + instruction->second;
			
		}
		instruction++;
		steps = instruction->first;
	} while (instruction < instructions.end() - 1);

	distance = head_position - tail_position;
	if (abs(distance.first) > 1 || abs(distance.second) > 1) {
		tail_position = prev_head_pos;
		visited[tail_position] = true;
	}


	return static_cast<int>(visited.size());
}

int main() {
	std::vector<std::pair<int, std::pair<int, int>>> instructions;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_09\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", instructions);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	start = std::chrono::high_resolution_clock::now();
	std::cout << "Amount of positions the tail visited: " << tail_visited(instructions) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

}

