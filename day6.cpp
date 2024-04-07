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

#include <functional>
void part1(std::vector<std::pair<int, int>> data);
long long concatenateIntegers(const std::vector<std::pair<int, int>> &data,
							  std::function<int(const std::pair<int, int> &)> getValue);
void part2(std::vector<std::pair<int, int>> data);
long long concatenateIntegers(const std::vector<std::pair<int, int>> &data,
							  std::function<int(const std::pair<int, int> &)> getValue) {
  std::vector<int> numbers;
  for (const auto &pair : data) {
	numbers.push_back(getValue(pair));
  }
  std::string combinedStr;
  for (int num : numbers) {
	combinedStr += std::to_string(num);
  }
  long long combinedInt = std::stoll(combinedStr);
  return combinedInt;
}
int main() {
  std::vector<std::pair<int, int>> data;

  std::ifstream inputFile("day6.txt");

  if (inputFile.is_open()) {
	std::string line;

	while (std::getline(inputFile, line)) {
	  if (line.find("Time:") != std::string::npos) {
		std::istringstream timeStream(line.substr(6));
		int time;

		while (timeStream >> time) {
		  data.push_back(std::make_pair(time, 0));
		}
	  } else if (line.find("Distance:") != std::string::npos) {
		std::istringstream distanceStream(line.substr(10));
		int distance;

		for (auto &pair : data) {
		  distanceStream >> distance;
		  pair.second = distance;
		}
	  }
	}

	inputFile.close();
  } else {
	std::cerr << "Error opening file" << std::endl;
	return 1;
  }

  part1(data);
  part2(data);
  return 0;
}

void part1(std::vector<std::pair<int, int>> data) {
  std::vector<int> ways;
  for (auto n : data) {
	std::vector<int> pos;
	for (int i = 0; i < n.first; i++) {
	  int traveltime = n.first - i;

	  if (traveltime * i > n.second) {
		pos.push_back(traveltime * i);
	  }
	}
	sort(pos.begin(), pos.end());

	ways.push_back(pos.size());
  }
  int countWays = 1;
  for (auto w : ways) {
	countWays = countWays * w;
  }
  std::cout << countWays << std::endl;
}
void part2(std::vector<std::pair<int, int>> data) {
  long long time, distance;
  // Implementation for part2 goes here
  long long counter = 0;
  time = concatenateIntegers(data, [](const auto &pair) { return pair.first; });
  distance = concatenateIntegers(data, [](const auto &pair) { return pair.second; });

  for (long long i = 0; i < time; i++) {
	int traveltime = time - i;
	if (traveltime * i > distance) {
	  counter++;
	}
  }
  std::cout << counter;
}
