#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype> // for std::isdigit
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
void rotateGrid(std::vector<std::vector<char>> &grid);
void part1(std::vector<std::vector<std::vector<char>>> grid);
void part2(std::vector<std::vector<std::vector<char>>> grid);
int main() {
  std::ifstream file("day13.txt");
  if (!file.is_open()) {
	std::cerr << "Error opening file." << std::endl;
	return 1;
  }
  std::vector<std::vector<std::vector<char>>> allBlocks;

  std::vector<std::vector<char>> currentBlock;

  std::string line;
  while (std::getline(file, line)) {
	if (line.empty()) {

	  if (!currentBlock.empty()) {
		allBlocks.push_back(currentBlock);
		currentBlock.clear();
	  }
	} else {

	  std::vector<char> row;
	  for (char c : line) {
		row.push_back(c);
	  }
	  currentBlock.push_back(row);
	}
  }

  if (!currentBlock.empty()) {
	allBlocks.push_back(currentBlock);
  }

  file.close();

  auto start = std::chrono::high_resolution_clock::now();
  part1(allBlocks);
  part2(allBlocks);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  return 0;
}
void part1(std::vector<std::vector<std::vector<char>>> grid) {
  long long total = 0;
  int checker = 0;
  for (auto &blocks : grid) {
	bool mirrorFound = false;
	for (int i = 0; i < blocks.size() - 1; i++) {
	  for (int j = 0; j < blocks[i].size(); j++) {
		if (blocks[i][j] != blocks[i + 1][j]) {
		  break;
		}
		if (j == blocks[i].size() - 1) {
		  int count = 1;
		  bool temp = false;
		  bool check = false;

		  while (temp == false) {
			for (int x = 0; x < blocks[i].size() - 1; x++) {
			  int index1 = i - count;
			  int index2 = i + 1 + count;
			  if (index1 < 0 || index2 > blocks.size() - 1) {
				if (i == 0) {
				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size() - 1) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }
			  if ((index1 >= 0 && (index1 < blocks.size() || index2 >= 0) && index2 < blocks.size())
				  && (i + 1 == blocks.size() - 1 || i == 0)) {
				if (i == 0) {
				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size() - 1) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }

			  if (blocks[i - count][x] != blocks[i + 1 + count][x]) {
				temp = true;
				break;
			  }
			  if (i - count < 0 || i + count + 1 >= blocks.size()) {
				if (temp != true) {
				  check = true;
				}
				temp = true;
				break;
			  } else if (x == blocks[i].size() - 2) {
				count++;
				break;
			  }
			}
		  }

		  if (count == 1 && check == true && checker == 2 && mirrorFound == false) {
			count = i + 1;
			count = count * 100;
			total += count;
			checker = 0;
			mirrorFound = true;

		  } else if (count == 1 && check == true && checker == 1 && mirrorFound == false) {
			count = i + 1;
			count = count * 100;
			total += count;
			checker = 0;
			mirrorFound = true;

		  } else {
			if (check && mirrorFound == false) {
			  count = i + 1;
			  count = count * 100;
			  total += count;
			  mirrorFound = true;
			}
		  }

		}
	  }
	}
  }
  for (auto &blocks : grid) {
	rotateGrid(blocks);
  }
  for (auto &blocks : grid) {
	bool mirrorFound = false;
	for (int i = 0; i < blocks.size() - 1; i++) {
	  for (int j = 0; j < blocks[i].size(); j++) {
		if (blocks[i][j] != blocks[i + 1][j]) {
		  break;
		}
		if (j == blocks[i].size() - 1) {
		  int count = 1;
		  bool temp = false;
		  bool check = false;

		  while (temp == false) {
			for (int x = 0; x < blocks[i].size(); x++) {
			  int index1 = i - count;
			  int index2 = i + 1 + count;
			  if (index1 < 0 || index2 > blocks.size() - 1) {
				if (i == 0) {
				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size()) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }

			  if ((index1 >= 0 && (index1 < blocks.size() || index2 >= 0) && index2 < blocks.size())
				  && (i + 1 == blocks.size() || i == 0)) {
				if (i == 0) {
				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size()) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }

			  if (blocks[i - count][x] != blocks[i + 1 + count][x]) {
				temp = true;
				break;
			  }
			  if (i - count < 0 || i + count + 1 >= blocks.size()) {
				if (temp != true) {
				  check = true;
				}
				temp = true;
				break;
			  } else if (x == blocks[i].size() - 1) {
				count++;
				break;
			  }
			}
		  }

		  if (check == true && checker == 2 && mirrorFound == false) {
			count = i + 1;
			total += count;
			checker = 0;
			mirrorFound = true;
		  }
		  else if (check == true && checker == 1 && mirrorFound == false) {
			count = i + 1;
			total += count;
			checker = 0;
			mirrorFound = true;

		  }
		  else {
			if (check && mirrorFound == false) {
			  count = i + 1;
			  total += count;
			  mirrorFound = true;
			}
		  }
		}
	  }
	}
  }
  std::cout << "Total = " << total << std::endl;

}
void part2(std::vector<std::vector<std::vector<char>>> grid) {
  long long total = 0;
  int checker = 0;

  for (auto &blocks : grid) {
	bool mirrorFound = false;

	for (int i = 0; i < blocks.size() - 1; i++) {
	  bool top = false;
	  int differences = 0;
	  for (int j = 0; j < blocks[i].size(); j++) {
		if (blocks[i][j] != blocks[i + 1][j]) {
		  differences++;
		  top = true;
		}
		if (j == blocks[i].size() - 1 && differences <= 1) {
		  int count = 1;
		  bool temp = false;
		  bool check = false;

		  while (temp == false) {
			for (int x = 0; x < blocks[i].size(); x++) {
			  int index1 = i - count;
			  int index2 = i + 1 + count;
			  if (index1 < 0 || index2 > blocks.size() - 1) {
				if (i == 0) {
				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size() - 1) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }
			  if ((index1 >= 0 && (index1 < blocks.size() || index2 >= 0) && index2 < blocks.size())
				  && (i + 1 == blocks.size() - 1 || i == 0)) {
				if (i == 0) {
				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size() - 1) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }

			  if (blocks[i - count][x] != blocks[i + 1 + count][x]) {
				if (differences == 0) {
				  differences += 1;
				} else {
				  differences += 1;
				  temp = true;
				  break;
				}
			  }
			  if (i - count < 0 || i + count + 1 >= blocks.size()) {
				if (temp != true) {
				  check = true;
				}
				temp = true;
				break;
			  } else if (x == blocks[i].size() - 2) {
				if (blocks[i - count][x + 1] != blocks[i + 1 + count][x + 1]) {
				  differences++;
				}
				count++;
				break;
			  }
			}
		  }

		  if (count == 1 && check == true && checker == 2 && mirrorFound == false && differences == 1) {
			count = i + 1;
			count = count * 100;
			total += count;
			checker = 0;
			mirrorFound = true;

		  } else if (count == 1 && check == true && checker == 1 && mirrorFound == false && differences == 1) {
			count = i + 1;
			count = count * 100;
			total += count;
			checker = 0;
			mirrorFound = true;

		  } else {
			if (check && mirrorFound == false && differences == 1) {
			  count = i + 1;
			  count = count * 100;
			  total += count;
			  mirrorFound = true;
			}
		  }
		}
	  }
	}
  }
  for (auto &blocks : grid) {
	rotateGrid(blocks);
  }
  for (auto &blocks : grid) {
	bool mirrorFound = false;
	bool top = false;
	for (int i = 0; i < blocks.size() - 1; i++) {
	  int differences = 0;
	  for (int j = 0; j < blocks[i].size(); j++) {
		if (blocks[i][j] != blocks[i + 1][j]) {
		  differences++;
		  top = true;
		}
		if (j == blocks[i].size() - 1) {
		  int count = 1;
		  bool temp = false;
		  bool check = false;

		  while (temp == false) {
			for (int x = 0; x < blocks[i].size(); x++) {
			  int index1 = i - count;
			  int index2 = i + 1 + count;
			  if (index1 < 0 || index2 > blocks.size() - 1) {

				if (i == 0) {

				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size()) {
				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }

			  if ((index1 >= 0 && (index1 < blocks.size() || index2 >= 0) && index2 < blocks.size())
				  && (i + 1 == blocks.size() || i == 0)) {
				if (i == 0) {

				  checker = 1;
				  temp = true;
				  check = true;
				  break;
				} else if (i + 1 == blocks.size()) {

				  checker = 2;
				  temp = true;
				  check = true;
				  break;
				}
				temp = true;
				check = true;
				break;
			  }

			  if (blocks[i - count][x] != blocks[i + 1 + count][x]) {
				if (differences == 0) {
				  differences += 1;
				} else {
				  differences += 1;
				  temp = true;
				  break;
				}
			  }
			  if (i - count < 0 || i + count + 1 >= blocks.size()) {
				if (temp != true) {
				  check = true;
				}
				temp = true;
				break;
			  } else if (x == blocks[i].size() - 1) {
				count++;
				break;
			  }
			}
		  }

		  if (check == true && checker == 2 && mirrorFound == false && differences == 1) {
			count = i + 1;
			total += count;
			checker = 0;
			mirrorFound = true;
		  } else if (check == true && checker == 1 && mirrorFound == false && differences == 1) {
			count = i + 1;
			total += count;
			checker = 0;
			mirrorFound = true;

		  } else {
			if (check && mirrorFound == false && differences == 1) {
			  count = i + 1;
			  total += count;
			  mirrorFound = true;
			}
		  }

		}
	  }
	}
  }
  std::cout << total << std::endl;
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