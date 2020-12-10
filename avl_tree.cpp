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
    root = std::shared_ptr<Node_> (new Node_(value_));
}

//====Functions for AVLtree======================================
template<typename T, class Node_>
std::shared_ptr<Node_> AVLtree<T, Node_>::insert(T value_)
{
    return  root->insert(value_);
}
template<typename T, class Node_>
std::shared_ptr<Node_> AVLtree<T, Node_>::find(T value_)
{
    return nullptr;//root->find(value_);
}

template<typename T, class Node_>
bool AVLtree<T, Node_>::erase(T value_)
{
    return 0;//root->erase(value_);
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
size_t get_height(std::shared_ptr<Node<T>> p)
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
std::shared_ptr<Node<T>> Node<T>:: right_rotation()
{
    std::shared_ptr<Node<T>> node_tmp = this->left;
    this->left = node_tmp->right;
    node_tmp->right.reset(this);
    this->reheight();
    node_tmp->reheight();
    return node_tmp;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>:: left_rotation()
{   
    //std::cout << "I'm here!" << std::endl;
    std::shared_ptr<Node<T>> node_tmp = this->right;
    this->right = node_tmp->left;
    node_tmp->left.reset(this);
    this->reheight();
    node_tmp->reheight();
    
    return node_tmp;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::rebalance()
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
    
    return nullptr;
}
template<typename T>
std::shared_ptr<Node<T>> Node<T>::insert(T value_)
{

    if( value_ < this->value)
    {
        if (this->left == nullptr)
            this->left = std::shared_ptr<Node<T>> (new Node<T>(value_));
        else 
            this->left = this->left->insert(value_);
    }
    else if( value_ > this->value)
    {
        
        if (this->right == nullptr)
            this->right = std::shared_ptr<Node<T>> (new Node<T>(value_));
        else
            this->right = this->right->insert(value_);
    }
    
    return this->rebalance();
    
}
template<typename T>
void print_Tree(std::shared_ptr<Node<T>> p,int level)
{
    if(p)
    {
        print_Tree(p->left,level + 1);
        for(int i = 0;i< level;i++) std::cout<<"   ";
        std::cout << p->value << std::endl;
        print_Tree(p->right,level + 1);
    }
}



int main()
{
    AVLtree<int> tree(0);
    //std::cout << tree.root->show();
    int a;
    while(std::cin >> a)
    {
        tree.insert(a);
    print_Tree(tree.root, 0);
    std::cout << "==>";}
    /*
    for(int i = -100; i < -93; ++i)
    {
        tree.insert(i);
    }
    tree.insert(-93);*/
    return 0;
}