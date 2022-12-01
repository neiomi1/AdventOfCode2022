#include "Day_01.h"

#include <chrono>



inline void read_entries(const std::string& filename, std::vector<std::vector<int>>& entries) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\" + filename };
	std::vector<int> temp;
	int current;
	while(!file.eof()){
		std::string line;
		std::getline(file, line);

		if (line.empty()) {
			entries.push_back(temp);
			temp = std::vector<int>{};
		}
		else {
			current = std::stoi(line);
			temp.push_back(current);
		}
	}
	if(!temp.empty())
		entries.push_back(temp);
}

inline int highest_sum(std::vector<std::vector<int>>& calorielist) {
	int max = 0;
	std::for_each(calorielist.begin(), calorielist.end(), [&](const auto& elf_calorielist) {
		int current = 0;
		std::for_each(elf_calorielist.begin(), elf_calorielist.end(), [&](const auto& elf_calories) {
			current += elf_calories; 
			});
	max = (current > max) ? current : max; 
	});
	return max;
}

inline int highest_sum_top_three(std::vector<std::vector<int>>& calorielist) {
	std::vector<int> sums;
	std::for_each(calorielist.begin(), calorielist.end(), [&](const auto& elf_calorielist) {
		int current = 0;
		std::for_each(elf_calorielist.begin(), elf_calorielist.end(), [&](const auto& elf_calories) {
			current += elf_calories;
			});
		sums.push_back(current);
		});
	std::sort(sums.begin(), sums.end(), [&](int a, int b) {return a > b; });
	return sums[0] + sums[1] + sums[2];
}

int main() {
	std::vector<std::vector<int>> entries;



	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_01\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", entries);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Most Calories on an elf: " << highest_sum(entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated the most Calories on an elf in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Calories on top three elves: " << highest_sum_top_three(entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated the Calories on top three elves in " << duration.count() << " microseconds.";
	
	file_time.close();
}
