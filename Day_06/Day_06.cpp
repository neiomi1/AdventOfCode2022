#include "Day_06.h"

#include <chrono>



inline void read_entries(const std::string& filename, std::vector<char>& message) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_06\\" + filename };

	char c;
	while (file >> c) {
		message.push_back(c);
	}
}

inline int sliding_window(std::vector<char>& message, int window) {
	int occurences[26]{ 0 };
	int distinct = 0;
	for (int i = 0; i < message.size(); i++) {
		if (!(i < window) && message[i] == message[i - window]) continue;
		distinct += (occurences[message[i] - 97] == 0) ? 1 : 0;
		occurences[message[i] - 97]++;
		if (i < window) continue;
		occurences[message[i - window] - 97]--;
		distinct -= (occurences[message[i - window] - 97] == 0) ? 1 : 0;

		if (distinct == window) return i+1;
	}
	return (int)message.size();
}

inline int part_1(std::vector<char>& message) {
	return sliding_window(message, 4);
}

inline auto part_2(std::vector<char>& message) {
	return sliding_window(message, 14);
}



int main() {
	std::vector<char> instructions;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_06\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", instructions);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "First Signal Bit: " << part_1(instructions) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "First Message Bit: " << part_2(instructions) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";
    
}

