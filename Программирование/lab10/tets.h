#ifndef UNTITLED1_TETS_H
#define UNTITLED1_TETS_H
#include <iostream>
#include <stack>
using namespace std;
static const  string TRUE = "true";
static const string FALSE = "false";

template <typename T>
struct Node {
    T key;
    Node<T> *left;
    Node<T> *right;
    int height;
};

template <typename T>
class btIter {
public:
    btIter(Node<T> *p) : nodePtr(p) {}

    bool operator== (const btIter& item) const
    {
        return item.nodePtr == this->nodePtr;
    }

    bool operator!= (const btIter& item) const
    {
        return item.nodePtr != this->nodePtr;
    }

    T& operator* () const
    {
        return this->nodePtr->key;
    }

    stack<Node<T> > node_stack;
    btIter& operator++() {
        if(nodePtr != nullptr) {
            if(nodePtr->right != nullptr) {
                node_stack.push(*nodePtr->right);
            }
            if(nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
            else {
                nodePtr = node_stack.top();
                node_stack.pop();
            }
        }
        return *this;
    }

    btIter operator++(int) {
        if(nodePtr != nullptr) {
            if(nodePtr->right != nullptr) {
                node_stack.push(*nodePtr->right);
            }
            if(nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
            else {
                nodePtr = &node_stack.top();
                node_stack.pop();
            }
        }
        return *this;
    }

private:
    Node<T> *nodePtr;
};

template <typename T, class Compare = less<T> >
class AVLTree {
    typedef btIter<T> iterator;
    typedef btIter<T> constIterator;
public:
    AVLTree() {
        head = nullptr;
    }

    AVLTree(const AVLTree &avlTree) {
        head = nullptr;
        head->left = avlTree.head->left;
        head->right = avlTree.head->right;
    }

    ~AVLTree() {
        delete head;
    }

    AVLTree& operator=(const AVLTree& avlTree) {
        _size = avlTree._size;
        head = new Node<T>;
        head->key = avlTree.head->key;
        head->left = avlTree.head->left;
        head->right = avlTree.head->right;
        head->height = avlTree.head->height;

        return *this;
    }

    template<class InputIt>
    void del(InputIt first, InputIt last)
    {
        AVLTree<int> tree;

        if (head != nullptr)
            delete head;

        for (InputIt i = first; i != last; i++)
        {
            insert(*(i));
        }
    }

    iterator begin() {
        return iterator(head);
    }

    constIterator cbegin() {
        return iterator(head);
    }

    iterator end() {
        btIter<T> n = iterator(head);
        int s = _size;

        while (s != 1 )
        {
            n++;
            s--;
        }
        return n;
    }

    constIterator cend() {
        btIter<T> n = iterator(head);
        int s = _size;

        while (s != 1 )
        {
            n++;
            s--;
        }
        return n;
    }

    iterator insert(const T &key){
        _size++;
        Node<T> *res = head;
        insNode(head, key, &res);

        return iterator(res);
    }

    iterator Delete(const T &key){
        _size--;
        Node<T> *res;
        delNode(head, key, &res);

        return iterator(res);
    }

    iterator find(const T key) {
        if (ExistNode(head, key) != nullptr)
            return iterator(ExistNode(head, key)); // Проверка на существование
        else
            cout << "Error";
    }

    constIterator cfind(const T key) {
        if (ExistNode(head, key) != nullptr)
            return iterator(ExistNode(head, key)); // Проверка на существование
        else
            cout << "Error";
    }

    size_t size() const {
        return _size;
    };

    bool empty() const {
        return head == nullptr;
    };

private:
    Node<T> *head;
    int _size = 0;

    Node<T> *next(Node<T> *node) {
        Node<T> *current = node->right;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    int height(const Node<T> * const node) const{
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(const Node<T> * const node) const{
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    void leftRotate(Node<T>*& node) {
        Node<T>* result = node->right;
        Node<T>* tmp = result->left;

        result->left = node;
        node->right = tmp;

        node->height = max(height(node->left), height(node->right)) + 1;
        result->height = max(height(result->left), height(result->right)) + 1;

        node = result;
    }

    void rightRotate(Node<T>*& node) {
        Node<T>* result = node->left;
        Node<T>* tmp = result->right;

        result->right = node;
        node->left = tmp;

        node->height = max(height(node->left), height(node->right)) + 1;
        result->height = max(height(result->left), height(result->right)) + 1;

        node = result;
    }

    void insNode(Node<T>*& node, const T key, Node<T>** res) {
        if (node == nullptr) {
            node = new Node<T>;
            node->key = key;
            node->left = nullptr;
            node->right = nullptr;
            node->height = 1;
            *res = node;
        }

        if (key < node->key)
            insNode(node->left, key, res);
        else if (key > node->key)
            insNode(node->right, key, res);

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            rightRotate(node);
            return;
        }

        if (balance < -1 && key > node->right->key) {
            leftRotate(node);
            return;
        }

        if (balance > 1 && key > node->left->key)
        {
            leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            rightRotate(node->right);
            return leftRotate(node);
        }
    }

    void delNode(Node<T>*& node, T key, Node<T>** res) {
        if (node == nullptr)
            return;

        if ( key < node->key )
            delNode(node->left, key, res);

        else if( key > node->key )
            delNode(node->right, key, res);

        else
        {
            if( (node->left == nullptr) || (node->right == nullptr) )
            {
                Node<T> *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                *res = temp;
            }
            else
            {
                Node<T>* temp = next(node);

                node->key = temp->key;

                delNode(node->right, temp->key, res);
            }
        }

        if (node == nullptr)
            return;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            rightRotate(node);
            return;
        }

        if (balance > 1 && getBalance(node->left) < 0)
        {
            leftRotate(node->left);
            rightRotate(node);
            return;
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            leftRotate(node);
            return;
        }

        if (balance < -1 && getBalance(node->right) > 0)
        {
            rightRotate(node->right);
            leftRotate(node);
            return;
        }
    }

    Node<T>* ExistNode(Node<T> *& node, const int key) {
        if (node == nullptr)
            return nullptr;
        if (node->key == key)
            return node;
        if (node->key > key)
            return ExistNode(node->left, key);
        else
            return ExistNode(node->right, key);
    }
};
#endif //UNTITLED1_TETS_H

