#include "avl_tree.hpp"

//=====Constructors for AVLtree ==================================
template<typename T, class Node_>
AVLtree<T, Node_>::AVLtree()
{
    root = new Node_;
}

template<typename T, class Node_>
AVLtree<T, Node_>::AVLtree(T value_)
{
    root = new Node_(value_);
}

//====Functions for AVLtree======================================
template<typename T, class Node_>
std::shared_ptr<Node_> AVLtree<T, Node_>::insert(T value_)
{
    return root.insert(value_);
}
template<typename T, class Node_>
std::shared_ptr<Node_> AVLtree<T, Node_>::find(T value_)
{
    return root.find(value_);
}

template<typename T, class Node_>
bool AVLtree<T, Node_>::erase(T value_)
{
    return root.erase(value_);
}


//====Constructors for Node=========================================
template<typename T>
Node<T>::Node()
{
    value = 0;
    left = nullptr;
    right = nullptr;
    height = 0;
}

template<typename T>
Node<T>::Node(T value_)
{
    value = value_;
    left = nullptr;
    right = nullptr;
    height = 1;
}

//====Functions for Node=========================================
template<typename T>
size_t Node<T>::get_height()
{
    return this? this->height : 0;
}

template<typename T>
void Node<T>::reheight()
{
    this->height = std::max(get_height(this->left), get_height(this->right)) + 1;
}

template<typename T>
int Node<T>::balance_factor()
{
    return get_height(this->right) - get_height(this->left);
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>:: right_rotaion()
{
    std::shared_ptr<Node<T>> node_tmp = this->left;
    this->left = node_tmp->right;
    node_tmp->right.reset(this);
    this->reheight();
    node_tmp->reheight();

}

template<typename T>
std::shared_ptr<Node<T>> Node<T>:: left_rotation()
{
    std::shared_ptr<Node<T>> node_tmp = this->right;
    this->right = node_tmp->left;
    node_tmp->left.reset(this);
    this->reheight();
    node_tmp->reheight();
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::rebalance()
{

}
int main()
{
    return 0;
}