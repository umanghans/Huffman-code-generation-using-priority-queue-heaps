struct min_queue {
    struct min_queue *left;
    struct min_queue *right;
    int data;
    int freq;
};

void insert_element(struct min_queue e);
struct min_queue remove_min();


