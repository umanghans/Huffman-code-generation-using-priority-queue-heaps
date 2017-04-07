#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "min_queue.h"

using namespace std;

vector<min_queue> min_q;

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return (2 * i + 1);
}

int right(int i)
{
    return (2 * i + 2);
}

void heapify_down(int i)
{
        int left_e = left(i);
        int right_e = right(i);

        int smallest = i;

        if (left_e < min_q.size() && min_q[left_e].freq <= min_q[i].freq)
            smallest = left_e;

        if (right_e < min_q.size() && min_q[right_e].freq <= min_q[smallest].freq)
            smallest = right_e;

        if (smallest != i) {
            swap(min_q[i], min_q[smallest]);
            heapify_down(smallest);
        }
}

void heapify_up(int i)
{
        if (i && min_q[parent(i)].freq >= min_q[i].freq)
        {
            swap(min_q[i], min_q[parent(i)]);

            heapify_up(parent(i));
        }
}

struct min_queue remove_min()
{
    struct min_queue mq;
    try {
            if ( min_q.size() == 0 )
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");

            mq = min_q[0];
            min_q[0] = min_q.back();
            min_q.pop_back();

            heapify_down(0);
        }

        catch (const out_of_range& ex) {
            cout << "\n" << ex.what();
        }

        return mq;
}

void insert_element(struct min_queue e)
{
        min_q.push_back(e);

        int index = min_q.size() - 1;
        heapify_up(index);
}
