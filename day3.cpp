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

void part2(std::vector<std::string> grid);
bool checkNeighbors2(const std::vector<std::string> &grid, int i, int j);
void part1(std::vector<std::string> grid);
bool isSymbol(char ch);
bool isInsideGrid(int i, int j, int rows, int cols);
bool checkNeighbors(const std::vector<std::string> &grid, int i, int j);
std::vector<int> findConnectedNumbers(int i, int j, const std::vector<std::string> &grid);
std::vector<int> getAdjacentNumbers(const std::vector<std::string> &grid, int row, int col);
int checkAboveLeft(const std::vector<std::string> &grid, int row, int col);
int checkAboveRight(const std::vector<std::string> &grid, int row, int col, bool topleft);
int checkLeft(const std::vector<std::string> &grid, int row, int col);
int checkRight(const std::vector<std::string> &grid, int row, int col);

int main() {
  std::ifstream inputFile("day3.txt");
  if (!inputFile.is_open()) {
	std::cerr << "Error opening file.\n";
	return 1;
  }
  std::vector<std::string> grid;
  std::string line;
  while (std::getline(inputFile, line)) {
	grid.push_back(line);
  }
  inputFile.close();
  part1(grid);
  part2(grid);

  return 0;
}
void part1(std::vector<std::string> grid) {
  std::vector<int> numbers;
  std::vector<int> partnumbers;
  int temp = 0;
  bool check = false;
  for (int i = 0; i < grid.size(); ++i) {
	for (int j = 0; j < grid[i].size(); ++j) {
	  if (std::isdigit(grid[i][j])) {
		numbers.push_back(grid[i][j] - '0');
		if (check == false) {
		  check = checkNeighbors(grid, i, j);
		}
	  } else if (check == true) {
		for (auto &n : numbers) {
		  temp = temp * 10 + n;
		}
		partnumbers.push_back(temp);
		check = false;
		temp = 0;
		numbers.clear();
	  } else {
		numbers.clear();
	  }
	}
  }
  long long sum = 0;
  for (auto &n : partnumbers) {
	sum = sum + n;
  }
  std::cout << sum << std::endl;

}
bool isSymbol(char ch) {
  if (ch == '.') {
	return false;
  }
  return !std::isalnum(ch);
}
bool checkNeighbors(const std::vector<std::string> &grid, int i, int j) {
  int rows = grid.size();
  int cols = grid[0].size();
  for (int x = i - 1; x <= i + 1; ++x) {
	for (int y = j - 1; y <= j + 1; ++y) {
	  if (isInsideGrid(x, y, rows, cols)) {
		char currentElement = grid[x][y];
		bool test = isSymbol(currentElement);
		if (test == true) {
		  return true;
		}
	  }
	}
  }
  return false;
}
bool isInsideGrid(int i, int j, int rows, int cols) {
  return i >= 0 && i < rows && j >= 0 && j < cols;
}

std::vector<int> getAdjacentNumbers(const std::vector<std::string> &grid, int row, int col) {
  int rows = grid.size();
  int cols = grid[0].size();
  if (row < 0 || row >= rows || col < 0 || col >= cols) {
	std::cerr << "Invalid position!" << std::endl;
	return std::vector<int>();
  }
  bool topleft = false;
  bool topright = false;
  bool bottomright = false;
  bool bottomleft = false;
  std::vector<int> adjacentNumbers;
  std::vector<int> test;

  int countAdjacentNumbers = 0;

  if (row > 0 && col > 0 && isdigit(grid[row - 1][col - 1])) {
	adjacentNumbers.push_back(grid[row - 1][col - 1] - '0');
	int digit = checkAboveLeft(grid, row - 1, col - 1);
	topleft = true;

	++countAdjacentNumbers;
	test.push_back(digit);
  }

  if (row > 0 && col < cols - 1 && isdigit(grid[row - 1][col + 1])) {
	adjacentNumbers.push_back(grid[row - 1][col + 1] - '0');
	int digit = checkAboveRight(grid, row - 1, col + 1, topleft);
	topright = true;

	if (digit != 0) {
	  ++countAdjacentNumbers;
	  test.push_back(digit);
	}
  }

  if (row > 0 && isdigit(grid[row - 1][col]) && topright == false && topleft == false) {
	test.push_back(grid[row - 1][col] - '0');
	++countAdjacentNumbers;
  }

  if (col > 0 && isdigit(grid[row][col - 1])) {
	adjacentNumbers.push_back(grid[row][col - 1] - '0');
	int digit = checkLeft(grid, row, col - 1);
	++countAdjacentNumbers;
	test.push_back(digit);
  }

  if (col < cols - 1 && isdigit(grid[row][col + 1])) {
	adjacentNumbers.push_back(grid[row][col + 1] - '0');
	int digit = checkRight(grid, row, col + 1);
	++countAdjacentNumbers;
	test.push_back(digit);
  }
  if (row < rows - 1 && col > 0 && isdigit(grid[row + 1][col - 1])) {
	adjacentNumbers.push_back(grid[row + 1][col - 1] - '0');
	int digit = checkAboveLeft(grid, row + 1, col - 1);
	bottomleft = true;
	++countAdjacentNumbers;
	test.push_back(digit);
  }

  if (row < rows - 1 && col < cols - 1 && isdigit(grid[row + 1][col + 1])) {
	adjacentNumbers.push_back(grid[row + 1][col + 1] - '0');
	int digit = checkAboveRight(grid, row + 1, col + 1, bottomleft);

	bottomright = true;
	if (digit != 0) {
	  ++countAdjacentNumbers;
	  test.push_back(digit);
	}

  }

  if (row < rows - 1 && isdigit(grid[row + 1][col]) && bottomright == false && bottomleft == false) {

	test.push_back(grid[row + 1][col] - '0');
	++countAdjacentNumbers;
  }

  if (test.size() == 2) {
	return test;
  } else {
	return std::vector<int>();
  }
}

void part2(std::vector<std::string> grid) {
  std::vector<int> numbers;
  std::vector<int> partnumbers;
  int temp = 0;
  bool check = false;
  int total = 0;
  for (int i = 0; i < grid.size(); i++) {
	for (int j = 0; j < grid[i].size(); j++) {
	  if (isSymbol(grid[i][j]) == true) {

		std::vector<int> result = getAdjacentNumbers(grid, i, j);
		if (result.size() == 2) {
		  temp = result[0] * result[1];
		  total = total + temp;
		  check = true;
		}
	  }
	}
  }
  std::cout << total;
}
int checkAboveLeft(const std::vector<std::string> &grid, int row, int col) {
  int rows = grid.size();
  int cols = grid[0].size();
  int digit = 0;
  digit = grid[row][col] - '0';
  int temp = 0;
  if (isInsideGrid(col - 1, row, rows, cols) == true) {

	if (isdigit(grid[row][col - 1])) {

	  temp = grid[row][col - 1] - '0';
	  temp = temp * 10;
	  digit = digit + temp;

	  if (isInsideGrid(col - 2, row, rows, cols) == true) {
		if (isdigit(grid[row][col - 2])) {
		  temp = grid[row][col - 2] - '0';
		  temp = temp * 100;
		  digit = digit + temp;
		}
	  }
	}
  }
  if (isInsideGrid(col + 1, row, rows, cols) == true) {
	if (isdigit(grid[row][col + 1])) {
	  digit = digit * 10;
	  temp = grid[row][col + 1] - '0';
	  digit = digit + temp;
	  if (isInsideGrid(col + 2, row, rows, cols) == true) {
		if (isdigit(grid[row][col + 2])) {
		  digit = digit * 10;
		  temp = grid[row][col + 2] - '0';
		  digit = digit + temp;
		}
	  }
	}
  }
  return digit;
}

int checkAboveRight(const std::vector<std::string> &grid, int row, int col, bool topleft) {
  int rows = grid.size();
  int cols = grid[0].size();
  int digit = 0;
  digit = grid[row][col] - '0';
  int temp = 0;

  if (topleft == false) {
	if (isInsideGrid(col - 1, row, rows, cols) == true) {
	  if (isdigit(grid[row][col - 1])) {
		temp = grid[row][col - 1] - '0';
		temp = temp * 10;
		digit = digit + temp;
	  }
	}
  }

  if (isInsideGrid(col + 1, row, rows, cols) == true) {

	if (isdigit(grid[row][col + 1])) {

	  digit = digit * 10;
	  temp = grid[row][col + 1] - '0';
	  digit = digit + temp;
	  if (isInsideGrid(col + 2, row, rows, cols) == true) {
		if (isdigit(grid[row][col + 2])) {

		  digit = digit * 10;
		  temp = grid[row][col + 2] - '0';
		  digit = digit + temp;
		}
	  }
	}
  }
  if (digit < 10 && topleft == true) {
	return 0;
  }
  return digit;
}
int checkLeft(const std::vector<std::string> &grid, int row, int col) {
  int rows = grid.size();
  int cols = grid[0].size();
  int digit = 0;
  digit = grid[row][col] - '0';
  int temp = 0;
  if (isInsideGrid(col - 1, row, rows, cols) == true) {

	if (isdigit(grid[row][col - 1])) {

	  temp = grid[row][col - 1] - '0';
	  temp = temp * 10;
	  digit = digit + temp;

	  if (isInsideGrid(col - 2, row, rows, cols) == true) {
		if (isdigit(grid[row][col - 2])) {
		  temp = grid[row][col - 2] - '0';
		  temp = temp * 100;
		  digit = digit + temp;
		}

	  }
	}
  }
  return digit;
}
int checkRight(const std::vector<std::string> &grid, int row, int col) {
  int rows = grid.size();
  int cols = grid[0].size();
  int digit = 0;
  digit = grid[row][col] - '0';
  int temp = 0;
  if (isInsideGrid(col + 1, row, rows, cols) == true) {
	if (isdigit(grid[row][col + 1])) {
	  digit = digit * 10;
	  temp = grid[row][col + 1] - '0';
	  digit = digit + temp;
	  if (isInsideGrid(col + 2, row, rows, cols) == true) {
		if (isdigit(grid[row][col + 2])) {
		  digit = digit * 10;
		  temp = grid[row][col + 2] - '0';
		  digit = digit + temp;
		}
	  }
	}
  }
  return digit;
}
