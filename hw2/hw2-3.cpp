//
// Created by Borisss_Yang on 2019/10/30.
//
#include<iostream>

using namespace std;

class Layer {
public:
    int label_index;
    int quantity;

    Layer(int= -1, int= 0);

    ~Layer();
    // void push_rule(int,int,int);
};

Layer::Layer(int x1, int x2) : label_index(x1), quantity(x2) {
}

Layer::~Layer() {

}

//Node class
class Node {
public:
    Layer *element;
    Node *next_node;
    Node *front_node;

    Node(Layer * = NULL, Node * = NULL, Node * = NULL);

    Layer *retrieve();

    Node *next();

    Node *front();
    //friend class List;

};

Node::Node(Layer *l, Node *n, Node *f) :
        element(l), next_node(n), front_node(f) {
    //empty constructor
}

Layer *Node::retrieve() {
    return element;
}

Node *Node::next() {
    return next_node;
}

Node *Node::front() {
    return front_node;
}

//class underflows
class underflow {
};

//List class
class List {
private:
    Node *list_head;
    Node *list_tail;
public:
    List();

    ~List();

    bool empty() const;

    //int size() const;
    Layer *front() const;

    Node *head() const;

    Node *tail() const;

    // int count(int) const;
    void push_front(Layer *);

    void pop_front();

    void pop_back();

    // void erase(int);
    void Insert(Layer *);
};

List::List() : list_tail(NULL) {
    list_head = new Node;
    list_head = NULL;
}

List::~List() {
    while (!empty()) {
        pop_front();
    }
    delete list_head;
    list_head = NULL;
}

bool List::empty() const {
    return list_head == NULL;
}

Node *List::head() const {
    return list_head;
}

Node *List::tail() const {
    return list_tail;
}

Layer *List::front() const {
//    if(empty()){
//        throw underflow();
//    }
    return head()->retrieve();
}


void List::push_front(Layer *n) {
    Node *tem = new Node(n, NULL, NULL);
    if (list_tail == NULL) {
        list_head = list_tail = tem;
    } else {
        list_head->front_node = tem;
        tem->next_node = list_head;
        list_head = tem;
    }
}

void List::pop_front() {
//    if(empty()){
//        throw underflow();
//    }

    // int* e;
    // e[0]=front()->label_index;
    // e[1]=front()->quantity;
    Node *ptr = list_head;
    // 1 2
    if (list_head->next_node == NULL) {
        list_head = NULL;
        delete ptr;
        list_tail = NULL;
    } else {
        list_head = list_head->next_node;
        list_head->front_node = NULL;
        delete ptr;
    }
    // return e;
}

void List::pop_back() {
    Node *ptr = list_tail;

    // 1

    list_tail = list_tail->front_node;
    if (list_tail == NULL) { list_head = NULL; }
    else { list_tail->next_node = NULL; }
    delete ptr;
}

bool Is_Legal(Layer *layer1, Layer *layer2, int **rule) {
    return rule[layer1->label_index][layer2->label_index] != -1;
}

void Merge(List *fu_list, Layer *layer_in, Layer *layer_out, int **rule) {
    //for (Node *ptr = fu_list->head(); ptr != NULL; ptr = ptr->next()) {
    // cout << ptr->element->quantity << ":" << ptr->element->label_index << endl;
    //}
    if (layer_in->label_index != layer_out->label_index) {
        if (!fu_list->empty() && (Is_Legal(layer_in, layer_out, rule))) {
            if (layer_in->quantity == 0) { fu_list->pop_front(); }
            if (layer_in->quantity == layer_out->quantity) {
                int temp_in_label_index_1;
                int temp_in_quantity_1;
                layer_in->label_index = rule[layer_out->label_index][layer_in->label_index];
                //layer_out->quantity -= layer_in->quantity;
                temp_in_label_index_1 = layer_in->label_index;
                temp_in_quantity_1 = layer_in->quantity;
                fu_list->pop_front();
                Layer *new_layer_in = new Layer(temp_in_label_index_1, temp_in_quantity_1);
                if (!fu_list->empty()) {
                    Merge(fu_list, fu_list->head()->element, new_layer_in, rule);
                } else { fu_list->push_front(new_layer_in); }
            } else if (layer_in->quantity > layer_out->quantity) {
                layer_in->quantity -= layer_out->quantity;
                layer_out->label_index = rule[layer_out->label_index][layer_in->label_index];
                if (!fu_list->empty()) {
                    Merge(fu_list, fu_list->head()->element, layer_out, rule);
                } else { fu_list->push_front(layer_out); }
            } else {
                int temp_in_label_index;
                int temp_in_quantity;
                layer_in->label_index = rule[layer_out->label_index][layer_in->label_index];
                layer_out->quantity -= layer_in->quantity;
                temp_in_label_index = layer_in->label_index;
                temp_in_quantity = layer_in->quantity;
                fu_list->pop_front();
                Layer *new_layer_in = new Layer(temp_in_label_index, temp_in_quantity);
                if (!fu_list->empty()) {
                    Merge(fu_list, fu_list->head()->element, new_layer_in, rule);
                } else { fu_list->push_front(new_layer_in); }
                if (!fu_list->empty()) {
                    Merge(fu_list, fu_list->head()->element, layer_out, rule);
                } else { fu_list->push_front(new_layer_in); }
                // Merge(fu_list,fu_list->head()->element,layer_out,rule);
            }
        } else { fu_list->push_front(layer_out); }
    } else {
        layer_in->quantity += layer_out->quantity;
        delete layer_out;
    }

}

int count_layers(List *fu_list) {
    int count = 0;
    for (Node *ptr = fu_list->head(); ptr != NULL; ptr = ptr->next()) {
        //cout<<ptr->element->quantity<<":"<<ptr->element->label_index<<endl;
        count += ptr->element->quantity;
    }
    return count;
}

void Fu_pop(List *fu_list, int quant) {
    int tem_quant = 0;
    if (!fu_list->empty()) {
        if (quant < fu_list->tail()->element->quantity) {
            fu_list->tail()->element->quantity -= quant;
        } else {
            tem_quant = quant - fu_list->tail()->element->quantity;
            fu_list->pop_back();
            Fu_pop(fu_list, tem_quant);
        }
    }
}

int main() {
    int **rule = new int *[3000];
    for (int i = 0; i < 3000; ++i) {
        rule[i] = new int[3000];
    }
    for (int i = 0; i < 3000; i++) {
        for (int j = 0; j < 3000; j++) { rule[i][j] = -1; }
    }
    List ins_fu_list;
    int final_result = -1;
    int arr[3];
    int tem_1, index = 0;
    for (int i = 0; i < 3; i++) {
        cin >> arr[i];
    }

//    while(cin>>tem_1){
//        cout<<tem_1<<endl;
//        arr[index++] = tem_1;
//        char ch = getchar();//
//        if(ch == '\n')
//            break;
//    }
    int rul_1 = -1, rul_2 = -1, rul_3 = -1;
    for (int i = 0; i < arr[1]; i++) {
        cin >> rul_1 >> rul_2 >> rul_3;
//        cout<<rul_1<<rul_2<<rul_3<<endl;
        rule[rul_1][rul_2] = rul_3;
        rule[rul_2][rul_1] = rul_3;
    }
    //cout<<rule[0][3]<<endl;
    int opr_1 = -2, opr_2 = -1;
    for (int j = 0; j < arr[2]; j++) {
        cin >> opr_1 >> opr_2;
//    cout<<opr_1<<opr_2<<endl;
        if (opr_1 == -1) {
            if (ins_fu_list.empty()) {
                if (opr_2 == 0) final_result = 0;
                else throw std::underflow_error("");
            } else { Fu_pop(&ins_fu_list, opr_2); }
        } else {
            Layer *new_layer = new Layer(opr_1, opr_2);
            if (ins_fu_list.empty()) { ins_fu_list.push_front(new_layer); }
            else { Merge(&ins_fu_list, ins_fu_list.head()->retrieve(), new_layer, rule); }
        }
    }
    final_result = count_layers(&ins_fu_list);
    cout << final_result << endl;
    for (int i = 0; i < 3000; i++)
        delete[] rule[i];
    delete[] rule;
    rule = NULL;

    return 0;
}