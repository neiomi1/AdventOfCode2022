#include "Day_10.h"

#include <chrono>
#include <map>

const std::map<std::string, Command> CommandMapping{
	{"addx", addx},
	{"noop", noop}
};

const std::map<Command, int> CommandCycleTime{
	{addx, 2},
	{noop, 1}
};

inline void print_position(const std::pair<int, int>& pos) {
	std::cout << std::format("({}, {})", pos.first, pos.second) << "\n";
}


inline void read_entries(const std::string& filename, std::vector<std::pair<Command, int>>& instructions) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_10\\" + filename};

	std::string line;

	while (std::getline(file, line)) {
		std::pair <Command, int> instruction;
		auto pos = line.find(" ");
		instruction.first = CommandMapping.at(line.substr(0, pos));
		switch (instruction.first)
		{
		case addx:
			instruction.second = std::stoi(line.substr(++pos));
			break;
		case noop:
		default: instruction.second = 0;
		}

		instructions.push_back(instruction);
	}
}


inline int part_1(std::vector<std::pair<Command, int>>& instructions) {
	int reg = 1;
	int cycle = 0;
	int command_duration;
	int print = 0;
	int sum = 0;

	for (const auto& instruction : instructions) {
		command_duration = CommandCycleTime.at(instruction.first);
		for (int i = 0; i < command_duration; i++) {
			cycle++;
			if (cycle == 20 + 40 * print) {
				print++;
				sum += reg*cycle;
				std::cout << std::format("Cycle: {} \t register: {} \t signal strength: {} \n", cycle, reg, reg * cycle);
			}
		}
		switch (instruction.first)
		{
		case addx:
			reg += instruction.second;
			break;
		case noop:
		default: break;
		}
	}
	return sum;
}

inline void part_2(std::vector<std::pair<Command, int>>& instructions) {
	int reg = 1;
	int cycle = 0;
	int command_duration;

	for (const auto& instruction : instructions) {
		command_duration = CommandCycleTime.at(instruction.first);
		for (int i = 0; i < command_duration; i++) {
			auto newpage = cycle % 240;
			auto cursor = cycle % 40;
			if (cursor == 0) {
				std::cout << "\n";
			}

			if (newpage == 0) {
				std::cout << std::format("Page: {}\n", cycle / 240);
			}

			if (cursor >= reg -1 && cursor <= reg+1) {
				std::cout << '#';
			}
			else {
				std::cout << ' ';
			}
			cycle++;
		}
		switch (instruction.first)
		{
		case addx:
			reg += instruction.second;
			break;
		case noop:
		default: break;
		}
	}
}


int main() {
	std::vector<std::pair<Command, int>> instructions;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_10\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", instructions);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	start = std::chrono::high_resolution_clock::now();
	std::cout << "sum of these six signal strengths: \n" << part_1(instructions) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	part_2(instructions);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";

}

