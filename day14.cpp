#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
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

#define cycles 1000000000

void rotateGrid(std::vector<std::vector<char>> &grid);
void rotateGridBack(std::vector<std::vector<char>> &grid);
void part1(std::vector<std::vector<char>> grid);
void part2(std::vector<std::vector<char>> grid);

int main() {

  std::ifstream file("day14.txt");
  if (!file.is_open()) {
	std::cerr << "Error opening file." << std::endl;
	return 1;
  }

  std::vector<std::vector<char>> grid;
  std::string line;
  while (std::getline(file, line)) {
	std::vector<char> row(line.begin(), line.end());
	grid.push_back(row);
  }

  file.close();
  auto start = std::chrono::high_resolution_clock::now();

  part1(grid);
  part2(grid);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  return 0;
}

void part1(std::vector<std::vector<char>> grid) {
  rotateGrid(grid);

  int rows = grid.size();
  int cols = grid[0].size();

  for (int i = 0; i < rows; ++i) {
	for (int j = cols - 2; j >= 0; --j) {
	  if (grid[i][j] == 'O') {
		int k = j + 1;
		while (k < cols && grid[i][k] == '.') {
		  std::swap(grid[i][k], grid[i][k - 1]);
		  ++k;
		}
	  }
	}
  }
  rotateGridBack(grid);
  long long total = 0;
  rows = grid.size();
  cols = grid[0].size();
  for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
	  if (grid[i][j] == 'O') {
		long long temp = cols - i;
		total += temp;
	  }
	}
  }
  std::cout << "Total = " << total << std::endl;
}
void part2(std::vector<std::vector<char>> grid) {
  std::map<std::vector<std::vector<char>>, int> grid_cycle_map;
  int cycle_count = 0;
  bool cycle_detected = false;
  for (int c = 0; c < cycles; c++) {
	if (grid_cycle_map.find(grid) != grid_cycle_map.end()) {

	  cycle_detected = true;
	  cycle_count = c - grid_cycle_map[grid];
	  break;
	}

	grid_cycle_map[grid] = c;

	rotateGrid(grid);
	int rows = grid.size();
	int cols = grid[0].size();

	for (int i = 0; i < rows; ++i) {
	  for (int j = cols - 2; j >= 0; --j) {
		if (grid[i][j] == 'O') {
		  int k = j + 1;
		  while (k < cols && grid[i][k] == '.') {
			std::swap(grid[i][k], grid[i][k - 1]);
			++k;
		  }
		}
	  }
	}
	rotateGrid(grid);
	rows = grid.size();
	cols = grid[0].size();
	for (int i = 0; i < rows; ++i) {
	  for (int j = cols - 2; j >= 0; --j) {
		if (grid[i][j] == 'O') {
		  int k = j + 1;
		  while (k < cols && grid[i][k] == '.') {
			std::swap(grid[i][k], grid[i][k - 1]);
			++k;
		  }
		}
	  }
	}
	rotateGrid(grid);
	rows = grid.size();
	cols = grid[0].size();
	for (int i = 0; i < rows; ++i) {
	  for (int j = cols - 2; j >= 0; --j) {
		if (grid[i][j] == 'O') {
		  int k = j + 1;
		  while (k < cols && grid[i][k] == '.') {
			std::swap(grid[i][k], grid[i][k - 1]);
			++k;
		  }
		}
	  }
	}
	rotateGrid(grid);
	rows = grid.size();
	cols = grid[0].size();
	for (int i = 0; i < rows; ++i) {
	  for (int j = cols - 2; j >= 0; --j) {
		if (grid[i][j] == 'O') {
		  int k = j + 1;
		  while (k < cols && grid[i][k] == '.') {
			std::swap(grid[i][k], grid[i][k - 1]);
			++k;
		  }
		}
	  }
	}
  }

  if (cycle_detected) {
	for (const auto &entry : grid_cycle_map) {
	  if (entry.second == ((cycles - (cycle_count + grid_cycle_map[grid])) % cycle_count)
		  + (cycle_count + grid_cycle_map[grid] - cycle_count)) {
		long long total = 0;
		int rows = entry.first.size();
		int cols = entry.first[0].size();
		for (int i = 0; i < rows; i++) {
		  for (int j = 0; j < cols; j++) {
			if (entry.first[i][j] == 'O') {
			  long long temp = cols - i;
			  total += temp;
			}
		  }
		}
		std::cout << "Total = " << total << std::endl;
		break;
	  }
	}

  }
}

void rotateGrid(std::vector<std::vector<char>> &grid) {

  std::vector<std::vector<char>> transposed(grid[0].size(), std::vector<char>(grid.size()));
  for (size_t i = 0; i < grid.size(); ++i) {
	for (size_t j = 0; j < grid[0].size(); ++j) {
	  transposed[j][i] = grid[i][j];
	}
  }
  for (auto &row : transposed) {
	std::reverse(row.begin(), row.end());
  }
  grid = std::move(transposed);
}

void rotateGridBack(std::vector<std::vector<char>> &grid) {

  std::vector<std::vector<char>> transposed(grid[0].size(), std::vector<char>(grid.size()));
  for (size_t i = 0; i < grid.size(); ++i) {
	for (size_t j = 0; j < grid[0].size(); ++j) {
	  transposed[grid[0].size() - 1 - j][i] = grid[i][j];
	}
  }
  grid = std::move(transposed);
}
