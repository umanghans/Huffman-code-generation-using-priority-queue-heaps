#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits.h>
#include <fstream>
#include "min_queue.h"

using namespace std;

extern vector<min_queue> four_way_heap;


void heapify_up_four_way()
{
        int index;
        index = four_way_heap.size() - 1;

        while(index > 3)
        {
            if(four_way_heap[index].freq <
               four_way_heap[(index + 8)/ 4].freq)
            {
                swap(four_way_heap[index] , four_way_heap[(index + 8)/ 4]);
                 index = (index + 8)/ 4;
            }
            else
            {
                break;
            }
        }

}

void heapify_down_four_way()
{
        int index;
        index = 3;

         while(index >= 3 && index < four_way_heap.size()) {
         	struct min_queue min_ele = four_way_heap[index];
            int j = -1;
            for(int i = 1; i <= 4; i++) {
                 int child_index = 4 * index - (i + 4);
                  if(child_index < four_way_heap.size()) {
                     if( four_way_heap[child_index].freq < min_ele.freq) {
                         min_ele = four_way_heap[child_index];
                         j = child_index;
                     }
                 }
             }
              if(j != -1) {
                 four_way_heap[j] = four_way_heap[index];
                 four_way_heap[index] = min_ele;
                 index = j;
             }
             else {
                 break;
             }
         }
}

struct min_queue remove_min_four_way_heap()
{
        struct min_queue mq;

        mq = four_way_heap[3];


       struct min_queue node;
       node.data = four_way_heap[four_way_heap.size() - 1].data;
       node.freq = four_way_heap[four_way_heap.size() - 1].freq;
       node.left = four_way_heap[four_way_heap.size() - 1].left;
       node.right = four_way_heap[four_way_heap.size() - 1].right;

       four_way_heap.pop_back();

        if(four_way_heap.size() > 3)
        {
            four_way_heap[3] = node;
            heapify_down_four_way();
        }

        return mq;
}

void insert_four_way_heap(struct min_queue mq)
{
    		four_way_heap.push_back(mq);
			heapify_up_four_way();
}

void build_four_way_heap(unordered_map<int,int> &freq_table)
{
    struct min_queue mq;
auto i = freq_table.begin();
    while(i != freq_table.end()){
            mq.left = NULL;
            mq.right = NULL;
            mq.data = i->first;
            mq.freq = i->second;
            insert_four_way_heap(mq);
            i++;
    }
}

void build_tree_using_4way_heap(std::unordered_map<int,int> &freq_table)
{
    struct min_queue mq;
    unordered_map<int, string> code_table;
    mq.data = -1;
    mq.freq = -1;
    mq.left = NULL;
    mq.right = NULL;

    four_way_heap.clear();

    insert_four_way_heap(mq);
    insert_four_way_heap(mq);
    insert_four_way_heap(mq);
    build_four_way_heap(freq_table);

      while( (four_way_heap.size() - 3) > 1) {

        struct min_queue mq_min1;
        struct min_queue mq_min2;
        struct min_queue new_ele;

        mq_min1 = remove_min_four_way_heap();
        mq_min2 = remove_min_four_way_heap();
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

        insert_four_way_heap(new_ele);

    }

}

