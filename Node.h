#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H

template <typename T>
class RB_tree;

template <typename T>
class Node {
//protected:
public:
    Node* parent;
    Node* left;
    Node* right;
    bool color; // 1 - red, 0 - black
    T data;

    Node();
    Node(T a, Node* par, bool col);
    ~Node();

    Node* grandparent(Node* n);
    Node* uncle(Node* n);
    Node* sibling(Node* n);
    Node* child(Node* n);

    friend RB_tree<T>;
};

/// Методы класса Node
template <typename T> Node<T>::Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}
template <typename T> Node<T>::Node(T a, Node* par, bool col) {
    this->color = col;
    this->data = a;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = par;
}
template <typename T> Node<T>::~Node() {
    if (right) delete right;
    if (left) delete left;
}
template <typename T> Node<T>* Node<T>::grandparent(Node* n) {
    if ((n != nullptr) && (n->parent != nullptr))
        return n->parent->parent;
    else
        return nullptr;
}
template <typename T> Node<T>* Node<T>::uncle(Node* n) {
    Node *g = grandparent(n);
    if (g == nullptr)
        return nullptr;
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}
template <typename T> Node<T>* Node<T>::sibling(Node* n) {
    if (n == n->parent->left)
            return n->parent->right;
    else
        return n->parent->left;
}
template <typename T> Node<T>* Node<T>::child(Node* n) {
    // использовать,только если ребенок 1 или 0
    if (n->right != nullptr)
        return n->right;
    else
        return n->left;
}

#endif //RB_TREE_NODE_H