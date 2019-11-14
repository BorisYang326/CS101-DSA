#include <iostream>

using namespace std;

class Min_Heap {
public:
    int *Main_array;
    int cur_size;
    int max_size;

    Min_Heap(int max_size);

    ~Min_Heap();

    int *array_head();

    bool is_empty();

    bool is_full();

    void percolate(int index);

    void raw_push(int element);

    void maintain_up(int index);

    void stable_pop();

    int top();
};

Min_Heap::Min_Heap(int m) : cur_size(m), max_size(m) {
    Main_array = new int[cur_size + 1];
}

Min_Heap::~Min_Heap() {
    if (!is_empty()) {
        delete[]Main_array;  // necessary empty()
    }
}

int *Min_Heap::array_head() {
    return Main_array;
}

bool Min_Heap::is_empty() {
    return cur_size == 1;
}

bool Min_Heap::is_full() {
    return cur_size == max_size;
}

void Min_Heap::raw_push(int element) {
    if (!is_full()) {
        cur_size++;
        Main_array[cur_size] = element;
    }
}

void Min_Heap::percolate(int index) {
    if (index <= max_size) {
        if (Main_array[index] < std::min(Main_array[2 * index], Main_array[2 * index + 1])) {
            return; //Default all value is distinct.
        } else {
            int child_index = Main_array[2 * index] > Main_array[2 * index + 1] ? 2 * index + 1 : 2 * index;
            swap(Main_array[index], Main_array[child_index]);
            percolate(child_index);
        }
    }
}

int Min_Heap::top() {
    return Main_array[1];
}

void Min_Heap::maintain_up(int index) {
//    if (!is_full()) {
//        cur_size++;
//        Main_array[cur_size] = element;
        int temp_index = index;
        while (temp_index > 1) {
            if (Main_array[temp_index] > Main_array[temp_index / 2]) {
                int parent_index = temp_index / 2;
                swap(Main_array[temp_index], Main_array[temp_index / 2]);
                temp_index = parent_index;
            } else { break; }
        }
    //}
}

void Min_Heap::stable_pop(){
    if(cur_size>1) {
        swap(Main_array[cur_size], Main_array[1]);
        maintain_up(cur_size);
    }
}