#include "avl_tree.hpp"

//=====Constructors for AVLtree ==================================
template<typename T, class Node_>
AVLtree<T, Node_>::AVLtree()
{
    T zero = 0;
    root = new Node_(zero);
}

template<typename T, class Node_>
AVLtree<T, Node_>::AVLtree()
{
    root = new Node_(value_);
}

//====Functions for AVLtree======================================
template<typename T, class Node_>
Node_* AVLtree<T, Node_>::insert(T value_)
{
    return root.insert(value_);
}
template<typename T, class Node_>
Node_* AVLtree<T, Node_>::find(T value_)
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
Node<T>::Node(T value_)
{
    value = value_;
    left = nullptr;
    right = nullptr;
    height = 1;
}

//====Functions for Node=========================================


