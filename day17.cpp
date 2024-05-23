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

struct Point {
  int x;
  int y;
  int heat_loss;
  char direction;
  int steps_in_direction;
};

bool operator<(const Point &lhs, const Point &rhs) {
  return std::tie(lhs.x, lhs.y, lhs.direction, lhs.steps_in_direction) <
         std::tie(rhs.x, rhs.y, rhs.direction, rhs.steps_in_direction);
}
struct PointComparator {
  bool operator()(const Point &a, const Point &b) const {
    return a.heat_loss > b.heat_loss;
  }
};
void part1(std::vector<std::vector<int>> digits);
void part2(std::vector<std::vector<int>> digits);

int main() {
  std::ifstream file("day17.txt");

  if (!file.is_open()) {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }

  std::vector<std::vector<int>> digits;

  std::string line;
  while (std::getline(file, line)) {
    std::vector<int> lineDigits;

    for (char c : line) {
      lineDigits.push_back(c - '0');
    }

    digits.push_back(lineDigits);
  }

  file.close();

  auto start = std::chrono::high_resolution_clock::now();

  part1(digits);
  std::cout << "part2" << std::endl;
  part2(digits);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds"
            << std::endl;
  return 0;
}

void part1(std::vector<std::vector<int>> digits) {
  int start_x = 0;
  int start_y = 0;
  int end_x = digits.size() - 1;
  int end_y = digits[0].size() - 1;
  Point start = {0, 0, 0, 'R', 1};
  Point start2 = {0, 0, 0, 'D', 1};
  Point end = {end_x, end_y, digits[end.x][end.y]};
  // priorityqueue works, normal queue doesnt. Strange but not gonna look
  // further into it
  std::priority_queue<Point, std::vector<Point>, PointComparator> q;
  std::set<Point> map;
  q.push(start);
  Point bullshit = {2000000000, 2000000000, 2000000000, 'D', 2000000000};
  map.insert(bullshit);
  int max_heat_loss = 2000000000;
  while (!q.empty()) {
    Point current = q.top();
    q.pop();

    auto it = map.find(current);
    if (it != map.end()) {
      continue;
    }
    map.insert(current);
    if (current.x == end_x && current.y == end_y) {
      std::cout << "heatloss = " << current.heat_loss << std::endl;
    }

    if (current.direction == 'D') {
      current.x++;
    } else if (current.direction == 'U') {
      current.x--;
    } else if (current.direction == 'L') {
      current.y--;
    } else if (current.direction == 'R') {
      current.y++;
    }
    if (current.x >= 0 && current.x <= end_x && current.y >= 0 &&
        current.y <= end_y) {

      current.heat_loss += digits[current.y][current.x];
      if (current.steps_in_direction < 3) {
        current.steps_in_direction++;
        q.push(current);
      }
      if (current.steps_in_direction >= 1) {
        current.steps_in_direction = 1;
        char direction = current.direction;
        if (direction == 'D') {
          current.direction = 'L';
        } else if (direction == 'U') {
          current.direction = 'R';
        } else if (direction == 'R') {
          current.direction = 'D';
        } else if (direction == 'L') {
          current.direction = 'U';
        }

        q.push(current);
        if (direction == 'D') {
          current.direction = 'R';
        } else if (direction == 'U') {
          current.direction = 'L';
        } else if (direction == 'R') {
          current.direction = 'U';
        } else if (direction == 'L') {
          current.direction = 'D';
        }
        q.push(current);
      }
    } else {
      continue;
    }
  }
}

void part2(std::vector<std::vector<int>> digits) {
  int start_x = 0;
  int start_y = 0;
  int end_x = digits.size() - 1;
  int end_y = digits[0].size() - 1;
  Point start = {0, 0, 0, 'R', 1};
  Point start2 = {0, 0, 0, 'D', 1};
  Point end = {end_x, end_y, digits[end.x][end.y]};
  // priorityqueue works, normal queue doesnt. Strange but not gonna look
  // further into it
  std::priority_queue<Point, std::vector<Point>, PointComparator> q;
  std::set<Point> map;
  q.push(start);
  Point bullshit = {2000000000, 2000000000, 2000000000, 'D', 2000000000};
  map.insert(bullshit);
  int max_heat_loss = 2000000000;
  while (!q.empty()) {
    Point current = q.top();
    q.pop();

    auto it = map.find(current);
    if (it != map.end()) {
      continue;
    }
    map.insert(current);
    if (current.x == end_x && current.y == end_y) {
      std::cout << "heatloss = " << current.heat_loss << std::endl;
    }

    if (current.direction == 'D') {
      current.x++;
    } else if (current.direction == 'U') {
      current.x--;
    } else if (current.direction == 'L') {
      current.y--;
    } else if (current.direction == 'R') {
      current.y++;
    }
    if (current.x >= 0 && current.x <= end_x && current.y >= 0 &&
        current.y <= end_y) {

      current.heat_loss += digits[current.x][current.y];
      if (current.steps_in_direction < 10) {
        current.steps_in_direction++;
        q.push(current);
      }
      if (current.steps_in_direction >= 5) {
        current.steps_in_direction = 1;
        char direction = current.direction;
        if (direction == 'D') {
          current.direction = 'L';
        } else if (direction == 'U') {
          current.direction = 'R';
        } else if (direction == 'R') {
          current.direction = 'D';
        } else if (direction == 'L') {
          current.direction = 'U';
        }

        q.push(current);
        if (direction == 'D') {
          current.direction = 'R';
        } else if (direction == 'U') {
          current.direction = 'L';
        } else if (direction == 'R') {
          current.direction = 'U';
        } else if (direction == 'L') {
          current.direction = 'D';
        }
        q.push(current);
      }
    } else {
      continue;
    }
  }
}
