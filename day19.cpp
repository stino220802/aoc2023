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
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Rule {
  std::string category;
  char parameter;
  char operatorType;
  int value;
  std::string results;
};

struct ValueSet {
  unsigned int x, m, a, s;
};

std::vector<Rule> readRules(std::ifstream &file) {
  std::vector<Rule> rules;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty())
      break;

    std::stringstream ss(line);
    std::string category;
    std::getline(ss, category, '{'); 

    std::string condition;
    while (std::getline(ss, condition, ',')) {
      Rule rule;
      rule.category = category;

      std::stringstream condStream(condition);
      if (!(condition.find('>') != std::string::npos ||
            condition.find('<') != std::string::npos)) {

        if (!condition.empty()) {
          condition.erase(condition.size() - 1);

          rule.results = condition;
          rule.parameter = '0';
          rule.operatorType = '0';
          rule.value = 0;
          rules.push_back(rule);
        }
        continue;
      }
      condStream >> rule.parameter >> rule.operatorType >> rule.value;

      if (condStream.peek() == ':') {
        condStream.ignore(); 
        std::string result;
        while (std::getline(condStream, result, ',')) {
          rule.results = result;
        }
      }

      rules.push_back(rule);
      if (ss.peek() == '}') {
        ss.ignore(1); 
        break;
      }
    }
  }

  return rules;
}

std::vector<ValueSet> readValueSets(std::ifstream &file) {
  std::vector<ValueSet> valueSets;
  std::string line;

  while (std::getline(file, line)) {

    if (line.empty())
      continue;
    ValueSet valueSet;
    char dummy;

    std::stringstream ss(line);
    ss.ignore(2); 
    ss >> dummy >> valueSet.x;
    ss.ignore(3); 
    ss >> valueSet.m;
    ss.ignore(3); 
    ss >> valueSet.a;
    ss.ignore(3); 
    ss >> valueSet.s;
    ss.ignore(1); 

    valueSets.push_back(valueSet);
  }

  return valueSets;
}
void part1(std::vector<Rule> rules, std::vector<ValueSet> valueSets);
void part2(std::vector<Rule> rules, std::vector<ValueSet> valueSets);
int main() {
  std::ifstream file("day19.txt");
  if (!file.is_open()) {
    std::cerr << "Unable to open file" << std::endl;
    return 1;
  }

  std::vector<Rule> rules = readRules(file);
  std::vector<ValueSet> valueSets = readValueSets(file);

  file.close();

  
  auto start = std::chrono::high_resolution_clock::now();
  part1(rules, valueSets);
  part2(rules, valueSets);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds"
            << std::endl;
  return 0;
}

void part2(std::vector<Rule> rules, std::vector<ValueSet> valueSets){
     std::queue<std::pair<std::unordered_map<char, std::pair<int, int>>, std::string>> queue;
     queue.push({{{'x', {1, 4000}}, {'m', {1, 4000}}, {'a', {1, 4000}}, {'s', {1, 4000}}}, "in"}); 

     long long combinations = 0; 
     while(!queue.empty()){
      auto [part_ranges, workflow_name] = queue.front();
      queue.pop();
      if(workflow_name == "A"){
        long long product = 1; 
        for(const auto & [_, range] : part_ranges){
            product *= (range.second- range.first + 1); 
        }
        combinations += product;
      }
      while(workflow_name != "A" && workflow_name != "R"){
        for(auto & r: rules){
          if(r.category == workflow_name){
            auto it = part_ranges.find(r.parameter);
            if(it == part_ranges.end()){
              queue.push({part_ranges, r.results});
              continue;
            }
            int low = it->second.first;
            int high = it->second.second;

            if(r.operatorType == '<' && low < r.value){
              auto new_part_ranges = part_ranges; 
              new_part_ranges[r.parameter] = {low, r.value - 1}; 
              queue.push({new_part_ranges, r.results});
              part_ranges[r.parameter] = {r.value, high}; 
            }
            else if(r.operatorType == '>' && high > r.value){
              auto new_part_ranges = part_ranges; 
              new_part_ranges[r.parameter] = {r.value +1, high}; 
              queue.push({new_part_ranges, r.results}); 
              part_ranges[r.parameter] = {low, r.value};
            }
            else{
              queue.push({part_ranges, r.results});
            }
          }
        
        }

        break;
      }
     }

     std::cout << "total part 2 = " << combinations << std::endl; 
}



void part1(const std::vector<Rule> rules, const std::vector<ValueSet> valueSets) {
    long long total = 0;

    for (const auto& v : valueSets) {
        bool ar = false;
        std::string cat = "in";

        while (!ar) {
            for (const auto& r : rules) {
                if (r.category == cat) {
                    auto evaluate = [&](char param, int value) {
                        if ((r.operatorType == '>' && value > r.value) ||
                            (r.operatorType == '<' && value < r.value) ||
                            r.parameter == '0') {
                            if (r.results == "A") {
                                total += v.x + v.s + v.m + v.a;
                            }
                            ar = (r.results == "A" || r.results == "R");
                            cat = r.results;
                            return true;
                        }
                        return false;
                    };

                    if ((r.parameter == '0' && evaluate('0', 0)) ||
                        (r.parameter == 'x' && evaluate('x', v.x)) ||
                        (r.parameter == 'm' && evaluate('m', v.m)) ||
                        (r.parameter == 'a' && evaluate('a', v.a)) ||
                        (r.parameter == 's' && evaluate('s', v.s))) {
                        break;
                    }
                }
            }
        }
    }
    std::cout << "total part 1 = " << total << std::endl;
}