#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <time.h>
#include "input_reader.h"
#include "huffman_binary_heap.h"
#include "huffman_four_way_cache_heap.h"
#include "huffman_pairing_heap.h"


using namespace std;

const string INPUT_FILE = "sample_input_large.txt";

int main()
{
    unordered_map<int, int> freq_table;
    vector<int> input_table;
    clock_t start_time;

    start_time = clock();

    f_table(INPUT_FILE,  freq_table, input_table);

    cout << "time to read input file (microsecond):  " << (clock() - start_time) << endl;

    start_time = clock();

    for(int i = 0; i < 10; i++) {
        start_time = clock();
        build_tree_using_binary_heap(freq_table);
    }
    cout << "Time using binary heap (microsecond):  " << (clock() - start_time)/10 << endl;

    start_time = clock();

    for(int i = 0; i < 10; i++) {
       start_time = clock();
       build_tree_using_4way_heap(freq_table);
    }

    cout << "Time using four way cache heap (microsecond):  " << (clock() - start_time)/10 << endl;


    start_time = clock();
    for(int i = 0; i < 10; i++) {
        start_time = clock();
        build_tree_using_pairing_heap(freq_table);
    }
    cout << "Time using pairing heap (microsecond):  " << (clock() - start_time)/10 << endl;

}
