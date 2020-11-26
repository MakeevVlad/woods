#include <iostream>
#include<vector>

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
private:
    T value;
    size_t height;
    Node* left;
    Node* right;
public:
    Node(T value_);

    Node* insert(T value_);

    bool erase(T value_);

    ~Node(){};
};

template<typename T, class Node_>
class AVLtree : public AbstractTree<T, Node_>
{
private:
    Node_* root;

public:
    AVLtree();

    AVLtree(T value_);

    AVLtree(std::vector<T> values_)
    {
        for(auto value_ : values_)
            root = new Node_(value_);
    }

    Node_* insert(T value);

    Node_* find(T value);

    bool erase(T value);

    ~AVLtree(){};

};
