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
#include <deque>

void part1(std::vector<std::string> tokens);
void part2(std::vector<std::string> tokens);
int hashFunc(char i, int total);
int main() {
  std::ifstream file("day15.txt");
  if (!file.is_open()) {
	std::cerr << "Error opening file." << std::endl;
	return 1;
  }
  
  std::string line;
  std::getline(file, line);

  file.close();

  std::vector<std::string> tokens;
  std::stringstream ss(line);
  std::string token;
  while (std::getline(ss, token, ',')) {
	tokens.push_back(token);
  }

  auto start = std::chrono::high_resolution_clock::now();
  part1(tokens);
  part2(tokens);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  return 0;
}

void part1(std::vector<std::string> tokens) {
  long long total = 0;
  for (const auto &str : tokens) {
	int current = 0;
	for (int i = 0; i < str.size(); i++) {
	  current = current + static_cast<int>(str[i]);
	  current *= 17;
	  current %= 256;
	}
	total += current;

  }
  std::cout << "total = " << total << std::endl;
}
void part2(std::vector<std::string> tokens) {
  std::vector<std::deque<std::pair<std::string, int>>> hel{256};
  for (const auto &str : tokens) {
	int hash = 0;
	std::string temp;
	for (int i = 0; i < str.size(); i++) {
	  if (str[i] == '=') {
		bool checker = false;
		if (!hel[hash].empty()) {
		  for (int j = 0; j < hel[hash].size(); j++) {
			if (hel[hash][j].first == temp) {
			  hel[hash][j].second = str[i + 1] - '0';
			  checker = true;
			  break;
			}
		  }
		}
		if (!checker) {
		  std::pair<std::string, int> tempPair;
		  tempPair.first = temp;
		  tempPair.second = str[i + 1] - '0';
		  hel[hash].push_back(tempPair);
		  break;
		}
	  } else if (str[i] == '-') {
		if (!hel[hash].empty()) {
		  for (int j = 0; j < hel[hash].size(); j++) {
			if (hel[hash][j].first == temp) {
			  hel[hash].erase(hel[hash].begin() + j);
			  break;
			}
		  }
		} else {
		  break;
		}

	  } else {
		temp.push_back(str[i]);
		hash = hashFunc(str[i], hash);

	  }
	}
  }
  long long total = 0;
  for (int i = 0; i < hel.size(); ++i) {
	if (!hel[i].empty()) {

	  for (int j = 0; j < hel[i].size(); j++) {
		total += ((i + 1) * (j + 1) * hel[i][j].second);
	  }
	}
  }
  std::cout << "Total = " << total << std::endl;
}

int hashFunc(char i, int total) {
  total += static_cast<int>(i);
  total *= 17;
  total %= 256;

  return total;
}