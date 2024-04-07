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
#define red 12
#define green 13
#define blue 14

void part1(std::vector<std::pair<int, std::pair<std::string, int>>> gameData);
void part2(std::vector<std::pair<int, std::pair<std::string, int>>> gameData);
int main() {
  std::ifstream inputFile("day2.txt");
  if (!inputFile.is_open()) {
	std::cerr << "Error opening file.\n";
	return 1;
  }

  std::vector<std::pair<int, std::pair<std::string, int>>> gameData;
  std::vector<std::pair<int, std::pair<std::string, int>>> gameData2;
  std::string line;
  while (std::getline(inputFile, line)) {

	size_t pos = line.find(":");
	if (pos != std::string::npos) {
	  int gameID = std::stoi(line.substr(5, pos - 5)); // Extract the game number

	  std::istringstream gameStream(line.substr(pos + 2));
	  std::string token;
	  while (std::getline(gameStream, token, ';')) {
		std::istringstream colorStream(token);
		int quantity;
		std::string color;

		while (colorStream >> quantity >> color) {
		  gameData.emplace_back(gameID, std::make_pair(color, quantity));
		}
	  }
	}
  }

  gameData2 = gameData;
  part1(gameData);
  part2(gameData2);
  inputFile.close();
  return 0;
}

void part1(std::vector<std::pair<int, std::pair<std::string, int>>> gameData) {
  int total = 0;
  int id = 0;
  std::vector<int> wrong;
  for (const auto &entry : gameData) {

	if (entry.second.first == "blue" || entry.second.first == "blue,") {

	  if (entry.second.second > blue) {
		if (id != entry.first) {
		  wrong.emplace_back(entry.first);
		  id = entry.first;
		}
	  }
	}
	if (entry.second.first == "green" || entry.second.first == "green,") {

	  if (entry.second.second > green) {
		if (id != entry.first) {
		  wrong.emplace_back(entry.first);
		  id = entry.first;

		}
	  }
	}
	if (entry.second.first == "red" || entry.second.first == "red,") {

	  if (entry.second.second > red) {
		if (id != entry.first) {

		  wrong.emplace_back(entry.first);
		  id = entry.first;
		}
	  }
	}

  }
  gameData.erase(std::remove_if(gameData.begin(), gameData.end(), [&wrong](const auto &elem) {
	return std::find(wrong.begin(), wrong.end(), elem.first) != wrong.end();
  }), gameData.end());

  int id2 = 0;
  total = 0;
  for (const auto &data : gameData) {
	if (data.first != id2) {
	  total += data.first;
	  id2 = data.first;
	}
  }
  std::cout << total << std::endl;
}
struct game {
  int cblue;
  int cred;
  int cgreen;
};
void part2(std::vector<std::pair<int, std::pair<std::string, int>>> gameData) {

  int maxGameID = 0;

  for (const auto &loop : gameData) {
	maxGameID = std::max(maxGameID, loop.first);
  }

  std::vector<game> min(maxGameID + 1);

  int curId = 0;
  int curBlue = 0;
  int curRed = 0;
  int curGreen = 0;
  for (auto &loop : gameData) {
	if (loop.first != curId) {
	  min[curId].cblue = curBlue;
	  min[curId].cred = curRed;
	  min[curId].cgreen = curGreen;
	  curGreen = 0;
	  curRed = 0;
	  curBlue = 0;
	  curId = loop.first;
	}
	if (loop.second.first == "blue" || loop.second.first == "blue,") {
	  curBlue = (loop.second.second > curBlue ? loop.second.second : curBlue);
	}
	if (loop.second.first == "green" || loop.second.first == "green,") {
	  curGreen = (loop.second.second > curGreen ? loop.second.second : curGreen);
	}
	if (loop.second.first == "red" || loop.second.first == "red,") {
	  curRed = (loop.second.second > curRed ? loop.second.second : curRed);
	}
  }
  min[maxGameID].cblue = curBlue;
  min[maxGameID].cgreen = curGreen;
  min[maxGameID].cred = curRed;

  int total = 0;
  for (size_t i = 1; i < min.size() + 1; ++i) {
	total = total + min[i].cblue * min[i].cgreen * min[i].cred;

  }
  std::cout << total << std::endl;
}





