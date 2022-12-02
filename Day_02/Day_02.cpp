#include "Day_02.h"

#include <chrono>



inline void read_entries(const std::string& filename, std::vector<rockPaperScissorsRound>& entries) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_02\\" + filename };
	char p1;
	char p2;
	while (file >> p1 >> p2) {
		entries.push_back(rockPaperScissorsRound(p1, p2));
	}
	
}

inline int highscore(std::vector<rockPaperScissorsRound>& entries) {
	int highscore = 0;
	std::for_each(entries.begin(), entries.end(), [&](rockPaperScissorsRound& entry) {highscore += entry.score(); });
	return highscore;
}

inline int highscore_part_two(std::vector<rockPaperScissorsRound>& entries) {
	int highscore = 0;
	std::for_each(entries.begin(), entries.end(), [&](rockPaperScissorsRound& entry) {highscore += entry.score_2(); });
	return highscore;
}


int main() {
	std::vector<rockPaperScissorsRound> entries;



	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_02\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", entries);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Highscore: " << highscore(entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";
	
	start = std::chrono::high_resolution_clock::now();
	std::cout << "Highscore: " << highscore_part_two(entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";


	file_time.close();
}

