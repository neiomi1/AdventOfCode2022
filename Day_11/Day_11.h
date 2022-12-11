#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <deque>

#include <string>

struct Monkey {
    std::deque<long long> items;
    std::vector<std::string> operation;
    long long test;
    long long if_true;
    long long if_false;
    long long kgv;

    void execute_round(std::vector<Monkey>& monkeys, bool divide) {
        for (int i = 0; i < items.size();) {
            long long item = items.front();
            
            long long a = (operation[0] == "old") ? item : static_cast<long long>(std::stoi(operation[0]));
            long long b = (operation[2] == "old") ? item : static_cast<long long>(std::stoi(operation[2]));
            
            switch (operation[1][0]) {
            case '+': item = a + b; break;
            case '-': item = a - b; break;
            case '*': item = a * b; break;
            case '/': item = a / b; break;
            }

            if(divide)
                item /= 3;

            item %= kgv;

            if (item % test == 0)
                monkeys[if_true].items.push_back(item);
            else
                monkeys[if_false].items.push_back(item);
            items.pop_front();
        }

    }
};

inline void read_entries(const std::string& filename, std::vector<Monkey>& monkeys);

inline long long part_1(std::vector<Monkey>& monkeys, bool print);

inline long long part_2(std::vector<Monkey>& monkeys, bool print);