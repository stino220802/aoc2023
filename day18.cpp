#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct pit {
  char direction;
  int distance;
  std::string color;
};
void part1(std::vector<pit> directions);
void part2(std::vector<pit> directions);
int areaF(std::vector<std::pair<int, int>> corners);
long long areaFLong(std::vector<std::pair<long long, long long>> corners);
int main() {

  std::ifstream inputFile("day18.txt");
  if (!inputFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  std::string line;
  std::vector<pit> directions;

  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    char direction;
    int distance;
    std::string color;

    if (iss >> direction >> distance >> color) {
      color = color.substr(1, color.length() - 2);
      directions.push_back({direction, distance, color});
    }
  }

  inputFile.close();

  auto start = std::chrono::high_resolution_clock::now();
  part1(directions);
  part2(directions);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds"
            << std::endl;
  return 0;
}

void part1(std::vector<pit> directions) {

  std::vector<std::pair<int, int>> corners;
  long long point = 0;
  int x = 0;
  int y = 0;
  corners.push_back({x, y});
  for (auto &t : directions) {
    if (t.direction == 'R') {
      y += t.distance;
      point += t.distance;
    } else if (t.direction == 'L') {
      y -= t.distance;
      point += t.distance;
    } else if (t.direction == 'U') {
      x -= t.distance;
      point += t.distance;
    } else if (t.direction == 'D') {
      x += t.distance;
      point += t.distance;
    }

    corners.push_back({x, y});
  }

  int area = areaF(corners);
  int interiorPoints = area - (point / 2) + 1;
  int total = interiorPoints + point;
  std::cout << "total = " << total << std::endl;
}

void part2(std::vector<pit> directions) {
  std::vector<std::pair<long long, long long>> corners;
  long long point = 0;
  long long x = 0;
  long long y = 0;
  corners.push_back({x, y});

  for (auto &t : directions) {
    long long dir = 1000;
    t.color.erase(0, 1);
    dir = t.color[t.color.size() - 1] - '0';
    t.color.erase(t.color.size() - 1, t.color.size());
    long long hex = std::stoi(t.color, nullptr, 16);
    if (dir == 0) {
      y += hex;
      point += hex;
    } else if (dir == 2) {
      y -= hex;
      point += hex;
    } else if (dir == 3) {
      x -= hex;
      point += hex;
    } else if (dir == 1) {
      x += hex;
      point += hex;
    }

    corners.push_back({x, y});
  }
  long long area = areaFLong(corners);
  long long interiorPoints = area - (point / 2) + 1;
  long long total = interiorPoints + point;
  std::cout << "total = " << total << std::endl;
}

int areaF(std::vector<std::pair<int, int>> corners) {
  int area = 0;
  for (int i = 0; i < corners.size(); i++) {
    int j = (i + 1) % corners.size();
    area += (corners[i].first * corners[j].second) -
            (corners[j].first * corners[i].second);
  }
  area = abs(area) / 2.0;

  return area;
}

long long areaFLong(std::vector<std::pair<long long, long long>> corners) {
  long long area = 0;
  for (long long i = 0; i < corners.size(); i++) {
    long long j = (i + 1) % corners.size();
    area += (corners[i].first * corners[j].second) -
            (corners[j].first * corners[i].second);
  }
  area = abs(area) / 2.0;

  return area;
}