#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>
using namespace std;

class Tokenizer {
	public:
		//////////////////////////////////////////////////////////////////////////////
		// @brief: Break lines into tokens based on given identifier, then store them
		//		   into given vector
		// @param input given string
		// @param split given identifier to split string by
		// @param vec vector to store the tokens into
		inline static void tokenize(string input, string split, vector<string>& vec) {
			vec.clear();
			int pos = input.find(split);
			int currPos = 0;
			while(pos != string::npos && currPos < input.length()){
				vec.push_back(input.substr(currPos, pos-currPos));
				currPos = pos + split.length();
				pos = input.find(split, currPos);
			}
			if(currPos < input.length())
				vec.push_back(input.substr(currPos));
		}
};
#endif