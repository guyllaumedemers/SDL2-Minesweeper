#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
namespace Toolset {
	class StringExtension {
	public:
		static vector<string> Split(string input, const char& delim) {
			stringstream ss(input);
			string line;
			vector<string> tokens;
			while (getline(ss, line)) {
				size_t pos, prev = 0;
				while ((pos = line.find_first_of(delim, prev)) != string::npos) {
					tokens.push_back(line.substr(prev, pos - prev));
					prev = pos + 1;
				}
				if (prev < line.length()) {
					tokens.push_back(line.substr(prev, line.find_last_of('.') - prev));
				}
			}
			return tokens;
		}
	};
}