#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <string_view>
#include <array>
#include <map>
#include <sstream>
#include <regex>
#include <numeric>

void part1(std::vector<std::string> cal);
void part2(std::vector<std::string> cal);

int main() {

  std::vector<std::string> cal;
  std::ifstream input("day1.txt");
  if (input.fail()) std::cout << "Failed to open file";
  else {
	while (input.peek() != EOF) {
	  std::string test;
	  input >> test;
	  cal.push_back(test);
	}
  }

  part1(cal);
  part2(cal);
  return 0;
}

void part1(std::vector<std::string> cal) {
  int total = 0;
  for (const auto &str : cal) {
	int firstnum = 0;
	int secondnum = 0;
	for (const auto &ch : str) {
	  if (std::isdigit(ch)) {
		if (firstnum == 0) {
		  firstnum = ch - '0';
		}
		secondnum = ch - '0';
	  }
	}
	firstnum = firstnum * 10;
	total = firstnum + secondnum + total;
  }
  std::cout << total << std::endl;
}
void part2(std::vector<std::string> cal) {
  int temp = 0;
  std::vector<std::vector<int>> numbers;
  for (const auto &str : cal) {

	for (int i = 0; i < str.size(); i++) {
	  if (str[i] == 'o' || str[i] == 't' || str[i] == 'f' || str[i] == 's' || str[i] == 'e' || str[i] == 'n') {
		if (str.substr(i, 3) == "one") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(1);

		} else if (str.substr(i, 3) == "two") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(2);

		} else if (str.substr(i, 5) == "three") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(3);

		} else if (str.substr(i, 4) == "four") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(4);

		} else if (str.substr(i, 4) == "five") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(5);

		} else if (str.substr(i, 3) == "six") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(6);

		} else if (str.substr(i, 5) == "seven") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(7);

		} else if (str.substr(i, 5) == "eight") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(8);

		} else if (str.substr(i, 4) == "nine") {
		  if (temp >= numbers.size()) {
			numbers.resize(temp + 1);
		  }
		  numbers[temp].emplace_back(9);

		}
	  } else if (std::isdigit(str[i])) {
		if (temp >= numbers.size()) {
		  numbers.resize(temp + 1);
		}
		numbers[temp].emplace_back(str[i] - '0');
	  }
	}
	temp++;
  }
  int total = 0;

  for (const auto &row : numbers) {
	int first = 0;
	int second = 0;
	for (int value : row) {
	  if (first == 0) {
		first = value;
	  }

	  second = value;

	}
	first = first * 10;
	total = first + second + total;
  }
  std::cout << total << std::endl;
}





