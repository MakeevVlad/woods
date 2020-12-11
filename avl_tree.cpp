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

template<typename T, class Node_>
AVLtree<T, Node_>::~AVLtree()
{
    if(root != nullptr)
        root->clear();
}

//====Functions for AVLtree======================================
template<typename T, class Node_>
Node_* AVLtree<T, Node_>::insert(T value_)
{
    if(root == nullptr)
        root = new Node<T>(value_);
    else
        root = root->insert(value_);
    return  root;
}
template<typename T, class Node_>
Node_* AVLtree<T, Node_>::find(T value_)
{
    return root->find(value_);
}

template<typename T, class Node_>
bool AVLtree<T, Node_>::erase(T value_)
{
    if(root == nullptr)
        return 0;
    root = root->erase(value_);
    return 1;//root->erase(value_);
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
void Node<T>::clear()
{
    if(this->right != nullptr)
        this->right->clear();
    if(this->left != nullptr)
        this->left->clear();

    delete this;
}

template<typename T>
size_t get_height(Node<T>* p)
{
    if(p == nullptr)
        return 0;
    return p->height;
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
Node<T>* Node<T>:: right_rotation()
{
    Node<T>* node_tmp = this->left;
    this->left = node_tmp->right;
    node_tmp->right= this;
    this->reheight();
    node_tmp->reheight();
    return node_tmp;
}

template<typename T>
Node<T>* Node<T>:: left_rotation()
{   
    //std::cout << "I'm here!" << std::endl;
    Node<T>* node_tmp = this->right;
    this->right = node_tmp->left;
    node_tmp->left = this;
    this->reheight();
    node_tmp->reheight();
    
    return node_tmp;
}

template<typename T>
Node<T>* Node<T>::rebalance()
{
    this->reheight();
    
    if (this->balance_factor() == 2)
    {
        if (this->right->balance_factor() < 0)
            this->right = this->right->right_rotation();

        return this->left_rotation();
    }
    if (this->balance_factor() == -2)
    {
        if (this->left->balance_factor() > 0)
            this->left = this->left->left_rotation();
        
        return this->right_rotation();
    }
    
    
    return this;
}
template<typename T>
Node<T>* Node<T>::insert(T value_)
{

    if( value_ < this->value)
    {
        if (this->left == nullptr)
            this->left = new Node<T>(value_);
        else 
            this->left = this->left->insert(value_);
    }
    if( value_ > this->value)
    {
        
        if (this->right == nullptr)
            this->right = new Node<T>(value_);
        else
            this->right = this->right->insert(value_);
    }
    
    return this->rebalance();
    
}
template<typename T>
void print_Tree(Node<T>* p,int level)
{
    if(p)
    {
        print_Tree(p->left,level + 1);
        for(int i = 0;i< level;i++) std::cout<<"   ";
        std::cout << p->value << std::endl;
        print_Tree(p->right,level + 1);
    }
}

template<typename T>
Node<T>* Node<T>::min_knot()
{
    if(this->left != nullptr)
        return this->left->min_knot();
    return this;
}
template<typename T>
Node<T>* Node<T>::min_erase()
{
    if(!this->left)
        return this->right;
    this->left = this->left->min_erase();
    return this->rebalance();
}
template<typename T>
Node<T>* Node<T>::erase(T value_)
{
    if(value_ < this->value)
    {
        //std::cout << "if_section" << std::endl;
        if(this->left == nullptr)
            return nullptr;
        this->left = this->left->erase(value_);
    }
    else if(value_ > this->value)
    {
        if(this->right == nullptr)
            return nullptr;
        this->right = this->right->erase(value_);
    }
    else
    {

        Node<T>* node_tmp_l = this->left;
        Node<T>* node_tmp_r = this->right;
        delete this;
        if(node_tmp_r == nullptr)
            return node_tmp_l;
        Node<T>* node_tmp_min =node_tmp_r-> min_knot();

        node_tmp_min->right = node_tmp_r->min_erase();
        node_tmp_min->left = node_tmp_l;
        return node_tmp_min->rebalance();
    }

    return this->rebalance();
    
}

template<typename T>
Node<T>* Node<T>::find(T value_)
{
    if(this->value == value_)
        return this;

    if(this->value < value_ )
    {
        if(this->right == nullptr)
            return nullptr;
        return this->right->find(value_);
    }
    else
    {
        if(this->left == nullptr)
                return nullptr;
        return this->left->find(value_);
    }
}