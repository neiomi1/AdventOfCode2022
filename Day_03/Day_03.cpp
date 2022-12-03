#include "Day_03.h"

#include <chrono>



inline void read_entries(const std::string& filename, std::vector<Rucksack>& entries) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_03\\" + filename };
	while (!file.eof()) {
		std::string line;
		std::getline(file, line);

		if (line.empty()) {
			return;
		}
		else {
			entries.push_back(Rucksack(line.substr(0, line.length() / 2), line.substr(line.length() / 2)));
		}
	}
	
}

inline int priorities(std::vector<Rucksack>& entries) {
	int highscore = 0;
	std::for_each(entries.begin(), entries.end(), [&](Rucksack& entry) {highscore += entry.findDuplicateItem(); });
	return highscore;
}


inline int group_badges(std::vector<Rucksack>& entries) {
	int badge_priorities = 0;
	std::unordered_set<char> badge_options;
	for (int i = 0; i < entries.size();) {
		badgeOptions(entries[i], badge_options);
		badgeOptions(entries[i+1], badge_options);
		badgeOptions(entries[i+2], badge_options);

		badge_priorities += charToPriority(*(badge_options.begin()));
		i += 3;
		badge_options.clear();
	}
	return badge_priorities;
}


int main() {
	std::vector<Rucksack> entries;



	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_03\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", entries);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Priorities: " << priorities(entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";
	
	start = std::chrono::high_resolution_clock::now();
	std::cout << "Badge Priorities: " << group_badges(entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";


	file_time.close();
}

