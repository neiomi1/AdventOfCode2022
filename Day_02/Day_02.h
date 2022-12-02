#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct rockPaperScissorsRound
{
	char player_1;
	char player_2;

	rockPaperScissorsRound(char p1, char p2) :player_1(p1-=65), player_2(p2 -=88) {};

	int score() {
		//cast player_2 to a-c scheme
		int round = ((player_2 - player_1 + 1) % 3 + 3) % 3;
		return player_2 + 1 + round * 3;
	}

	int score_2() {
		int round = player_2;
		int score = ((player_1 + player_2 - 1) % 3 + 3) % 3;
		score = score < 0 ? score += 3 : score;

		return score + 1 + round * 3;
	}
};

inline void read_entries(const std::string& filename, std::vector<rockPaperScissorsRound>& entries);

inline int highscore(std::vector<rockPaperScissorsRound>& entries);

inline int highscore_part_two(std::vector<rockPaperScissorsRound>& entries);

