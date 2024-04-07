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

#include <functional>
int getCardValue(char cardChar);
void part1(std::vector<std::pair<std::string, int>> data);
void part2(std::vector<std::pair<std::string, int>> data);
bool isWildCard(char rank);
std::vector<std::pair<std::string, int>> sortCategories(std::vector<std::pair<std::string, int>> data);
std::vector<std::pair<std::string, int>> sortCategories2(std::vector<std::pair<std::string, int>> data);
bool customSort(const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2);
bool customSort2(const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2);
bool customSort(const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2) {
  const std::string ranks = "23456789TJQKA";

  for (size_t i = 0; i < hand1.first.size(); ++i) {
	size_t rankIndex1 = ranks.find(hand1.first[i]);
	size_t rankIndex2 = ranks.find(hand2.first[i]);

	if (rankIndex1 < rankIndex2) {
	  return true;
	} else if (rankIndex1 > rankIndex2) {
	  return false;
	}
	// If ranks are equal, continue checking the next card
  }

  return false;
}
bool isWildCard(char rank) {
  return rank == 'J';
}

bool customSort2(const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2) {
  const std::string ranks = "J23456789TQKA";

  for (size_t i = 0; i < hand1.first.size(); ++i) {
	size_t rankIndex1 = ranks.find(hand1.first[i]);
	size_t rankIndex2 = ranks.find(hand2.first[i]);

	if (rankIndex1 < rankIndex2) {
	  return true;
	} else if (rankIndex1 > rankIndex2) {
	  return false;
	}
	// If ranks are equal, continue checking the next card
  }

  return false;
}

int main() {
  std::vector<std::pair<std::string, int>> data; // Vector to store pairs of string and int

  std::ifstream inputFile("day7.txt"); // Replace "your_input_file.txt" with the actual file path

  if (inputFile.is_open()) { // Check if the file is successfully opened
	std::string line;

	// Loop through each line in the file
	while (std::getline(inputFile, line)) {
	  std::istringstream lineStream(line);
	  std::string strValue;
	  int intValue;

	  // Read string and integer values from each line
	  if (lineStream >> strValue >> intValue) {
		data.push_back(std::make_pair(strValue, intValue)); // Add pair to vector
	  } else {
		std::cerr << "Error reading line: " << line << std::endl;
	  }
	}

	inputFile.close(); // Close the file
  } else {
	std::cerr << "Error opening file" << std::endl;
	return 1; // Return error code if file cannot be opened
  }

  // Print the contents of the vector
  //part1(data);
  part2(data);
  return 0;
}

void part1(std::vector<std::pair<std::string, int>> data) {
  std::vector<std::pair<std::string, int>> sorted = sortCategories(data);
  long long winnings = 0;
  int count = 1;
  for(int i = 0; i < sorted.size(); i++) {
	int temp = sorted[i].second * count;
	winnings += temp;
	//std::cout << "winnings: " << winnings << " i: " << count << " sorted " << sorted[i].second << " cards: " << sorted[i].first << std::endl;
	count++;
  }
  std::cout << winnings << std::endl;
}

void part2(std::vector<std::pair<std::string, int>> data) {
  std::vector<std::pair<std::string, int>> sorted = sortCategories2(data);

}
std::vector<std::pair<std::string, int>> sortCategories(std::vector<std::pair<std::string, int>> data) {
  std::vector<std::pair<std::string, int>> five;
  std::vector<std::pair<std::string, int>> four;
  std::vector<std::pair<std::string, int>> fulhouse;
  std::vector<std::pair<std::string, int>> three;
  std::vector<std::pair<std::string, int>> twoPair;
  std::vector<std::pair<std::string, int>> pair;
  std::vector<std::pair<std::string, int>> highCard;

  std::vector<std::pair<std::string, int>> sorted;

  for (auto d : data) {
	std::array<int, 13> rankCount = {};

	for (char rank : d.first) {
	  if (std::isdigit(rank)) {
		int index = rank - '2';
		rankCount[index]++;
	  } else if (rank == 'T') {
		rankCount[8]++;
	  } else if (rank == 'J') {
		rankCount[9]++;
	  } else if (rank == 'Q') {
		rankCount[10]++;
	  } else if (rank == 'K') {
		rankCount[11]++;
	  } else if (rank == 'A') {
		rankCount[12]++;
	  }
	}

	int numPairs = 0;
	int numThreeOfAKind = 0;
	int numFourOfAKind = 0;
	int numFiveOfAKind = 0;

	for (int count : rankCount) {
	  if (count == 2) {
		numPairs++;
	  } else if (count == 3) {
		numThreeOfAKind++;
	  } else if (count == 4) {
		numFourOfAKind++;
	  } else if (count == 5) {
		numFiveOfAKind++;
	  }
	}

	if (numFiveOfAKind == 1) {
	  five.push_back(d);
	} else if (numFourOfAKind == 1) {
	  four.push_back(d);
	} else if (numThreeOfAKind == 1 && numPairs == 1) {
	  fulhouse.push_back(d);  // Full house condition
	} else if (numThreeOfAKind == 1) {
	  three.push_back(d);
	} else if (numPairs == 2) {
	  twoPair.push_back(d);
	} else if (numPairs == 1) {
	  pair.push_back(d);
	} else {
	  highCard.push_back(d);
	}
  }
  for(auto i: fulhouse){
	std::cout << i.first << " " << i.second << std::endl;
  }
  std::sort(five.begin(), five.end(), customSort);
  std::sort(four.begin(), four.end(), customSort);
  std::sort(fulhouse.begin(), fulhouse.end(), customSort);

  std::sort(three.begin(), three.end(), customSort);
  std::sort(twoPair.begin(), twoPair.end(), customSort);
  std::sort(pair.begin(), pair.end(), customSort);
  std::sort(highCard.begin(), highCard.end(), customSort);
  sorted.insert(sorted.end(), highCard.begin(), highCard.end());
  sorted.insert(sorted.end(), pair.begin(), pair.end());
  sorted.insert(sorted.end(), twoPair.begin(), twoPair.end());
  sorted.insert(sorted.end(), three.begin(), three.end());
  sorted.insert(sorted.end(), fulhouse.begin(), fulhouse.end());
  sorted.insert(sorted.end(), four.begin(), four.end());
  sorted.insert(sorted.end(), five.begin(), five.end());
  return sorted;
}
std::vector<std::pair<std::string, int>> sortCategories2(std::vector<std::pair<std::string, int>> data) {
  std::vector<std::pair<std::string, int>> sorted;

  std::vector<std::pair<std::string, int>> five;
  std::vector<std::pair<std::string, int>> four;
  std::vector<std::pair<std::string, int>> fullHouse;
  std::vector<std::pair<std::string, int>> three;
  std::vector<std::pair<std::string, int>> twoPair;
  std::vector<std::pair<std::string, int>> pair;
  std::vector<std::pair<std::string, int>> highCard;

  for (auto d : data) {
	std::array<int, 13> rankCount = {};

	for (char rank : d.first) {
	  if (std::isdigit(rank)) {
		int index = rank - '2';
		rankCount[index]++;
	  } else if (rank == 'T') {
		rankCount[8]++;
	  } else if (isWildCard(rank)) {
		// Treat J as a wild card, increment count for all ranks
		for (int i = 0; i < 13; ++i) {
		  rankCount[i]++;
		}
	  } else if (rank == 'Q') {
		rankCount[10]++;
	  } else if (rank == 'K') {
		rankCount[11]++;
	  } else if (rank == 'A') {
		rankCount[12]++;
	  }
	}

	int numPairs = 0;
	int numThreeOfAKind = 0;
	int numFourOfAKind = 0;
	int numFiveOfAKind = 0;

	for (int count : rankCount) {
	  if (count == 2) {
		numPairs++;
	  } else if (count == 3) {
		numThreeOfAKind++;
	  } else if (count == 4) {
		numFourOfAKind++;
	  } else if (count == 5) {
		numFiveOfAKind++;
	  }
	}

	if (numFiveOfAKind == 1) {
	  five.push_back(d);
	} else if (numFourOfAKind == 1) {
	  four.push_back(d);
	} else if (numThreeOfAKind == 1 && numPairs == 1) {
	  fullHouse.push_back(d);
	} else if (numThreeOfAKind == 1) {
	  three.push_back(d);
	} else if (numPairs == 2) {
	  twoPair.push_back(d);
	} else if (numPairs == 1) {
	  pair.push_back(d);
	} else {
	  highCard.push_back(d);
	}
  }

  // Output the categorized hands
  std::cout << "Five of a kind: ";
  for (auto hand : five) std::cout << hand.first << " ";
  std::cout << "\nFour of a kind: ";
  for (auto hand : four) std::cout << hand.first << " ";
  std::cout << "\nFull House: ";
  for (auto hand : fullHouse) std::cout << hand.first << " ";
  std::cout << "\nThree of a kind: ";
  for (auto hand : three) std::cout << hand.first << " ";
  std::cout << "\nTwo Pair: ";
  for (auto hand : twoPair) std::cout << hand.first << " ";
  std::cout << "\nPair: ";
  for (auto hand : pair) std::cout << hand.first << " ";
  std::cout << "\nHigh Card: ";
  for (auto hand : highCard) std::cout << hand.first << " ";

  return sorted;
}