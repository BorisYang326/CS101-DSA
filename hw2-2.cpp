//
// Created by Borisss_Yang on 2019/10/30.
//

#include <iostream>
#include <math.h>
using namespace std;

class underflow {
};

template<typename T>
class Node {
public:
    T element;
    Node *next_node;

    Node(T const & = T(), Node * = nullptr);

    T retrieve();

    Node *next();
};

template<typename T>
Node<T>::Node(T const &e, Node<T> *next):element(e), next_node(next) {};

template<typename T>
T Node<T>::retrieve() {
    return element;
};

template<typename T>
Node<T> *Node<T>::next() {
    return next_node;
}

template<typename T>

class List {
private:
    Node<T> *list_head;
    Node<T> *list_tail;
    int size;
public:
    List(Node<T> * = nullptr, Node<T> * = nullptr, int = 0);

    Node<T> *head();

    Node<T> *tail();

    bool empty();

    void insert(T &node);

    int get_size() const;

};

template<typename T>
List<T>::List(Node<T> *head, Node<T> *tail, int n):list_head(head), list_tail(tail), size(n) {
}

template<typename T>
Node<T> *List<T>::head() {
    return list_head;
}

template<typename T>
int List<T>::get_size() const {
    return size;
}

template<typename T>
Node<T> *List<T>::tail() {
    return list_tail;
}

template<typename T>
bool List<T>::empty() {
    return list_head->next_node == NULL;
}

template<typename T>
void List<T>::insert(T &node) {
    if (list_head == NULL) {
        list_head = list_tail = new Node<T>(node);
        list_head->next_node = NULL;
        list_tail->next_node = NULL;
    } else {
        Node<T> *p = new Node<T>(node);
        list_tail->next_node = p;
        list_tail = p;
        list_tail->next_node = NULL;
    }
    size += 1;
}

//template <typename T>
class Tree {
private:
    int element;
    Tree *parent;
//    int decay_value;
    int test_value = 0;
public:
    int signal_max;
    int decay_value;
    int amp_count = 0;
    List<Tree *> children;

//    Tree(int = -9999, Tree * = nullptr , Node<Tree*> * = nullptr , Node<Tree*> * = nullptr, int = 0  );
    Tree(int = 0, Tree * = nullptr, int= -1, int= 0);

    int tree_retrieve() const;

    Tree *get_parent() const;

    int degree() const;

    bool is_root() const;

    bool is_leaf() const;

    Tree *get_child(int n);

    void attach(int const &n, int const &dv, int const &s_max);

    int recursive();

    void *search(int n);

};
Tree* search_add[20000] ;
Tree::Tree(int e, Tree *pa, int dv, int s_max) {
    search_add[e]= this;
    this->element = e;
    this->parent = pa;
    this->decay_value = dv;
    this->signal_max = s_max;
}


int Tree::tree_retrieve() const {
    return element;
}

Tree *Tree::get_parent() const {
    return parent;
}

bool Tree::is_root() const {
    return (get_parent() == nullptr);
}

bool Tree::is_leaf() const {
    return (degree() == 0);
}

int Tree::degree() const {
    return children.get_size();
}

Tree *Tree::get_child(int n) {
    if (n <= 0 || n > degree()) {
        return nullptr;

    }
    Node<Tree *> *ptr = children.head();
    for (int i = 1; i < n; ++i) {
        ptr = ptr->next();
    }
    return ptr->retrieve();
}

void Tree::attach(int const &n, int const &dv, int const &s_max) {
    Tree *new_tree = new Tree(n, this, dv, s_max);
    children.insert(new_tree);
}

int Tree::recursive() {
    if (!this->is_leaf()) {
        for (int i = 1; i < this->degree() + 1; i++) {
            this->get_child(i)->recursive();
        }
//        if(this->test_value>this->signal_max){
//           this->amp_count+=1;
//           this->test_value=0;
    }
    if (this->tree_retrieve() == 1) { return this->amp_count; }
    this->test_value += this->decay_value;
    if (this->test_value > this->signal_max) {
        this->amp_count += 1;
        this->test_value = decay_value;
    }
    this->get_parent()->test_value = std::max(this->test_value, this->get_parent()->test_value);
    this->get_parent()->amp_count += this->amp_count;

}

//void *Tree::search(int n) {
//    if (this->tree_retrieve() != n) {
//        if (!this->is_leaf()) {
//            for (int i = 1; i < this->degree() + 1; i++) {
//                this->get_child(i)->search(n);
//            }
//        }
//    } else {
//        search_add[n]= this;
//    }
//}

int main() {
//    Tree x1(1, nullptr, -1, 4);
//    x1.attach(2, 3, 4);
//    x1.attach(3, 1, 4);
//    x1.get_child(1)->attach(4, 2, 4);
//    x1.search(2);
//    Tree * x=search_add[2];
//    cout << x->decay_value << endl;
//    cout << x1.recursive() << endl;
    int node[1];
    int intial_max[1];
    int* input_array[2];
    cin>>node[0];
    input_array[0]=node;
//    for(int n=1;n<node[0]+1;n++){
//        int* arr=new int[100];//guess!
//        int a,index = 0;
//        while(cin>>a){
//            arr[index++] = a;
//            char ch = getchar();
//            if(ch == '\n')
//                break;
//        }
//        delete[] arr;
//    }
//    cin>>intial_max[0];
    intial_max[0]=0;
    Tree signal_tree(1, nullptr,-1);
    for(int n=1;n<node[0]+1;n++){
        int x;
        cin>>x;
//        signal_tree.search(n);
        if(x!=0){
            for(int k = 1;k<2*x+1;k+=2)
            {
                int t1=0;
                int t2=0;
                cin>>t1>>t2;
                search_add[n]->attach(t1,t2,intial_max[0]);
            }}
    }
    cin>>intial_max[0];
    for(int s=1;s<node[0]+1;s++){
        search_add[s]->signal_max=intial_max[0];
    }
    cout<<signal_tree.recursive();
    return 0;
}