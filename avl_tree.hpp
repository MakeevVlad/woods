#include <iostream>
#include <vector>
#include <memory>

template<typename T, class Node_>
class AbstractTree
{
public:
    virtual std::shared_ptr<Node_> find(T value_)
    {
        return nullptr;
    }

    virtual std::shared_ptr<Node_> insert(T value_)
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
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>>  right;

    Node();
    Node(T value_);

    std::shared_ptr<Node<T>> insert(T value_);

    std::shared_ptr<Node<T>> find(T value_);
    
    

    void reheight();

    int balance_factor();

    bool erase(T value_);

    std::shared_ptr<Node<T>> right_rotation();
    std::shared_ptr<Node<T>> left_rotation();

    std::shared_ptr<Node<T>> rebalance();

    T show()
    {
        return value;
    }

};
template<typename T>
size_t get_height(std::shared_ptr<Node<T>>);

template<typename T, class Node_ = Node<T>>
class AVLtree : public AbstractTree<T, Node_>
{
public:
    std::shared_ptr<Node_> root;

    AVLtree();

    AVLtree(T value_);

    AVLtree(std::vector<T> values_)
    {
        for(auto value_ : values_)
            root = std::shared_ptr<Node_> (new Node_(value_));
    }

    std::shared_ptr<Node_> insert(T value);

    std::shared_ptr<Node_> find(T value);

    bool erase(T value);

};
