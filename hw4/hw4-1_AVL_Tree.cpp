//
// Created by Borisss_Yang on 2019/12/29.
//


#include <iostream>

using namespace std;

class node {
public:
    long key = 0;
    long value = 0;
    long height = 0;
    node *left = NULL;
    node *right = NULL;

    node(long key, long value, long height, node *l, node *r);
};

node::node(long key, long value, long height, node *l, node *r) : key(key), value(value), height(height), left(l),
                                                                  right(r) {};

class avl_tree {
public:
    node *root;

    avl_tree();

    ~avl_tree();

    void destory(node *in_node);

    long height(node *in_node);

    //long max(long a,long b);
    long search(node *in_node, long key);

    node *insert(long key, long value, node *in_node);

    node *rotateleft(node *in_node);

    node *rotateright(node *in_node);

    long bal_factor(node *in_node);

    node *rotate_balance(node *node);
};

avl_tree::avl_tree() : root(NULL) {};

avl_tree::~avl_tree() { destory(root); };

void avl_tree::destory(node *in_node) {
    if (in_node != NULL) {
        destory(in_node->left);
        destory(in_node->right);
        delete in_node;
        in_node = nullptr;
    }
};

long avl_tree::height(node *in_node) {
    if (in_node == NULL) { return -1; }
    return in_node->height;
}

//long avl_tree::max(long a,long b){
//    if(a>b){return a;}
//    else{return b;}
//}
node *avl_tree::rotateleft(node *in_node) {
    node *right_node = in_node->right;
    in_node->right = right_node->left;
    right_node->left = in_node;
    in_node->height = 1 + max(height(in_node->left), height(in_node->right));
    right_node->height = 1 + max(height(right_node->left), height(right_node->right));
    return right_node;
}

node *avl_tree::rotateright(node *in_node) {
    node *left_node = in_node->left;
    in_node->left = left_node->right;
    left_node->right = in_node;
    in_node->height = 1 + max(height(in_node->left), height(in_node->right));
    left_node->height = 1 + max(height(left_node->left), height(left_node->right));
    return left_node;
}

long avl_tree::bal_factor(node *in_node) {
    return height(in_node->left) - height(in_node->right);
}

node *avl_tree::rotate_balance(node *in_node) {
    if (bal_factor(in_node) < -1) {
        if (bal_factor(in_node->right) > 0) {
            in_node->right = rotateright(in_node->right);
        }
        in_node = rotateleft(in_node);
    } else if (bal_factor(in_node) > 1) {
        if (bal_factor(in_node->left) < 0) {
            in_node->left = rotateleft(in_node->left);
        }
        in_node = rotateright(in_node);
    }
    return in_node;
}

node *avl_tree::insert(long key, long value, node *in_node) {
    if (in_node != NULL) {
        if (in_node->key > key) { in_node->left = insert(key, value, in_node->left); }
        else if (in_node->key < key) { in_node->right = insert(key, value, in_node->right); }
        else {
            in_node->value += value;
            return in_node;
        }
        in_node->height = 1 + max(height(in_node->left), height(in_node->right));
        return rotate_balance(in_node);
    } else { return new node(key, value, 0, NULL, NULL); }
}

long avl_tree::search(node *in_node, long key) {
    if (in_node != NULL) {
        if (in_node->key < key) {
            return search(in_node->right, key);
        } else if (in_node->key > key) {
            return search(in_node->left, key);
        } else { return in_node->value; }
    } else { return 0; }
}


long gcd(long x, long y) {
    long z = y;
    while (x % y != 0) {
        z = x % y;
        x = y;
        y = z;
    }
    return z;
}


int main() {
    long p, q;
    cin >> p;
    long *M = new long[p];
    for (long i = 0; i < p; i++)
        cin >> M[i];
    cin >> q;
    long *a = new long[q];
    for (long i = 0; i < q; i++) {
        cin >> a[i];
//        if(a[i]>k)
//            k=a[i];
    }
    //input done
    avl_tree tree;
    for (long x = 0; x < p; x++) {
        long temp = M[x];
        for (long y = x; y < p; y++) {
            long gcd_temp = gcd(temp, M[y]);
            if (gcd_temp == 1) {
                tree.root = tree.insert(1, p - y, tree.root);
                break;
            }
            tree.root = tree.insert(gcd_temp, 1, tree.root);
            temp = gcd_temp;
        }
    }
    for (int j = 0; j < q; ++j) {
        cout << tree.search(tree.root, a[j]) << " ";
    }
    return 0;
}