#include <iostream>
#include <vector>
#include <memory>

template<typename T, class Node_>
class AbstractTree
{
public:
    virtual Node_* find(T value_)
    {
        return nullptr;
    }

    virtual Node_* insert(T value_)
    {
        return nullptr;
    }
    
    virtual bool erase(T value_)
    {
        return 0;
    }
};


template<typename T>
class Node
{
public:
    T value;
    size_t height;
    Node<T>* left;
    Node<T>*  right;

    Node();
    Node(T value_);

    Node<T>* insert(T value_);

    Node<T>* find(T value_);
    
    Node<T>* erase(T value_);

    void reheight();

    int balance_factor();

    Node<T>* right_rotation();
    Node<T>* left_rotation();

    Node<T>* rebalance();

    Node<T>* min_knot();
    Node<T>* min_erase();

    T show()
    {
        return value;
    }
    void clear();

};
template<typename T>
size_t get_height(Node<T>*);

template<typename T, class Node_ = Node<T>>
class AVLtree : public AbstractTree<T, Node_>
{
public:
    Node_* root;

    AVLtree();

    AVLtree(T value_);

    AVLtree(std::vector<T> values_)
    {
        for(auto value_ : values_)
            root =  new Node_(value_);
    }

    Node_* insert(T value);

    Node_* find(T value);

    bool erase(T value);

    ~AVLtree();
};
