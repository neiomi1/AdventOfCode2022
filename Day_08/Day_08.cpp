#include "Day_08.h"

#include <chrono>
#include <map>

inline void read_entries(const std::string& filename, std::vector<std::vector<int>>& trees) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_08\\" + filename};

	std::string line;
	
	while (std::getline(file, line)) {
		std::vector<int> row;
		for(char& c : line) {
			row.push_back((c-48));
		}
		trees.push_back(row);
	}
}

inline void calculate_visibility(std::vector<std::vector<int>>& trees, std::vector<std::vector<bool>>& visible) {
	const int max_rows = static_cast<int>(trees.size());
	const int max_cols = static_cast<int>(trees[0].size());

	//set the outer trees to visible
	for (int col = 0; col < trees[0].size() - 1; col++) {
		visible[0][col] = true;
		visible[max_rows - 1][col] = true;
	}
	for (int row = 0; row < trees.size(); row++) {
		visible[row][0] = true;
		visible[row][max_cols - 1] = true;
	}

	//check rows
	for (int row = 0; row < max_rows; row++) {
		int max_from_right = trees[row][0];
		int max_from_left = trees[row][max_cols - 1];
		for (int col = 0; col < max_cols -1; col++) {
			if (max_from_right < trees[row][col + 1]) {
				visible[row][col + 1] = true;
				max_from_right = trees[row][col + 1];
			}
			if (max_from_left < trees[row][max_cols - col - 2]) {
				visible[row][max_cols - col - 2] = true;
				max_from_left = trees[row][max_cols - col - 2];
			}
		}
	}

	//check columns
	for (int col = 0; col < max_cols; col++) {
		int max_from_bottom = trees[0][col];
		int max_from_top = trees[max_cols -1][col];
		for (int row = 0; row < max_rows -1; row++) {
			if (max_from_bottom < trees[row+1][col]) {
				visible[row+1][col] = true;
				max_from_bottom = trees[row+1][col];
			}
			if (max_from_top < trees[max_rows-row-2][col]) {
				visible[max_rows - row - 2][col] = true;
				max_from_top = trees[max_rows - row - 2][col];
			}
		}
	}
}


inline int count_visible(std::vector<std::vector<bool>>& visible) {
	return std::accumulate(
		std::begin(visible),
		std::end(visible),
		0,
		[](const int sum, const std::vector<bool>& row) { return sum + static_cast<int>(std::count(std::begin(row), std::end(row), true)); });
}


inline int max_scenic_score(std::vector<std::vector<int>>& trees, std::vector<std::vector<int>>& scenic_scores) {
	const int max_rows = static_cast<int>(trees.size());
	const int max_cols = static_cast<int>(trees[0].size());

	int score = 0;

	//set the outer trees to visible
	for (int col = 0; col < trees[0].size() - 1; col++) {
		scenic_scores[0][col] = 0;
		scenic_scores[max_rows - 1][col] = 0;
	}
	for (int row = 0; row < trees.size(); row++) {
		scenic_scores[row][0] = 0;
		scenic_scores[row][max_cols - 1] = 0;
	}

	//check rows
	for (int row = 0; row < max_rows; row++) {
		std::map<int, int> max_from_left;
		max_from_left[trees[row][0]] = 1;
		std::map<int, int> max_from_right;
		max_from_right[trees[row][max_cols - 1]] = 1;
		for (int col = 0; col < max_cols - 1; col++) {
			auto height = trees[row][col + 1];
			auto pos = max_from_left.lower_bound(height);
			if (pos != max_from_left.end()){
				scenic_scores[row][col + 1] *= pos->second;
			}
			else {
				scenic_scores[row][col + 1] *= (col+1);
			}
			max_from_left[trees[row][col + 1]] = 0;
			for (auto& element : max_from_left) {
				if (element.first < height) element.second = 0;
				element.second++;
			}

			height = trees[row][max_cols - col - 2];
			pos = max_from_right.lower_bound(height);
			if (pos != max_from_right.end()) {
				scenic_scores[row][max_cols - col - 2] *= pos->second;
			}
			else {
				scenic_scores[row][max_cols - col - 2] *= (col + 1);
			}
			max_from_right[trees[row][max_cols - col - 2]] = 0;
			for (auto& element : max_from_right) {
				if (element.first < height) element.second = 0;
				element.second++;
			}
		}
	}



	//check columns
	for (int col = 0; col < max_cols; col++) {
		std::map<int, int> max_from_bottom;
		max_from_bottom[trees[0][col]] = 1;
		std::map<int, int> max_from_top;
		max_from_top[trees[max_rows-1][col]] = 1;
		for (int row = 0; row < max_rows - 1; row++) {
			auto height = trees[row+1][col];
			auto pos = max_from_bottom.lower_bound(height);
			if (pos != max_from_bottom.end()) {
				scenic_scores[row+1][col] *= pos->second;
				score = std::max(scenic_scores[row + 1][col], score);
			}
			else {
				scenic_scores[row + 1][col] *= (row + 1);
			}
			max_from_bottom[trees[row + 1][col]] = 0;
			for (auto& element : max_from_bottom) {
				if (element.first < height) element.second = 0;
				element.second++;
			}


			height = trees[max_rows - row - 2][col];
			pos = max_from_top.lower_bound(height);

			if (pos != max_from_top.end()) {
				scenic_scores[max_rows - row - 2][col] *= pos->second;
				score = std::max(scenic_scores[max_rows - row - 2][col], score);
			}
			else {
				scenic_scores[max_rows - row - 2][col] *= (row + 1);
			}
			max_from_top[trees[max_rows - row - 2][col]] = 0;
			for (auto& element : max_from_top) {
				if (element.first < height) element.second = 0;
				element.second++;
			}
		}
	}


	return score;
}


int main() {
	std::vector<std::vector<int>> trees;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_08\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", trees);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	std::vector<std::vector<bool>> visible(
		trees.size(),
		std::vector<bool>(trees[0].size(), false)
	);

	start = std::chrono::high_resolution_clock::now();
	calculate_visibility(trees, visible);
	std::cout << "Sum of all visible trees: " << count_visible(visible) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";


	std::vector<std::vector<int>> scenic_score(
		trees.size(),
		std::vector<int>(trees[0].size(), 1)
	);

	start = std::chrono::high_resolution_clock::now();
	std::cout << "highest scenic score: " << max_scenic_score(trees, scenic_score) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";
}

