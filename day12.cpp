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
#include <cmath>

struct ConfigHash {
  std::size_t operator()(const std::pair<std::vector<char>, std::vector<int>> &config) const {
	std::size_t seed = 0;

	for (const char &c : config.first) {
	  seed ^= std::hash<char>()(c) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	for (const int &i : config.second) {
	  seed ^= std::hash<int>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
  }
};
long long recursion(std::vector<char> &characters,
					std::vector<int> &numbers,
					std::unordered_map<std::pair<std::vector<char>, std::vector<int>>,
									   long long,
									   ConfigHash> &memoization);
std::vector<int> countHash(const std::vector<char> &sequence);
void part1(std::vector<std::vector<char>> characters, std::vector<std::vector<int>> numbers);
void part2(std::vector<std::vector<char>> characters, std::vector<std::vector<int>> numbers);

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

	std::istringstream iss(line);
	char c;
	while (iss >> c) {
	  if (std::isdigit(c)) {

		int num;
		iss.unget();
		iss >> num;
		nums.push_back(num);
	  } else if (c != ',' && c != ' ') {
		chars.push_back(c);
	  }
	}

	characters.push_back(chars);
	numbers.push_back(nums);
  }

  file.close();


  part1(characters, numbers);
  auto start = std::chrono::high_resolution_clock::now();
  part2(characters, numbers);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  return 0;
}
void part1(std::vector<std::vector<char>> characters, const std::vector<std::vector<int>> numbers) {
  long long total = 0;
  for (size_t i = 0; i < characters.size(); ++i) {
	int countU = 0;
	std::vector<int> questionIndices;
	for (size_t j = 0; j < characters[i].size(); ++j) {
	  if (characters[i][j] == '?') {
		countU++;
		questionIndices.push_back(j);
	  }
	}

	int numCombinations = 1 << countU;

	for (int j = 0; j < numCombinations; ++j) {

	  for (int k = 0; k < countU; ++k) {
		int index = questionIndices[k];
		characters[i][index] = ((j >> k) & 1) ? '#' : '.';
	  }
	  std::vector<int> occurrences = countHash(characters[i]);

	  if (occurrences == numbers[i]) {
		total++;
	  }
	}

  }
  std::cout << total << std::endl;
}

std::vector<int> countHash(const std::vector<char> &sequence) {
  std::vector<int> counts;
  int count = 0;

  for (char c : sequence) {
	if (c == '#') {
	  count++;
	} else {
	  if (count > 0) {
		counts.push_back(count);
		count = 0;
	  }
	}
  }

  if (count > 0) {
	counts.push_back(count);
  }

  return counts;
}

void part2(std::vector<std::vector<char>> characters, std::vector<std::vector<int>> numbers) {
  std::unordered_map<std::pair<std::vector<char>, std::vector<int>>, long long, ConfigHash> memoization;
  long long total = 0;
  int unfoldings = 5;
  for (int i = 0; i < characters.size(); i++) {

	std::vector<char> unfolded_char(characters[i]);
	std::vector<int> unfolded_num(numbers[i]);
	unfolded_char.push_back('?');

	for (int j = 1; j < unfoldings; ++j) {

	  unfolded_char.insert(unfolded_char.end(), characters[i].begin(), characters[i].end());
	  unfolded_char.push_back('?');
	  unfolded_num.insert(unfolded_num.end(), numbers[i].begin(), numbers[i].end());
	}
	unfolded_char.pop_back();

	total += recursion(unfolded_char, unfolded_num, memoization);

  }

  std::cout << total << std::endl;
}
long long recursion(std::vector<char> &characters,
					std::vector<int> &numbers,
					std::unordered_map<std::pair<std::vector<char>, std::vector<int>>,
									   long long,
									   ConfigHash> &memoization) {

  std::pair<std::vector<char>, std::vector<int>> key = {characters, numbers};

  std::size_t hashValue = ConfigHash()(key);

  if (memoization.find(key) != memoization.end()) {

	return memoization[key];
  }
  if (characters.size() == 0) {
	if (numbers.size() == 0) {

	  return 1;
	} else {

	  return 0;
	}
  }
  if (numbers.empty()) {
	auto it = std::find(characters.begin(), characters.end(), '#');
	if (it != characters.end()) {
	  return 0;
	} else {
	  return 1;
	}
  }
  long long result = 0;
  if (characters[0] == '.' || characters[0] == '?') {

	std::vector<char> temp(characters.begin() + 1, characters.end());

	result += recursion(temp, numbers, memoization);
  }
  if (characters[0] == '#' || characters[0] == '?') {

	if (numbers[0] <= characters.size()) {
	  if (std::find(characters.begin(), characters.begin() + numbers[0], '.') == characters.begin() + numbers[0]) {
		if (numbers[0] == characters.size()) {
		  if (numbers[0] - characters.size() == 0) {
			if (numbers.size() <= 1) {
			  std::vector<int> tmpnum;
			  numbers = tmpnum;
			} else {
			  std::vector<int> tmpnum(numbers.begin() + 1, numbers.end());
			}
			std::vector<char> tempstr;
			characters = tempstr;
			result += recursion(characters, numbers, memoization);
		  } else {

			std::vector<char> tempChar(characters.begin() + numbers[0] + 1, characters.end());
			std::vector<int> tempNum(numbers.begin() + 1, numbers.end());

			result += recursion(tempChar, tempNum, memoization);

		  }

		}
		if (characters[numbers[0]] != '#' && !characters.empty()) {
		  std::vector<char> tempChar(characters.begin() + numbers[0] + 1, characters.end());
		  if (numbers.size() != 0) {
			std::vector<int> tempNum(numbers.begin() + 1, numbers.end());
			result += recursion(tempChar, tempNum, memoization);
		  } else {
			std::vector<int> tempNum;
			result += recursion(tempChar, tempNum, memoization);
		  }

		}
	  }

	}
  }

  memoization[key] = result;
  return result;
}

