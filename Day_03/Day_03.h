#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <set>

int charToPriority(const char& c) {
	return (int)(c > 96 ? c - 96 : c - 38);
}

std::string& removeDuplicate(std::string& str)
{
	std::sort(str.begin(), str.end());
	for (int i = 0; i < str.length() - 1;) {
		if (str[i + 1] == str[i])
			str.erase(i + 1, 1);
		else
			i++;
	}
	return str;
};


struct Rucksack
{
	std::string compartment_1;
	std::string compartment_2;
	std::string total;

	Rucksack(std::string compartment_1, std::string compartment_2) :compartment_2(removeDuplicate(compartment_2)), compartment_1(removeDuplicate(compartment_1)) {
		total = compartment_1 + compartment_2;
		removeDuplicate(total);
	};

	int findDuplicateItem() {
		for (char c : compartment_1) {
			if (compartment_2.find(c) != std::string::npos) {
				return charToPriority(c);
			}
		}
		return 0;
	};
};


inline void badgeOptions(Rucksack& elf, std::unordered_set<char>& options) {
	const bool empty = options.empty();
	if (!empty) {
		for (auto it = options.begin(); it != options.end();) {
			const auto pos = std::lower_bound(elf.total.begin(), elf.total.end(), *it);
			if (pos != elf.total.end() && *pos == *it) {
				++it;
			}
			else
				it = options.erase(it);
		}
	}
		//
	else {
			//std::cout << " " << *pos << " at index"  << std::distance(other_elf.total.begin(), pos) << "\n";
		std::for_each(elf.total.begin(), elf.total.end(), [&](const auto& c) {options.insert(c); });
	}
};


inline void read_entries(const std::string& filename, std::vector<Rucksack>& entries);

inline int priorities(std::vector<Rucksack>& entries);

inline int group_badges(std::vector<Rucksack>& entries);

