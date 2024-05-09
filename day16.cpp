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

void part2(std::vector<std::vector<char>> grid);
int simulate(std::vector<std::vector<char>> &grid, int start_x, int start_y,
             char start_direction);
struct Beam {
  int x, y;
  char direction;
};
void part1(std::vector<std::vector<char>> grid);
bool beamWithinBounds(const Beam &beam,
                      const std::vector<std::vector<char>> &grid) {
  int height = grid.size();
  int width = grid[0].size();
  return 0 <= beam.x && beam.x < width && 0 <= beam.y && beam.y < height;
}
int main() {
  // Open the file
  std::ifstream file("day16.txt");
  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  std::vector<std::vector<char>> grid;
  std::string line;
  while (std::getline(file, line)) {
    std::vector<char> row;
    for (char c : line) {
      row.push_back(c);
    }
    grid.push_back(row);
  }
  file.close();

  auto start = std::chrono::high_resolution_clock::now();
  part1(grid);
  part2(grid);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds"
            << std::endl;
  return 0;
}
void part1(std::vector<std::vector<char>> grid) {
  std::vector<std::pair<int, int>> hist;
  int x = 0;
  int y = 0;
  char direction = 'R';
  int energizedTiles = simulate(grid, x, y, direction);
  std::cout << "tiles:" << energizedTiles << std::endl;
}

void part2(std::vector<std::vector<char>> grid) {
  int highest = 0;
  int x = 0;
  int y = 0;
  char direction = 'R';
  for (int i = 0; i < grid.size(); i++) {
    int energizedTiles = simulate(grid, i, y, direction);
    if (energizedTiles > highest) {
      highest = energizedTiles;
    }
  }
  y = grid[0].size() - 1;
  direction = 'L';
  for (int i = 0; i < grid.size(); i++) {
    int energizedTiles = simulate(grid, i, y, direction);
    if (energizedTiles > highest) {
      highest = energizedTiles;
    }
  }
  x = 0;
  y = 0;
  direction = 'D';
  for (int i = 0; i < grid[0].size(); i++) {
    int energizedTiles = simulate(grid, x, i, direction);
    if (energizedTiles > highest) {
      highest = energizedTiles;
    }
  }
  x = grid.size() - 1;
  y = 0;
  direction = 'U';
  for (int i = 0; i < grid[i].size(); i++) {
    int energizedTiles = simulate(grid, x, i, direction);
    if (energizedTiles > highest) {
      highest = energizedTiles;
    }
  }
  std::cout << highest;
}

int simulate(std::vector<std::vector<char>> &grid, int start_x, int start_y,
             char start_direction) {
  std::set<std::pair<int, int>> energizedTiles;
  std::queue<Beam> beamQueue;
  std::set<std::pair<int, int>> splitters;
  beamQueue.push({start_x, start_y, start_direction});

  while (!beamQueue.empty()) {
    Beam beam = beamQueue.front();
    beamQueue.pop();

    int x = beam.x;
    int y = beam.y;

    if (!beamWithinBounds(beam, grid)) {
      continue;
    }
    if (energizedTiles.count({x, y}) == 0) {
      energizedTiles.insert({x, y});
    }

    char current_tile = grid[beam.x][beam.y];
    if (current_tile == '.') {
      if (beam.direction == 'U') {
        beam.x--;
      } else if (beam.direction == 'D') {
        beam.x++;
      } else if (beam.direction == 'L') {
        beam.y--;
      } else if (beam.direction == 'R') {
        beam.y++;
      }
    } else if (current_tile == '/' || current_tile == '\\') {
      if (current_tile == '/') {
        if (beam.direction == 'R') {
          beam.direction = 'U';
          beam.x--;
        } else if (beam.direction == 'L') {
          beam.direction = 'D';
          beam.x++;
        } else if (beam.direction == 'U') {
          beam.direction = 'R';
          beam.y++;
        } else if (beam.direction == 'D') {
          beam.direction = 'L';
          beam.y--;
        }
      } else if (current_tile == '\\') {
        if (beam.direction == 'L') {
          beam.direction = 'U';
          beam.x--;
        } else if (beam.direction == 'R') {
          beam.direction = 'D';
          beam.x++;
        } else if (beam.direction == 'U') {
          beam.direction = 'L';
          beam.y--;
        } else if (beam.direction == 'D') {
          beam.direction = 'R';
          beam.y++;
        }
      }
    } else if (current_tile == '|') {
      if (splitters.count({x, y}) != 0) {
        continue;
      }

      splitters.insert({x, y});

      if (beam.direction == 'U' || beam.direction == 'D') {
        if (beam.direction == 'U') {
          beam.x--;
        } else {
          beam.x++;
        }
      } else {
        beam.direction = 'U';
        beam.x--;
        beamQueue.push(beam);
        beam.direction = 'D';
        beam.x++;
        beam.x++;
        beamQueue.push(beam);
        continue;
      }
    } else if (current_tile == '-') {
      if (splitters.count({x, y}) != 0) {
        continue;
      }

      splitters.insert({x, y});
      if (beam.direction == 'L' || beam.direction == 'R') {
        if (beam.direction == 'L') {
          beam.y--;
        } else if (beam.direction == 'R') {
          beam.y++;
        }
      } else {
        beam.direction = 'L';
        beam.y--;
        beamQueue.push(beam);
        beam.direction = 'R';
        beam.y++;
        beam.y++;
        beamQueue.push(beam);
        continue;
      }
    }
    beamQueue.push(beam);
  }
  return energizedTiles.size();
}
