#include <unordered_map>
#include <vector>

struct pairingheapelement {
    struct min_queue key;
    struct pairingheapelement *left;
    struct pairingheapelement *prev;
    struct pairingheapelement *next;
};

void build_tree_using_pairing_heap(std::unordered_map<int,int> &);

