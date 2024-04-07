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



// shitty brute force solution part1 is fast, part2 takes a couple hours.

std::vector<long long> createUnorderedMapAndSearch(const std::vector<std::vector<long long>> &data,
												   std::vector<long long> &seeds);
long long createUnorderedMapAndSearch2(const std::vector<std::vector<long long>> &data, long long seed);
long long findValueInMap(const std::unordered_map<long long, long long> &map, long long key);
void part1(std::vector<long long> &seeds,
		   std::vector<std::vector<long long>> &seedToSoilMap,
		   std::vector<std::vector<long long>> &soilToFert,
		   std::vector<std::vector<long long>> &fertToWaterMap,
		   std::vector<std::vector<long long>> &waterToLight,
		   std::vector<std::vector<long long>> &lightToTemp,
		   std::vector<std::vector<long long>> &tempToHum,
		   std::vector<std::vector<long long>> &humToLoc);
void part2(std::vector<long long> &seeds,
		   std::vector<std::vector<long long>> &seedToSoilMap,
		   std::vector<std::vector<long long>> &soilToFert,
		   std::vector<std::vector<long long>> &fertToWaterMap,
		   std::vector<std::vector<long long>> &waterToLight,
		   std::vector<std::vector<long long>> &lightToTemp,
		   std::vector<std::vector<long long>> &tempToHum,
		   std::vector<std::vector<long long>> &humToLoc);
std::unordered_map<long long, long long> createUnorderedMap(const std::vector<std::vector<long long>> &data);
std::vector<long long> parseLine(const std::string &line) {
  std::vector<long long> values;
  std::istringstream iss(line);
  long long value;
  while (iss >> value) {
	values.push_back(value);
  }
  return values;
}
std::unordered_map<long long, long long> createUnorderedMap(const std::vector<std::vector<long long>> &data) {
  std::unordered_map<long long, long long> unorderedMap;

  for (const auto &mapData : data) {
	long long start = mapData[0];
	long long end = mapData[1] + mapData[2] - 1;

	for (long long i = mapData[1]; i <= end; ++i) {
	  unorderedMap[i] = start + i - mapData[1];
	}
  }

  return unorderedMap;
}
std::vector<long long> createUnorderedMapAndSearch(const std::vector<std::vector<long long>> &data,
												   std::vector<long long> &seeds) {
  std::vector<long long> temp;
  long long current = 0;

  for (auto n : seeds) {
	bool found = false;

	for (const auto &mapData : data) {
	  if (n >= mapData[1] && n < mapData[1] + mapData[2]) {
		current = n - mapData[1] + mapData[0];
		found = true;
		break;
	  }
	}

	if (!found) {
	  current = n;
	}

	temp.push_back(current);
  }

  return temp;
}
long long createUnorderedMapAndSearch2(const std::vector<std::vector<long long>> &data, long long seed) {
  long long current = 0;

  for (const auto &mapData : data) {
	if (seed >= mapData[1] && seed < mapData[1] + mapData[2]) {
	  current = seed - mapData[1] + mapData[0];
	  return current;
	}
  }

  return seed;
}
int main() {

  std::ifstream inputFile("day5.txt");
  if (!inputFile.is_open()) {
	std::cerr << "Error opening the file." << std::endl;
	return 1;
  }

  std::vector<long long> seeds;
  std::vector<std::vector<long long>> seedToSoilMap;
  std::vector<std::vector<long long>> soilToFert;
  std::vector<std::vector<long long>> fertToWaterMap;
  std::vector<std::vector<long long>> waterToLight;
  std::vector<std::vector<long long>> lightToTemp;
  std::vector<std::vector<long long>> tempToHum;
  std::vector<std::vector<long long>> humToLoc;

  std::string line;
  while (std::getline(inputFile, line)) {

	if (line.find("seeds:") != std::string::npos) {

	  seeds = parseLine(line.substr(line.find(":") + 1));
	} else if (line.find("seed-to-soil map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		seedToSoilMap.push_back(parseLine(line));
	  }
	} else if (line.find("soil-to-fertilizer map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		soilToFert.push_back(parseLine(line));
	  }
	} else if (line.find("fertilizer-to-water map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		fertToWaterMap.push_back(parseLine(line));
	  }
	} else if (line.find("water-to-light map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		waterToLight.push_back(parseLine(line));
	  }
	} else if (line.find("light-to-temperature map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		lightToTemp.push_back(parseLine(line));
	  }
	} else if (line.find("temperature-to-humidity map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		tempToHum.push_back(parseLine(line));
	  }
	} else if (line.find("humidity-to-location map:") != std::string::npos) {

	  while (std::getline(inputFile, line) && !line.empty()) {
		humToLoc.push_back(parseLine(line));
	  }
	}

  }

  part1(seeds, seedToSoilMap, soilToFert, fertToWaterMap, waterToLight, lightToTemp, tempToHum, humToLoc);
  //part2(seeds, seedToSoilMap, soilToFert, fertToWaterMap, waterToLight, lightToTemp, tempToHum, humToLoc);
  return 0;
}
void part1(std::vector<long long> &seeds,
		   std::vector<std::vector<long long>> &seedToSoilMap,
		   std::vector<std::vector<long long>> &soilToFert,
		   std::vector<std::vector<long long>> &fertToWaterMap,
		   std::vector<std::vector<long long>> &waterToLight,
		   std::vector<std::vector<long long>> &lightToTemp,
		   std::vector<std::vector<long long>> &tempToHum,
		   std::vector<std::vector<long long>> &humToLoc) {
  std::vector<long long> temp;
  temp = createUnorderedMapAndSearch(seedToSoilMap, seeds);

  temp = createUnorderedMapAndSearch(soilToFert, temp);
  temp = createUnorderedMapAndSearch(fertToWaterMap, temp);
  temp = createUnorderedMapAndSearch(waterToLight, temp);
  temp = createUnorderedMapAndSearch(lightToTemp, temp);
  temp = createUnorderedMapAndSearch(tempToHum, temp);
  temp = createUnorderedMapAndSearch(humToLoc, temp);

  std::sort(temp.begin(), temp.end());
  for (auto n : temp) {
	std::cout << n << std::endl;
  }

}
long long findValueInMap(const std::unordered_map<long long, long long> &map, long long key) {
  auto it = map.find(key);
  return (it != map.end()) ? it->second : key; // Return -1 if key not found
}
void part2(std::vector<long long> &seeds,
		   std::vector<std::vector<long long>> &seedToSoilMap,
		   std::vector<std::vector<long long>> &soilToFert,
		   std::vector<std::vector<long long>> &fertToWaterMap,
		   std::vector<std::vector<long long>> &waterToLight,
		   std::vector<std::vector<long long>> &lightToTemp,
		   std::vector<std::vector<long long>> &tempToHum,
		   std::vector<std::vector<long long>> &humToLoc) {

  std::cout << "creating maps" << std::endl;

  std::cout << "populate" << std::endl;
  long long smallest = 0;
  for (size_t i = 0; i < seeds.size(); i += 2) {
	long long start = seeds[i];
	long long size = seeds[i + 1];

	if (size <= 0) {

	  continue;
	}

	for (long long j = start; j < start + size; ++j) {
	  long long value = createUnorderedMapAndSearch2(seedToSoilMap, j);
	  value = createUnorderedMapAndSearch2(soilToFert, value);
	  value = createUnorderedMapAndSearch2(fertToWaterMap, value);
	  value = createUnorderedMapAndSearch2(waterToLight, value);
	  value = createUnorderedMapAndSearch2(lightToTemp, value);
	  value = createUnorderedMapAndSearch2(tempToHum, value);
	  value = createUnorderedMapAndSearch2(humToLoc, value);

	  if (smallest > value && value != 0) {
		smallest = value;
	  } else if (smallest == 0) {
		smallest = value;
	  }

	}

  }
  std::cout << smallest;

}