#ifndef RB_TREE_RB_TREE_H
#define RB_TREE_RB_TREE_H

#include "Node.h"

template <typename T>
class Node;

template <typename T>
class RB_tree {
//protected:
public:
    Node<T>* top;

    Node<T>* recursion_find(Node<T>* rec_n, T elem, bool find_to_insert, Node<T>* before);
    // также вариант с параметрами по умолчанию bool find_to_insert = 0, Node<T>* before= nullptr
    void rotate_left(Node<T>* father);
    void rotate_right(Node<T>* father);

    //удаление
    void cleaning(Node<T>* n);
    void deleting(Node<T>* n);
    void delete_case_1(Node<T>* n);
    void delete_case_2(Node<T>* n);
    void delete_case_3(Node<T>* n);
    void delete_case_4(Node<T>* n);
    void delete_case_5(Node<T>* n);
    void delete_case_6(Node<T>* n, bool ind);
    //конец случаев на удаление


    //перекраска при вставке
    void insert_case_1(Node<T>* n);
    void insert_case_2(Node<T>* n);
    void insert_case_3(Node<T>* n);
    void insert_case_4(Node<T>* n);
    void insert_case_5(Node<T>* n);
    //конец операций перекраски при добавлении

public:
    RB_tree<T>();
    ~RB_tree();

    bool find(T elem);
    void erase(T elem);
    void insert(T elem);
};

/// Методы 
template <typename T> Node<T>* RB_tree<T>::recursion_find(Node<T>* rec_n, T elem, bool find_to_insert, Node<T>* before) {
   
    if (rec_n == nullptr)
        if (find_to_insert)
            return before;
        else
            return nullptr;
    else {
        if (!find_to_insert) {std::cout << rec_n->data << rec_n->color << ' ';}//FIXME
        before = rec_n;
        if (rec_n->data == elem)
            return rec_n;
        else if (rec_n->data > elem) {
            return recursion_find(rec_n->left, elem, find_to_insert, before);
        }
        else {
            return recursion_find(rec_n->right, elem, find_to_insert, before);
        }
    }
}
template <typename T> void RB_tree<T>::rotate_left(Node<T>* father)
{
    Node<T> *son = father->right;

    son->parent = father->parent;
    if (father->parent != nullptr) {
        if (father->parent->left == father)
            father->parent->left = son;
        else
            father->parent->right = son;
    } else
        this->top = son;
    father->right = son->left;
    if (son->left != nullptr)
        son->left->parent = father;
    father->parent = son;
    son->left = father;
}
template <typename T> void RB_tree<T>::rotate_right(Node<T>* father)
{
    Node<T> *son = father->left;

    son->parent = father->parent;
    if (father->parent != nullptr) {
        if (father->parent->left == father)
            father->parent->left = son;
        else
            father->parent->right = son;
    } else
        this->top = son;
    father->left = son->right;
    if (son->right != nullptr)
        son->right->parent = father;
    father->parent = son;
    son->right = father;
}

//удаление
template <typename T> void RB_tree<T>::cleaning(Node<T>* n) {
    // при удалении считаем, что только 1 потомок
    // и узел не корневой
    Node<T>* child = n->child(n);
    if (child != nullptr)
        child->parent = n->parent;
    if (n->parent->left == n) {
        if (child != nullptr)
            n->parent->left = child;
        else
            n->parent->left = nullptr;
    }
    else {
        if (child != nullptr)
            n->parent->right = child;
        else
            n->parent->right = nullptr;
    }
    //std::cout << child->data << "and" << child->parent->data;
    delete n;
}
template <typename T> void RB_tree<T>::deleting(Node<T>* n) {
    // считаем, что есть ровно 1 потомок
    if (n->child(n) == nullptr) {
        if (n->color == 1)
            cleaning(n);
        else {
            delete_case_1(n);
            cleaning(n);
        }
    }
    else if (n->child(n)->color == 1) {
        n->child(n)->color = 0;
        cleaning(n);
    } else {
        delete_case_1(n);
        cleaning(n);
    }
}
template <typename T> void RB_tree<T>::delete_case_1(Node<T>* n) {
    // если n - корень
    if (n != top)
        delete_case_2(n);
}
template <typename T> void RB_tree<T>::delete_case_2(Node<T>* n) {
    // брат красный
    if (n->sibling(n)->color == 1) {
        n->parent->color = 1;
        n->sibling(n)->color = 0;
        if (n->parent->left == n)
            rotate_left(n->parent);
        else
            rotate_right(n->parent);
    } else
        delete_case_6(n, 0);
}
template <typename T> void RB_tree<T>::delete_case_3(Node<T>* n) {
    // брат,отец, оба потомка брата черные
    if (n->parent->color == 0 && n->sibling(n)->left->color == 0
    && n->sibling(n)->right->color == 0
    && n->sibling(n)->color == 0) {
        n->sibling(n)->color = 1;
        delete_case_1(n->parent);
    }
    else
        delete_case_4(n);
}
template <typename T> void RB_tree<T>::delete_case_4(Node<T>* n) {
    // отец красный, брат черный, потомки брата черные
    if (n->parent->color == 1 && n->sibling(n)->left->color == 0
    && n->sibling(n)->right->color == 0
    && (n->sibling(n))->color == 0) {
        n->parent->color = 0;
        n->sibling(n)->color = 1;
    }
    else
        delete_case_5(n);
}
template <typename T> void RB_tree<T>::delete_case_5(Node<T>* n) {
    // брат черный, если n - левый потомок, то левый потомок
    // брата красный, а правый черный и наоборот, если
    // n - правый потомок, то правый потомок
    // брата красный, а левый черный
    if (n->sibling(n)->color == 0 && n->parent->left == n
        && n->sibling(n)->left->color == 1
        && n->sibling(n)->right->color == 0) {
        n->sibling(n)->left->color = 0;
        n->sibling(n)->color = 1;
        rotate_right(n->sibling(n));
    }
    else if (n->sibling(n)->color == 0 && n->parent->right == n
             && n->sibling(n)->left->color == 0
             && n->sibling(n)->right->color == 1) {
        n->sibling(n)->right->color = 0;
        n->sibling(n)->color = 1;
        rotate_left(n->sibling(n));
    }
    delete_case_6(n, 1);
}
template <typename T> void RB_tree<T>::delete_case_6(Node<T>* n, bool ind) {
    // брат черный, если n - левый потомок, то правый потомок
    // брата красный и наоборот, если
    // n - правый потомок, то левый потомок брата красный
    if (n->sibling(n)->color == 0 && n->parent->left == n
        && n->sibling(n)->right->color == 1) {
        n->sibling(n)->color = n->parent->color;
        n->parent->color = 0;
        rotate_left(n->parent);
    }
    else if (n->sibling(n)->color == 0 && n->parent->right == n
             && n->sibling(n)->left->color == 1) {
        n->sibling(n)->color = n->parent->color;
        n->parent->color = 0;
        rotate_right(n->parent);
    } else if (!ind)
        delete_case_3(n);
}
//конец случаев на удаление


//перекраска при вставке
template <typename T> void RB_tree<T>::insert_case_1(Node<T>* n) {
    if (n->parent == nullptr)
        n->color = 0;
    else
        insert_case_2(n);
}
template <typename T> void RB_tree<T>::insert_case_2(Node<T>* n) {
    if (n->parent->color == 0)
        return;
    else
        insert_case_3(n);
}
template <typename T> void RB_tree<T>::insert_case_3(Node<T>* n) {
    if (n->uncle(n) != nullptr && n->uncle(n)->color == 1) {
        n->parent->color = 0;
        n->grandparent(n)->color = 1;
        n->uncle(n)->color = 0;
        insert_case_1(n->grandparent(n));
    } else
        insert_case_4(n);
}
template <typename T> void RB_tree<T>::insert_case_4(Node<T>* n) {
    if ((n == n->parent->right) && (n->parent == n->grandparent(n)->left)) {
        rotate_left(n->parent);
        n = n->left;
    }
    else if ((n == n->parent->left) && (n->parent == n->grandparent(n)->right)) {
        rotate_right(n->parent);
        n = n->right;
    }
    insert_case_5(n);
}
template <typename T> void RB_tree<T>::insert_case_5(Node<T>* n) {
    n->parent->color = 0;
    n->grandparent(n)->color = 1;
    if ((n == n->parent->left) && (n->parent == n->grandparent(n)->left))
        rotate_right(n->grandparent(n));
    else // if ((n == n->parent->right) && (n->parent == n->grandparent(n)()->right))
        rotate_left(n->grandparent(n));
}
//конец операций перекраски при добавлении

template <typename T> RB_tree<T>::RB_tree() {top = nullptr;}
template <typename T> RB_tree<T>::~RB_tree() {
    if (top) delete top;
}

template <typename T> bool RB_tree<T>::find(T elem) {
    return recursion_find(top, elem, 0, nullptr) != nullptr;
    //или без 2 последних параметров
}
template <typename T> void RB_tree<T>::erase(T elem) {
    std::cout << "erase";
    Node<T>* to_er = recursion_find(top, elem, 0, nullptr);
    // или без последнего параметра
    // проверка, есть ли вообще узел с удаляемым значением
    //if (to_er) std::cout << std::endl << to_er->data << std::endl; 
    if (to_er == nullptr) {return;}

    if (to_er->left == nullptr && to_er->right == nullptr
        && to_er == top) {
        // только один корневой узел в дереве
        top = nullptr;
        delete to_er;
    }
    else if (to_er->left == nullptr && to_er->right == nullptr) {
        if (to_er->color == 1)
            cleaning(to_er);
        else {
            delete_case_1(to_er);
            cleaning(to_er);
        }
    }
    else if (to_er->left != nullptr) {
        Node<T>* max = to_er->left;
        // ищем максимальный элемент в левом поддереве
        while (max->right != nullptr)
            max = max->right;
        to_er->data = max->data;
        //std::cout << max->left->data << "and" << max->left->data; 
        std::cout << "max" <<max->data;
        deleting(max);
    }
    else {
        Node<T>* min = to_er->right;
        // ищем минимальный элемент в правом поддереве
        while (min->left != nullptr)
            min = min->left;
        to_er->data = min->data;
        deleting(min);
    }
}
template <typename T> void RB_tree<T>::insert(T elem) {
    Node<T>* new_n = new Node<T>(elem, nullptr, 1);
    Node<T>* p_new_n = recursion_find(this->top, elem, 1, nullptr);
    //if (p_new_n) std::cout << p_new_n->data << "who "; 
    if (this->top == nullptr) { // в случае добавления в пустое дерево
        new_n->color = 0;
        this->top = new_n;
        this->top->data = elem;
        return;
    }
    if (p_new_n->data == elem) {return;} // проверка, если добавляют элемент, который есть
    if (p_new_n->data > elem)
        p_new_n->left = new_n;
    else
        p_new_n->right = new_n;
    new_n->parent = p_new_n;
    //if (p_new_n) std::cout << p_new_n->child(p_new_n)->data;
    // перекраска
    insert_case_1(new_n);
}


#endif //RB_TREE_RB_TREE_H
