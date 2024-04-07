#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype> // for std::isdigit
#include <algorithm>
#include <utility>
#include <map>
#include <unordered_map>
#include <iterator>
#include <memory>
#include <iomanip>
#include <cstddef>
#include <array>
#include <regex>
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>

int main() {

  std::ifstream file("day12.txt");
  if (!file.is_open()) {
	std::cerr << "Error opening file." << std::endl;
	return 1;
  }

  std::vector<std::vector<char>> characters;
  std::vector<std::vector<int>> numbers;

  std::string line;
  while (std::getline(file, line)) {

	std::vector<char> chars;

	std::vector<int> nums;

	for (char c : line) {

	  if (std::isdigit(c)) {

		nums.push_back(c - '0');
	  } else if (c != ',' && c != ' ') {

		chars.push_back(c);
	  }
	}

	characters.push_back(chars);
	numbers.push_back(nums);
  }

  file.close();

  for (size_t i = 0; i < characters.size(); ++i) {
	std::cout << "Characters: ";
	for (char c : characters[i]) {
	  std::cout << c << " ";
	}
	std::cout << std::endl;

	std::cout << "Numbers: ";
	for (int num : numbers[i]) {
	  std::cout << num << " ";
	}
	std::cout << std::endl << std::endl;
  }

  return 0;
}