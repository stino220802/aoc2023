#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

void part1(std::vector<std::tuple<int, std::vector<int>, std::vector<int>>> cardDataVector);
void part2(std::vector<std::tuple<int, std::vector<int>, std::vector<int>>> cardDataVector);

int main() {

  std::ifstream inputFile("day4.txt");


  if (!inputFile.is_open()) {
	std::cerr << "Error opening file." << std::endl;
	return 1;
  }

  std::string line;
  std::vector<std::tuple<int, std::vector<int>, std::vector<int>>> cardDataVector;

  while (std::getline(inputFile, line)) {
	std::istringstream iss(line);
	std::tuple<int, std::vector<int>, std::vector<int>> cardData;
	std::string cardLabel, separator;
	iss >> cardLabel >> std::get<0>(cardData) >> separator;
	int number;
	std::string temp;
	bool sep = false;
	while (iss >> temp) {
	  if (temp == "|") {
		sep = true;
	  } else if (sep == false) {
		number = stoi(temp);
		std::get<1>(cardData).push_back(number);
	  } else if (sep == true) {
		number = stoi(temp);
		std::get<2>(cardData).push_back(number);
	  }
	}
	cardDataVector.push_back(cardData);
  }
  inputFile.close();
  part1(cardDataVector);
  part2(cardDataVector);

  return 0;
}
void part1(std::vector<std::tuple<int, std::vector<int>, std::vector<int>>> cardDataVector) {
  std::vector<int> points;
  for (auto n : cardDataVector) {
	int countWinnings = 0;
	for (int two : std::get<1>(n)) {
	  for (int num : std::get<2>(n)) {
		if (two == num) {
		  if (countWinnings == 0) {
			countWinnings = 1;
		  } else {
			countWinnings = countWinnings * 2;
		  }
		}
	  }
	}
	if (countWinnings != 0) {
	  points.push_back(countWinnings);
	}
  }
  int total = 0;
  for (auto n : points) {
	total = n + total;
  }
  std::cout << total << std::endl;
}
void part2(std::vector<std::tuple<int, std::vector<int>, std::vector<int>>> cardDataVector) {
  std::vector<std::pair<int, int>> cards;
  std::vector<std::tuple<int, int, int>> cards2;
  for (auto n : cardDataVector) {
	int countWinnings = 0;
	for (int two : std::get<1>(n)) {
	  for (int num : std::get<2>(n)) {
		if (two == num) {
		  countWinnings += 1;
		}
	  }
	}
	std::tuple<int, int, int> temp;
	std::get<1>(temp) = countWinnings;
	std::get<0>(temp) = std::get<0>(n);
	std::get<2>(temp) = 1;
	cards2.push_back(temp);
  }
  for (auto n : cards2) {
	if (std::get<1>(n) != 0) {
	  for (int i = 0; i < std::get<2>(n); i++) {
		for (int j = 0; j < std::get<1>(n); j++) {
		  int targetCard = 0;
		  targetCard = std::get<0>(n) + j;
		  std::get<2>(cards2[targetCard]) += 1;
		}
	  }
	}
  }
  int counter = 0;
  for (auto n : cards2) {

	counter += std::get<2>(n);
  }
  std::cout << counter << std::endl;
}
