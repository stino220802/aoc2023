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

#define factor 1000000-1

void part1(std::vector<std::vector<char>> pattern);
void part2(std::vector<std::vector<char>> pattern);
std::vector<std::vector<char>> rotateClockwise(const std::vector<std::vector<char>> &matrix);
std::vector<std::vector<char>> rotateCounterclockwise(const std::vector<std::vector<char>> &matrix);
std::vector<std::vector<char>> transpose(const std::vector<std::vector<char>> &matrix);

int main() {

  std::ifstream inputFile("day11.txt");

  if (!inputFile.is_open()) {
	std::cerr << "Failed to open the file." << std::endl;
	return 1;
  }

  std::vector<std::vector<char>> pattern;
  std::string line;
  while (std::getline(inputFile, line)) {
	std::vector<char> row(line.begin(), line.end());
	pattern.push_back(row);
  }

  inputFile.close();

  part1(pattern);
  part2(pattern);

  return 0; // Return success
}
void part1(std::vector<std::vector<char>> pattern) {
  std::vector<std::vector<char>> expanded;
  std::vector<std::vector<char>> temp;
  int count1 = 0;
  for (auto i : pattern) {
	bool symbol = false;
	for (auto j : i) {
	  if (j == '#') {
		symbol = true;
	  }
	}
	if (symbol == true) {
	  expanded.push_back(i);
	} else {
	  count1++;
	  expanded.push_back(i);
	  expanded.push_back(i);
	}
  }
  int count2 = 0;
  std::vector<std::vector<char>> rotatedClockwise = rotateClockwise(expanded);
  std::vector<std::vector<char>> expanded2;
  for (auto i : rotatedClockwise) {
	bool symbol = false;
	for (auto j : i) {
	  if (j == '#') {
		symbol = true;
	  }
	}
	if (symbol == true) {
	  expanded2.push_back(i);
	} else {
	  count2++;
	  expanded2.push_back(i);
	  expanded2.push_back(i);

	}
  }
  std::vector<std::vector<char>> expanded3 = rotateCounterclockwise(expanded2);
  std::vector<std::pair<int, int>> coordinates;
  int count = 0;
  for (size_t i = 0; i < expanded3.size(); ++i) {
	for (size_t j = 0; j < expanded3[i].size(); ++j) {
	  if (expanded3[i][j] == '#') {
		coordinates.push_back(std::make_pair(i, j));
	  }
	}
  }

  int total = 0;
  for (size_t i = 0; i < coordinates.size() - 1; ++i) {
	for (size_t j = i + 1; j < coordinates.size(); ++j) {
	  int a = std::abs(coordinates[j].first - coordinates[i].first);
	  int b = std::abs(coordinates[j].second - coordinates[i].second);
	  int c = a + b;
	  total += c;
	}
  }
  std::cout << total << std::endl;
}

void part2(std::vector<std::vector<char>> pattern) {

  std::vector<std::vector<char>> expanded;
  std::vector<std::vector<char>> temp;
  int count1 = 0;
  std::vector<int> rows;
  for (auto i : pattern) {
	bool symbol = false;
	for (auto j : i) {
	  if (j == '#') {
		symbol = true;
	  }
	}
	if (symbol == true) {
	  expanded.push_back(i);
	} else {
	  rows.push_back(count1);
	  expanded.push_back(i);
	}
	count1++;

  }

  int count2 = 0;
  std::vector<int> cols;
  std::vector<std::vector<char>> rotatedClockwise = rotateClockwise(expanded);
  std::vector<std::vector<char>> expanded2;
  for (auto i : rotatedClockwise) {
	bool symbol = false;
	for (auto j : i) {
	  if (j == '#') {
		symbol = true;
	  }
	}
	if (symbol == true) {
	  expanded2.push_back(i);
	} else {
	  cols.push_back(count2);
	  expanded2.push_back(i);
	}
	count2++;
  }

  std::vector<std::vector<char>> expanded3 = rotateCounterclockwise(expanded2);

  std::vector<std::pair<int, int>> coordinates;
  int count = 0;
  for (size_t i = 0; i < expanded3.size(); ++i) {
	for (size_t j = 0; j < expanded3[i].size(); ++j) {
	  if (expanded3[i][j] == '#') {

		coordinates.push_back(std::make_pair(i, j));
	  }
	}
  }

  long long total = 0;

  for (size_t i = 0; i < coordinates.size() - 1; ++i) {
	for (size_t j = i + 1; j < coordinates.size(); ++j) {
	  long long a = std::abs(coordinates[j].first - coordinates[i].first);
	  long long b = std::abs(coordinates[j].second - coordinates[i].second);
	  long long c = 0;

	  for (int q = std::min(coordinates[i].first, coordinates[j].first);
		   q <= std::max(coordinates[i].first, coordinates[j].first); ++q) {
		for (auto r : rows) {
		  if (r == q) {
			c += factor;

		  }
		}
	  }
	  for (int q = std::min(coordinates[i].second, coordinates[j].second);
		   q <= std::max(coordinates[i].second, coordinates[j].second); ++q) {
		for (auto r : cols) {
		  if (r == q) {
			c += factor;

		  }
		}
	  }
	  c += a + b;
	  total += c;
	}
  }
  std::cout << total << std::endl;
}

std::vector<std::vector<char>> transpose(const std::vector<std::vector<char>> &matrix) {
  std::vector<std::vector<char>> result(matrix[0].size(), std::vector<char>(matrix.size(), '.'));

  for (size_t i = 0; i < matrix.size(); ++i) {
	for (size_t j = 0; j < matrix[i].size(); ++j) {
	  result[j][i] = matrix[i][j];
	}
  }

  return result;
}

std::vector<std::vector<char>> rotateClockwise(const std::vector<std::vector<char>> &matrix) {
  std::vector<std::vector<char>> transposed = transpose(matrix);

  for (auto &row : transposed) {
	std::reverse(row.begin(), row.end());
  }

  return transposed;
}

std::vector<std::vector<char>> rotateCounterclockwise(const std::vector<std::vector<char>> &matrix) {
  std::vector<std::vector<char>> transposed = transpose(matrix);
  std::reverse(transposed.begin(), transposed.end());

  return transposed;
}