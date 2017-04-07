#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <time.h>
#include "min_queue.h"
#include <limits.h>
#include <cstdlib>
#include <bitset>

using namespace std;

extern vector<min_queue> min_q;

void print_binary_heap()
{
    cout << "\n Min Binary Heap : ";
    for(auto i = 0; i < min_q.size(); i++) {
        cout << min_q[i].data   << "\t";
    }
}

void build_binary_heap(unordered_map<int,int> &freq_table)
{
    struct min_queue mq;
    for(auto i = freq_table.begin(); i != freq_table.end(); i++) {
            mq.left = NULL;
            mq.right = NULL;
            mq.data = i->first;
            mq.freq = i->second;
            insert_element(mq);
    }
}

void build_tree_using_binary_heap(unordered_map<int,int> &freq_table)
{
     unordered_map<int, string> code_table;
     min_q.clear();
     build_binary_heap(freq_table);

     while(min_q.size() > 1) {

        struct min_queue mq_min1;
        struct min_queue mq_min2;
        struct min_queue new_ele;

        mq_min1 = remove_min();
        mq_min2 = remove_min();
        new_ele.data = INT_MAX;
        new_ele.freq = mq_min1.freq + mq_min2.freq;
        struct min_queue *new1 = (struct min_queue *) malloc(sizeof(mq_min1));
        struct min_queue *new2 = (struct min_queue *) malloc(sizeof(mq_min2));

        new1->data = mq_min1.data;
        new1->freq = mq_min1.freq;
        new1->left = mq_min1.left;
        new1->right = mq_min1.right;

        new2->data = mq_min2.data;
        new2->freq = mq_min2.freq;
        new2->left = mq_min2.left;
        new2->right = mq_min2.right;

        new_ele.left = new1;
        new_ele.right = new2;

        insert_element(new_ele);

    }
}
