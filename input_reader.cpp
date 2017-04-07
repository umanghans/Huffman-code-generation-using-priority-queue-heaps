#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <unordered_map>
#include <cstring>
#include "input_reader.h"

using namespace std;

void f_table(string filename, unordered_map<int,int> &freq_table, vector<int> &input_table)  {
	ifstream input_file;
	input_file.open(filename.c_str());
	int temp;

	while (input_file >> temp) {

        input_table.push_back(temp);

		if (freq_table.find(temp) == freq_table.end()) {
			freq_table[temp] = 1;
		} else {
			freq_table[temp] = freq_table[temp] + 1;
		}

	}
	input_file.close();
}
