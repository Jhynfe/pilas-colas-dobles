#include <iostream>
#include <algorithm>
using namespace std;
//pila
template<typename data_type>
struct Stack {
    struct StackNode {
        data_type data;
        StackNode *next;
    };

    StackNode *_top;
    Stack() {
        _top = nullptr;
    }

    void push(data_type data) {
        StackNode *node = new StackNode(data);
        node->next = _top;
        _top = node;
    }
    void pop() {
        if (empty()) return;
        StackNode* aux = _top; _top = _top->next;
        delete aux;
    }

    data_type top() {
        return _top == nullptr ? data_type() : _top->data;
    }

    bool empty() {
        return _top == nullptr ? true : false;
    }
    void imprimir() {
        StackNode * rr = _top;
        while (rr != nullptr) {
            cout << rr->data << " ";
            rr = rr->next;
        }
    }
};
//stack max
template<typename data_type>
struct StackM {
    struct StackNode {
        data_type data;
        StackNode *next;
        data_type max;
        StackNode(data_type data, data_type max_) : data(data), next(nullptr), max(max_) {}
    };

    StackNode *_top;
    StackM() {
        _top = nullptr;
    }

    void push(data_type data) {
        data_type mx;
        if (empty()) {
            mx = data;
        }
        else {
            mx = max(data, _top->max);
        }
        StackNode *node = new StackNode(data, mx);
        node->next = _top;
        _top = node;
    }
    void pop() {
        if (empty()) return;
        StackNode* aux = _top;
        _top = _top->next;
        delete aux;
    }
    data_type maximus() {
        return _top->max;
    }
    data_type top() {
        return _top == nullptr ? data_type() : _top->data;
    }

    bool empty() {
        return _top == nullptr ? true : false;
    }
    void imprimir() {
        StackNode * rr = _top;
        while (rr != nullptr) {
            cout << rr->data << " ";
            rr = rr->next;
        }
    }
};


//cola
template<typename data_type>
struct Queue {

    struct QueueNode {
        data_type data;
        QueueNode* next;

        QueueNode(const data_type& d)
            : data(d), next(nullptr) {}
    };

    QueueNode* _front;
    QueueNode* _back;

    Queue() {
        _front = _back = nullptr;
    }

    bool empty() {
        return _front == nullptr;
    }

    void push(data_type x) {

        QueueNode* nuevo = new QueueNode(x);

        if (empty()) {
            _front = _back = nuevo;
        }
        else {
            _back->next = nuevo;
            _back = nuevo;
        }
    }

    void pop() {

        if (empty())
            return;

        QueueNode* aux = _front;

        _front = _front->next;

        delete aux;

        if (_front == nullptr)
            _back = nullptr;
    }

    data_type front() {
        return _front->data;
    }

};

//cola dobleeee
template<typename data_type>
struct Deque {
    struct DequeNode {
        data_type data;
        DequeNode *next;
        DequeNode *prev;
        DequeNode() {
            next= prev = NULL;
        }
        DequeNode(data_type d) {
            data= d;
            next= prev= NULL;
        }
    };
    DequeNode *_front, *_back;
    Deque() {
        _front= _back= NULL;
    }
    void push_front(data_type d) {
        if (_front==nullptr) {
            _front= new DequeNode(d);
            _back= _front;
        }
        else {
            _front -> prev= new DequeNode(d);
            _front ->prev ->next  =_front ;
            _front = _front->next ;
        }
    }
    void push_back(data_type d) {
        if (_front == nullptr) {
            _front = new DequeNode(d);
            _back = _front;
        }
        else {
            _back -> next = new DequeNode(d);
            _back -> next->prev= _back;
            _back = _back->next;
        }
    }
    void pop_front() {
        if (_back!= nullptr) {
            _back = _back -> prev;
        }
        if (_back == nullptr) {
            _front = NULL;
        }
    }
    data_type front() {
        return _front -> data;
    }
    data_type back() {
        return _back -> data;
    }
    void pop_back() {
        if (_front != nullptr) {
            _front = _front -> next;
        }
        if (_front == nullptr) {
            _back = NULL;
        }
    }

    bool empty() {
        return  _front == nullptr;
    }
};
template<typename T>
struct QueueMax {
    Deque<T> q;       
    Deque<T> max_q;  

    void push(T x) {

        // Eliminamos candidatos que ya no pueden ser máximo
        while (!max_q.empty() && max_q.back() < x) {
            max_q.pop_back();
        }

        // Insertamos x en ambas estructuras
        q.push_back(x);
        max_q.push_back(x);
    }

    void pop() {

        if (q.empty()) return;

        T x = q.front();
        q.pop_front();

        // Si el elemento que salió era el máximo candidato,
        // también lo eliminamos de max_q
        if (!max_q.empty() && max_q.front() == x) {
            max_q.pop_front();
        }
    }

    T maximum() {
        return max_q.front();
    }

    bool empty() {
        return q.empty();
    }
};


int main() {

    int n;
    cin >> n;

    QueueMax<int> Q;

    while (n--) {

        int tipo;
        cin >> tipo;

        if (tipo == 1) {

            int x;
            cin >> x;

            Q.push(x);

        }
        else if (tipo == 2) {

            Q.pop();

        }
        else if (tipo == 3) {

            cout << Q.maximum() << '\n';

        }
    }

    return 0;
}
