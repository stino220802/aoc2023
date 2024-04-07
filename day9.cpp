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

void part1(std::vector<std::vector<int>> data);
void part2(std::vector<std::vector<int>> data);
bool zeroCheck(std::vector<std::vector<int>> temp);

bool zeroCheck(std::vector<std::vector<int>> temp) {
  int size = temp.size();
  for (auto &i : temp[size - 1]) {
	if (i != 0) {
	  return true;
	}
  }
  return false;
}

int main() {
  std::string filename = "day9.txt";
  std::vector<std::vector<int>> data;

  std::ifstream file(filename);
  if (file.is_open()) {
	std::string line;
	while (std::getline(file, line)) {
	  std::vector<int> row;
	  std::istringstream iss(line);
	  int num;
	  while (iss >> num) {
		row.push_back(num);
	  }
	  data.push_back(row);
	}
	file.close();
  } else {
	std::cerr << "Unable to open file: " << filename << std::endl;
  }
  part1(data);
  part2(data);
  return 0;
}

void part1(std::vector<std::vector<int>> data) {
  long long results = 0;

  for (auto &i : data) {
	std::vector<std::vector<int>> temp;
	std::vector<int> t;

	for (auto &j : i) {
	  t.push_back(j);
	}
	temp.push_back(t);
	do {
	  std::vector<int> te;

	  for (int g = 0; g < temp[temp.size() - 1].size() - 1; g++) {
		int u = temp[temp.size() - 1][g + 1] - temp[temp.size() - 1][g];
		te.push_back(u);
	  }
	  temp.push_back(te);
	} while (zeroCheck(temp));
	int p = 0;
	for (int g = temp.size() - 1; g > 0; g--) {
	  if (g == temp.size() - 1) {
		p = temp[g][temp[g].size() - 1] + temp[g - 1][temp[g - 1].size() - 2];
	  } else {
		p = p + temp[g - 1][temp[g - 1].size() - 1];

	  }

	}
	results = results + p;
  }
  std::cout << results << std::endl;
}

void part2(std::vector<std::vector<int>> data) {

  long long results = 0;

  for (auto &i : data) {
	std::vector<std::vector<int>> temp;
	std::vector<int> t;
	for (auto &j : i) {
	  t.push_back(j);
	}
	temp.push_back(t);

	do {
	  std::vector<int> te;

	  for (int g = 0; g < temp[temp.size() - 1].size() - 1; g++) {
		int u = temp[temp.size() - 1][g + 1] - temp[temp.size() - 1][g];
		te.push_back(u);
	  }
	  temp.push_back(te);
	} while (zeroCheck(temp));

	int p = 0;
	for (int g = temp.size() - 1; g > 0; g--) {
	  if (g == temp.size() - 1) {
		p = temp[g - 1][0] - temp[g][0];
	  } else {
		p = temp[g - 1][0] - p;
	  }
	}
	results = results + p;
  }
  std::cout << results << std::endl;
}

