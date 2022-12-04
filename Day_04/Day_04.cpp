#include "Day_04.h"

#include <chrono>



inline void read_entries(const std::string& filename, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& elf_pairs) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_04\\" + filename };
	int a1, a2, b1, b2;
	char c;
	while (file >> a1 >> c >> a2 >> c >> b1 >> c >> b2) {
		std::pair<int, int> elf_1( a1, a2);
		std::pair<int, int> elf_2( b1, b2);
		std::pair<std::pair<int, int>, std::pair<int, int>> elf_pair(elf_1, elf_2);
		elf_pairs.push_back(elf_pair);
	}
}

inline int full_contains(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& elf_pairs) {
	int contains = 0;
	std::for_each(elf_pairs.begin(), elf_pairs.end(), [&](const auto& elf_pair) {
		const int min = std::max(elf_pair.first.first, elf_pair.second.first);
		const int max = std::min(elf_pair.first.second, elf_pair.second.second);
		contains += (elf_pair.first.first >= min && elf_pair.first.second <= max || elf_pair.second.first >= min && elf_pair.second.second <= max) ? 1 : 0;
		});
	return contains;
}


inline int overlaps(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& elf_pairs) {
	int overlaps = 0;
	std::for_each(elf_pairs.begin(), elf_pairs.end(), [&](const auto& elf_pair) {
		const int min = std::max(elf_pair.first.first, elf_pair.second.first);
		const int max = std::min(elf_pair.first.second, elf_pair.second.second);
		overlaps += (min <= max) ? 1 : 0;
		});
	return overlaps;
}



int main() {
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> elf_pairs;



	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_04\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", elf_pairs);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Contained: " << full_contains(elf_pairs) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Overlaps: " << overlaps(elf_pairs) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

	file_time.close();
}

