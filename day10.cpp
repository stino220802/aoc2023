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

void part1(std::vector<std::vector<char>> pattern);
void part2(std::vector<std::vector<char>> pattern);
int areaF(std::vector<std::pair<int, int>> corners);

int main() {

  std::ifstream inputFile("day10.txt");

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

  return 0;
}
void part1(std::vector<std::vector<char>> pattern) {

  int x, y = 0;
  for (int i = 0; i < pattern.size(); i++) {
	for (int j = 0; j < pattern[i].size(); j++) {
	  if (pattern[i][j] == 'S') {
		x = i;
		y = j;
	  }
	}
  }

  char prev = '0';
  char prev2 = '0';
  long long count = 0;

  for (;;) {

	if ((prev2 == 'J' || prev2 == 'L' || prev2 == '|' || prev2 == '0') && (prev != 'u' && x != 0
		&& (pattern[x - 1][y] == '|' || pattern[x - 1][y] == '7' || pattern[x - 1][y] == 'F'))) {

	  prev2 = pattern[x - 1][y];
	  x--;
	  prev = 'd';
	} else if ((prev2 == '|' || prev2 == '7' || prev2 == 'F' || prev2 == '0') && (prev != 'd' && x != pattern.size() - 1
		&& (pattern[x + 1][y] == '|' || pattern[x + 1][y] == 'L' || pattern[x + 1][y] == 'J'))) {
	  prev2 = pattern[x + 1][y];
	  x = x + 1;
	  prev = 'u';
	} else if ((prev2 == '7' || prev2 == 'J' || prev2 == '-' || prev2 == '0') && (prev != 'r' && y != 0
		&& (pattern[x][y - 1] == 'L' || pattern[x][y - 1] == '-' || pattern[x][y - 1] == 'F'))) {
	  prev2 = pattern[x][y - 1];
	  y--;
	  prev = 'l';
	} else if ((prev2 == '-' || prev2 == 'F' || prev2 == 'L' || prev2 == '0')
		&& (prev != 'l' && y != pattern[x].size() - 1
			&& (pattern[x][y + 1] == '-' || pattern[x][y + 1] == '7' || pattern[x][y + 1] == 'J'))) {
	  prev2 = pattern[x][y + 1];

	  y++;
	  prev = 'r';

	} else {
	  break;
	}
	count++;
  }
  count = count / 2;
  count++;
  std::cout << count << std::endl;
}
void part2(std::vector<std::vector<char>> pattern) {

  int x, y = 0;
  for (int i = 0; i < pattern.size(); i++) {
	for (int j = 0; j < pattern[i].size(); j++) {
	  if (pattern[i][j] == 'S') {
		x = i;
		y = j;
	  }
	}
  }

  std::vector<std::pair<int, int>> corners;
  std::vector<std::pair<int, int>> points;
  corners.push_back(std::make_pair(x, y));
  points.push_back(std::make_pair(x, y));

  char prev = '0';
  char prev2 = '0';
  long long count = 0;

  for (;;) {

	if ((prev2 == 'J' || prev2 == 'L' || prev2 == '|' || prev2 == '0') && (prev != 'u' && x != 0
		&& (pattern[x - 1][y] == '|' || pattern[x - 1][y] == '7' || pattern[x - 1][y] == 'F'))) {

	  prev2 = pattern[x - 1][y];
	  if (pattern[x - 1][y] == '7' || pattern[x - 1][y] == 'F') {
		corners.push_back(std::make_pair(x - 1, y));
	  }
	  points.push_back(std::make_pair(x - 1, y));
	  x--;
	  prev = 'd';
	} else if ((prev2 == '|' || prev2 == '7' || prev2 == 'F' || prev2 == '0') && (prev != 'd' && x != pattern.size() - 1
		&& (pattern[x + 1][y] == '|' || pattern[x + 1][y] == 'L' || pattern[x + 1][y] == 'J'))) {

	  prev2 = pattern[x + 1][y];
	  if (pattern[x + 1][y] == 'L' || pattern[x + 1][y] == 'J') {
		corners.push_back(std::make_pair(x + 1, y));
	  }
	  points.push_back(std::make_pair(x + 1, y));
	  x = x + 1;
	  prev = 'u';

	} else if ((prev2 == '7' || prev2 == 'J' || prev2 == '-' || prev2 == '0') && (prev != 'r' && y != 0
		&& (pattern[x][y - 1] == 'L' || pattern[x][y - 1] == '-' || pattern[x][y - 1] == 'F'))) {
	  prev2 = pattern[x][y - 1];
	  if (pattern[x][y - 1] == 'L' || pattern[x][y - 1] == 'F') {
		corners.push_back(std::make_pair(x, y - 1));
	  }
	  points.push_back(std::make_pair(x, y - 1));
	  y--;

	  prev = 'l';
	} else if ((prev2 == '-' || prev2 == 'F' || prev2 == 'L' || prev2 == '0')
		&& (prev != 'l' && y != pattern[x].size() - 1
			&& (pattern[x][y + 1] == '-' || pattern[x][y + 1] == '7' || pattern[x][y + 1] == 'J'))) {
	  prev2 = pattern[x][y + 1];
	  if (pattern[x][y + 1] == '7' || pattern[x][y + 1] == 'J') {
		corners.push_back(std::make_pair(x, y + 1));
	  }
	  points.push_back(std::make_pair(x, y + 1));
	  y++;
	  prev = 'r';

	} else {
	  break;
	}
	count++;
  }
  int area = areaF(corners);
  int interiorPoints = area - (points.size() / 2) + 1;
  std::cout << interiorPoints;
}

int areaF(std::vector<std::pair<int, int>> corners) {
  int area = 0;
  for (int i = 0; i < corners.size(); i++) {
	int j = (i + 1) % corners.size();
	area += (corners[i].first * corners[j].second) - (corners[j].first * corners[i].second);
  }
  area = abs(area) / 2.0;

  return area;
}


