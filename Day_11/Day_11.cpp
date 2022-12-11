#include "Day_11.h"

#include <chrono>

inline void read_entries(const std::string& filename, std::vector<Monkey>& monkeys) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_11\\" + filename };

	std::string line;
	Monkey monkey;
	int process = 0;

	while (std::getline(file, line)) {
		if (line.find_first_not_of(' ') == std::string::npos) {
			process = 0;
			monkeys.push_back(monkey);
			monkey = Monkey();
			continue;
		}
		size_t pos;
		switch (process) {
		case 0: break;
		case 1:
			pos = line.find(":");
			line = line.substr(++pos);
			do {
				pos = line.find(",");
				monkey.items.push_back(static_cast<long long>(std::stoi(line.substr(0, pos))));
				line = line.substr(pos+1);
			} while (pos != std::string::npos);
			break;

		case 2: 
			pos = line.find("=");
			line = line.substr(pos+2);
			do {
				pos = line.find(" ");
				monkey.operation.push_back(line.substr(0, pos));
				line = line.substr(pos+1);
			} while (pos != std::string::npos);
			break;
		case 3:
			pos = line.find("by ");
			monkey.test = static_cast<long long>(std::stoi(line.substr(pos+3)));
			break;
		case 4:
			pos = line.find("monkey ");
			monkey.if_true = static_cast<long long>(std::stoi(line.substr(pos+7)));
			break;
		case 5:
			pos = line.find("monkey ");
			monkey.if_false = static_cast<long long>(std::stoi(line.substr(pos + 7)));
			break;
		}
		process++;
	}
	monkeys.push_back(monkey);


	long long kgv = 1;
	for (int i = 0; i < monkeys.size(); i++) {
		kgv *= monkeys[i].test;
	}

	for (int i = 0; i < monkeys.size(); i++) {
		monkeys[i].kgv = kgv;
	}
}

inline long long part_1(std::vector<Monkey>& monkeys, bool print) {
	std::vector<long long> monkey_business(
		monkeys.size(),
		{ (long long)0 }
	);

	for (int round = 0; round < 20; round++) {
		
		for (int i = 0; i < monkeys.size(); i++) {
			monkey_business[i] += static_cast<long long>(monkeys[i].items.size());
			monkeys[i].execute_round(monkeys, true);
		}
		if (print) {
			std::cout << "After round " << round << ", the monkeys are holding items with these worry levels: \n";
			for (int i = 0; i < monkeys.size(); i++) {
				std::cout << "Monkey " << i << ": ";
				for (int j = 0; j < monkeys[i].items.size(); j++) {
					std::cout << monkeys[i].items[j] << ",";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
		}
	}
	if (print) {
		for (int i = 0; i < monkey_business.size(); i++) {
			std::cout << std::format("Monkey {} inspected items {} times\n", i, monkey_business[i]);
		}
	}

	std::sort(monkey_business.begin(), monkey_business.end(), std::greater<long long>());

	return monkey_business[0] * monkey_business[1];
}


inline long long part_2(std::vector<Monkey>& monkeys, bool print) {
	std::vector<long long> monkey_business(
		monkeys.size(),
		{ (long long)0 }
	);

	const int to_print[]{ 1,20, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
	for (int round = 0; round < 10000; round++) {
		if (print) {
			if (std::find(std::begin(to_print), std::end(to_print), round) != std::end(to_print)) {
				std::cout << std::format("== After round {} ==\n", round);
				for (int i = 0; i < monkeys.size(); i++) {
					std::cout << std::format("Monkey {} inspected items {} times\n", i, monkey_business[i]);
				}
				std::cout << "\n";
			}
		}

		for (int i = 0; i < monkeys.size(); i++) {
			monkey_business[i] += static_cast<long long>(monkeys[i].items.size());
			monkeys[i].execute_round(monkeys, false);
		}
	}
	if (print) {
		for (int i = 0; i < monkey_business.size(); i++) {
			std::cout << std::format("Monkey {} inspected items {} times\n", i, monkey_business[i]);
		}
	}
	std::sort(monkey_business.begin(), monkey_business.end(), std::greater<long long>());

	return monkey_business[0] * monkey_business[1];
}


int main() {
	std::vector<Monkey> monkeys;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_11\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", monkeys);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	start = std::chrono::high_resolution_clock::now();
	std::cout << "Monkey Business: \n" << part_1(monkeys, false) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Monkey Business 10000: \n" << part_2(monkeys, false) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";

}

