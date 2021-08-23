#include <iostream>
using namespace std;
static const  string TRUE = "true";
static const string FALSE = "false";

template <typename T>
struct Node {
    T key;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
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
        _size = 0;
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
        return LastNode(head);
    }

    constIterator cend() {
        return LastNode(head);
    }

    iterator insert(const T &key){
        Node<T> *res = head;
        insNode(head, key, &res);
        _size++;
        return iterator(res);
    }

    iterator Delete(const T &key){
        _size--;
        Node<T> *res;
        delNode(head, key, &res);

        return iterator(res);
    }

    iterator find(const T key) {
        return iterator(ExistNode(head, key));
    }

    constIterator cfind(const T key) {
        return iterator(ExistNode(head, key));
    }

    size_t size() const {
        return _size;
    };

    bool empty() const {
        return head == nullptr;
    };

private:
    Node<T> *head;
    int _size;

    void insNode(Node<T>*& node, const T key, Node<T>** res) {
        if (_size == 0) {
            node = new Node<T>;
            node->key = key;
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
            *res = node;
        } else {
            Node<T> *parent_ = nullptr;

            while (node != nullptr) {
               if (key < node->key) {
                    parent_ = node;
                    node = node->left;
                }
                else if (key > node->key) {
                    parent_ = node;
                    node = node->right;
                }
            }

            node = new Node<T>;
            node->key = key;
            node->parent = parent_;
            node->right = nullptr;
            node->left = nullptr;

            if (key < parent_->key)
                parent_->left = node;
            else parent_->right = node;
            *res = node;

            while(node->parent != nullptr)
                node = node->parent;
        }
    }

    void delNode(Node<T>*& node, T key, Node<T>** res) {
        Node<T>* temp;
        if (node->key == key) {
            temp = node;
            *res = node;
            if(temp->left == nullptr && temp->right==nullptr) { //остался только корень
                node = nullptr;
                return;
            }

            if(temp->right == nullptr) //от корня слева
            {
                temp = temp->left;
                if(temp->right == nullptr) //ответвление слева не имеет правого поддерева
                {
                    node = node->left;
                    node->parent = nullptr;
                    return;
                }
                else{
                    while(temp->right!=nullptr)
                        temp=temp->right;
                    node->key = temp->key;
                    node->parent = nullptr;
                    temp->parent->right = nullptr;
                    return;
                }
            }

            if(temp->left == nullptr) //от корня справа
            {
                temp = temp->right;
                if(temp->left == nullptr) //ответвление справа не имеет левого поддерева
                {
                    node = node->right;
                    node->parent = nullptr;
                    return;
                }
                else{
                    while(temp->left!=nullptr)
                        temp=temp->left;
                    node->key = temp->key;
                    node->parent = nullptr;
                    temp->parent->left = nullptr;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
            }
            if(temp->left != nullptr && temp->right != nullptr)
            {
                temp = temp->right;
                if(temp->left == nullptr) //ответвление справа не имеет левого поддерева
                {
                    node->right->left = node->left;
                    node = node->right;
                    node->parent = nullptr;
                    return;
                }
                else{
                    while(temp->left!=nullptr)
                        temp=temp->left;
                    node->key = temp->key;
                    node->parent = nullptr;
                    temp->parent->left = nullptr;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
            }
        }
        else {
            while (node->key != key) {
                if (key < node->key)
                    node = node->left;
                else if (key > node->key)
                    node = node->right;
            }
            temp = node;
        }
        *res = node;
        if(temp->right == nullptr && temp->left == nullptr) {
            if (temp->parent->key > temp->key)
                temp->parent->left == nullptr;
            else temp->parent->right == nullptr;
            while(node->parent != nullptr)
                node = node->parent;
            return;
        }
        if(temp->right == nullptr) {
            if (temp->parent->key > temp->key) //слева от родительского
            {
                Node<T>* temp1 = temp;
                temp1 = temp1->left;
                if(temp1->right == nullptr)
                {
                    node->left = temp1;
                    node->left->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
                else
                {
                    while(temp1->right != nullptr)
                        temp1 = temp1->right;
                    temp1->parent->right = nullptr;
                    node->left = temp1;
                    node->left->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
            }
            else  //справа от родительского
            {
                Node<T>* temp1 = temp;
                temp1 = temp1->left;
                if(temp1->right == nullptr)
                {
                    node->right = temp1;
                    node->right->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
                else
                {
                    while(temp1->right != nullptr)
                        temp1 = temp1->right;
                    temp1->parent->right = nullptr;
                    node->right = temp1;
                    node->right->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
            }
        }
        if(temp->left == nullptr)
        {
            if (temp->parent->key > temp->key) //слева от родительского
            {
                Node<T>* temp1 = temp;
                temp1 = temp1->right;
                if(temp1->left == nullptr)
                {
                    node->left = temp1;
                    node->left->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
                else
                {
                    while(temp1->left != nullptr)
                        temp1 = temp1->left;
                    temp1->parent->left = nullptr;
                    node->left = temp1;
                    node->left->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
            }
            else  //справа от родительского
            {
                Node<T>* temp1 = temp;
                temp1 = temp1->right;
                if(temp1->left == nullptr)
                {
                    node->right = temp1;
                    node->right->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
                else
                {
                    while(temp1->left != nullptr)
                        temp1 = temp1->left;
                    temp1->parent->right = nullptr;
                    node->right = temp1;
                    node->right->parent = node;
                    while(node->parent != nullptr)
                        node = node->parent;
                    return;
                }
            }
        }
        if(temp->right != nullptr && temp->left != nullptr) //справа и слева есть звенья
        {
            Node<T>* Left = node->left;
            temp = temp->right;
            while(temp->left != nullptr)
                temp = temp->left;
            node->key = temp->key;
            temp->parent->left = nullptr;
            while(node->parent != nullptr)
                node = node->parent;
            return;
        }

    }

    Node<T>* ExistNode(Node<T> *& node, const int key) {
        if (node->key == key)
            return node;
        while(node->key != key) {
            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
        }
        Node<T>* temp = node;
        while(node->parent != nullptr)
            node = node->parent;
        return temp;
    }

    Node<T>* LastNode(Node<T> *& node) {
        while(node->right != nullptr)
            node = node->right;
        Node<T>* temp = node;
        while(node->parent != nullptr)
            node = node->parent;
        return temp;
    }
};

int main()
{
    AVLTree<int> tree;
    cout << "Insert element: " << *tree.insert(3) << '\n';
    cout << "Insert element: " << *tree.insert(5) << '\n';
    cout << "Insert element: " << *tree.insert(2) << '\n';
    cout << "Insert element: " << *tree.insert(4) << '\n';
    cout << "First element: " << *tree.begin() << '\n';
    cout << "Last element: " << *tree.end() << '\n';
    cout << "Tree size: " << tree.size() << '\n';
    cout << "Is Empty: " << tree.empty() << '\n';
    cout << "Find element: " << *tree.find(2) << '\n';
    cout << "Delete element: " << *tree.Delete(3) << '\n';
    cout << "Find element: " << *tree.find(2) << '\n';
    cout << "Tree size: " << tree.size() << '\n';
 /*   cout << "Find element: " << *tree.find(5) << '\n';
    cout << "Delete element: " << *tree.Delete(5) << '\n';
    cout << "Find element: " << *tree.find(4) << '\n';
    cout << "Delete element: " << *tree.Delete(4) << '\n';
    cout << "Insert element: " << *tree.insert(1) << '\n';
    cout << "Tree size: " << tree.size() << '\n';
    cout << "Find element: " << *tree.find(3) << '\n';
    cout << "Find element: " << *tree.find(1) << '\n'; */

}