#include <unordered_map>
#include <limits.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "min_queue.h"
#include "huffman_pairing_heap.h"

using namespace std;

struct pairingheapelement *root_ph;
unsigned int ph_size = 0;

struct pairingheapelement * compare_and_link(struct pairingheapelement *first, struct pairingheapelement *second)
{
    if (second == NULL) {
        return first;
    }
    if (second->key.freq < first->key.freq)
    {
        second->prev = first->prev;
        first->prev = second;
        first->next = second->left;
        if (first->next != NULL)
            first->next->prev = first;
        second->left = first;
        first = second;
        return second;
    }
    else
    {
        second->prev = first;
        first->next = second->next;
        if (first->next != NULL)
            first->next->prev = first;
        second->next = first->left;
        if (second->next != NULL)
            second->next->prev = second;
        first->left = second;
        return first;
    }
}

struct pairingheapelement * combine_siblings(struct pairingheapelement*first_sibling)
{
    if (first_sibling->next == NULL)
        return first_sibling;
    static vector<struct pairingheapelement *> tree_array(5);
    int num_siblings = 0;
    for (; first_sibling != NULL; num_siblings++)
    {
        if (num_siblings == tree_array.size())
            tree_array.resize(num_siblings * 2);
        tree_array[num_siblings] = first_sibling;
        first_sibling->prev->next = NULL;
        first_sibling = first_sibling->next;
    }
    if (num_siblings == tree_array.size())
        tree_array.resize(num_siblings + 1);
    tree_array[num_siblings] = NULL;
    int i = 0;
    for (; i + 1 < num_siblings; i += 2)
       tree_array[i] =  compare_and_link(tree_array[i], tree_array[i + 1]);
    int j = i - 2;
    if (j == num_siblings - 3)
        tree_array[j] = compare_and_link (tree_array[j], tree_array[j + 2]);
    for (; j >= 2; j -= 2)
        tree_array[j-2] = compare_and_link(tree_array[j - 2], tree_array[j] );
    return tree_array[0];
}


struct min_queue remove_min_ph()
{

    struct pairingheapelement *old_root = root_ph;
    struct min_queue removed;

    removed.data = root_ph->key.data;
    removed.freq = root_ph->key.freq;
    removed.left = root_ph->key.left;
    removed.right = root_ph->key.right;

    if(root_ph->left ==  NULL) {
        root_ph = NULL;
    } else {
        root_ph = combine_siblings(root_ph->left);
    }

    delete old_root;
    ph_size--;
    return removed;

}

void insert_element_ph(struct min_queue x)
{
    struct pairingheapelement *new_node;
    new_node = (struct pairingheapelement *)malloc(sizeof(struct pairingheapelement));

    new_node->key.data = x.data;
    new_node->key.freq = x.freq;
    new_node->key.left = x.left;
    new_node->key.right = x.right;
    new_node->left = NULL;
    new_node->next = NULL;
    new_node->prev = NULL;
    ph_size++;


    if(root_ph == NULL) {
        root_ph = new_node;
    } else {
        compare_and_link(root_ph, new_node);
    }

}

void build_pairing_heap(unordered_map<int,int> &freq_table)
{
    struct min_queue mq;
    for(auto i = freq_table.begin(); i != freq_table.end(); i++) {
            mq.left = NULL;
            mq.right = NULL;
            mq.data = i->first;
            mq.freq = i->second;
            insert_element_ph(mq);
    }
}

void build_tree_using_pairing_heap(unordered_map<int,int> &freq_table)
{

    root_ph = NULL;

    build_pairing_heap(freq_table);


    while(root_ph->left != NULL) {

        struct min_queue mq_min1;
        struct min_queue mq_min2;
        struct min_queue new_ele;

        mq_min1 = remove_min_ph();
        mq_min2 = remove_min_ph();

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

        insert_element_ph(new_ele);

    }

}
