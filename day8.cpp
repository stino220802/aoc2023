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
std::mutex mtx;

void part1(std::vector<std::string> instructions, std::map<std::string, std::pair<std::string, std::string>> map);
void part2(std::vector<std::string> instructions, std::map<std::string, std::pair<std::string, std::string>> map);
bool checker(std::vector<std::string> nodes);
std::string removeParentheses(const std::string &str) {
  std::string result = str;
  result.erase(std::remove(result.begin(), result.end(), '('), result.end());
  result.erase(std::remove(result.begin(), result.end(), ')'), result.end());
  return result;
}
long long gcd(long long a, long long b) {
  while (b != 0) {
	long long temp = b;
	b = a % b;
	a = temp;
  }
  return a;
}


long long lcm(const std::vector<int>& numbers) {
  if (numbers.empty()) {
	return 0;
  }
  long long result = numbers[0];
  for (size_t i = 1; i < numbers.size(); ++i) {
	result = (result * numbers[i]) / gcd(result, numbers[i]);
  }
  return result;
}

int main() {

  std::ifstream inputFile("day8.txt");
  if (!inputFile.is_open()) {
	std::cerr << "Error opening file." << std::endl;
	return 1;
  }

  std::string line;
  std::vector<std::string> instructions_vector;
  std::map<std::string, std::pair<std::string, std::string>> RL_map;


  if (std::getline(inputFile, line)) {
	std::istringstream iss(line);
	std::string instruction;
	while (iss >> instruction) {
	  instructions_vector.push_back(instruction);
	}
  }


  while (std::getline(inputFile, line)) {
	std::istringstream iss(line);
	std::string key, equals, valueString;

	if (iss >> key >> equals) {

	  std::getline(iss, valueString);
	  key.erase(key.size());

	  valueString = removeParentheses(valueString);

	  std::istringstream valueStream(valueString);
	  std::string value1, value2;

	  if (std::getline(valueStream, value1, ',') && std::getline(valueStream, value2, ',')) {
		value1.erase(0, 1);
		value2.erase(0, 1);
		RL_map[key] = std::make_pair(value1, value2);
	  } else {
		std::cerr << "Error parsing values from line: " << line << std::endl;
	  }
	} else {
	  std::cerr << "Error parsing line: " << line << std::endl;
	}
  }

  part1(instructions_vector, RL_map);
  auto start = std::chrono::high_resolution_clock::now();
  part2(instructions_vector, RL_map);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  // Output the duration
  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  return 0;
}

void part1(std::vector<std::string> instructions, std::map<std::string, std::pair<std::string, std::string>> map) {
  std::string current = "AAA";
  int steps = 0;
  int countInstructions = 0;
  do {
	for (auto &t : map) {
	  if (t.first == current) {
		if (instructions[0][steps] == 'L') {
		  current = t.second.first;
		  break;
		} else if (instructions[0][steps] == 'R') {
		  current = t.second.second;
		  break;
		}
	  }
	}
	steps++;
	countInstructions++;
	if (steps == instructions[0].size()) {
	  steps = 0;
	}
  } while (current != "ZZZ");
  std::cout << countInstructions << std::endl;
}
void part2(std::vector<std::string> instructions, std::map<std::string, std::pair<std::string, std::string>> map) {
  std::vector<std::string> nodes;
  int steps = 0;
  long long countInstructions = 0;
  int instructionSize = instructions[0].size();
  for (const auto &m : map) {
	if (m.first[2] == 'A') {
	  nodes.push_back(m.first);
	}
  }

  std::vector<int> test;
  for(auto & n : nodes){

	do{
	  for(auto & m : map){
		if(n == m.first){
		  if(instructions[0][steps] == 'L'){
			n = m.second.first;
			break;
		  }

			else if(instructions[0][steps] == 'R'){
			  n = m.second.second;
			  break;
			}
		}
	  }
	  steps++;
	  countInstructions++;
	  if(steps == instructionSize){
		steps = 0;
	  }
	}
	while(n[2] != 'Z');
	test.emplace_back(countInstructions);
	countInstructions = 0;
  }
  long long result = lcm(test);
  std::cout << result << std::endl;
}

bool checker(std::vector<std::string> nodes) {
  for (const auto &n : nodes) {
	if (n[2] != 'Z') {
	  return true;
	}
  }
  return false;
}




