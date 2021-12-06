#include <iostream>
#include "ClassSeq.h"
using namespace std;


template<class T>
class tree_elem
{
 public:
     T related_data;
     int m_data;
     tree_elem * m_left;
     tree_elem * m_right;
     tree_elem(int val, T* related_val)
     {
         m_left = nullptr;
         m_right = nullptr;
         m_data = val;
         related_data = *related_val;
     }

     int* GetRelatedData()
     {
        related_data.Get();
     }

     int GetRelatedDataVal()
     {
        return related_data.GetVal();
     }

     void SetRelatedDataVal(int Val)
     {
            related_data.SetVal(Val);
     }

     void Print()
     {
       related_data.Print();
     }
};
template<class T>
class binary_tree
{
 private:
    tree_elem<T>* m_root;
    int m_size;
    void print_tree(tree_elem<T>*);
    void delete_tree(tree_elem<T>*);
    void MulallElem(tree_elem<T>*, int);

 public:
    binary_tree()
    {
        m_size = 0;
    }
    binary_tree(int, T*);
    ~binary_tree();
    void print();
    bool find(int);
    int* GetElem(int);
    void MulElem(int);
    void insert(int, T*);
    void erase(int);
    int size();
};

template<class T>
binary_tree<T>::binary_tree(int key, T* val)
{
    m_root = new tree_elem<T>(key, val);
    m_size = 1;
    //m_size = 0;
}

template<class T>
binary_tree<T>::~binary_tree()
{
    delete_tree(m_root);
}

template<class T>
void binary_tree<T>::delete_tree(tree_elem<T>* curr)
{
    if (curr)
    {
        delete_tree(curr->m_left);
        delete_tree(curr->m_right);
        delete curr;
    }
}

template<class T>
void binary_tree<T>::print()
{
    print_tree(m_root);
    cout << endl;
}

template<class T>
void binary_tree<T>::print_tree(tree_elem<T>* curr)
{
    if (curr) // Проверка на ненулевой указатель
    {
        print_tree(curr->m_left);
        curr -> Print(); //cout << curr->m_data << " ";
        print_tree(curr->m_right);
    }
}

template<class T>
bool binary_tree<T>::find(int key)
{
    tree_elem<T>* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
    return curr != nullptr;
}

template<class T>
int* binary_tree<T>::GetElem(int key)
{
    tree_elem<T>* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
    return curr -> GetRealatedData();
}

template<class T>
void binary_tree<T>::MulElem(int Num)
{
    MulallElem(m_root, Num);
}

template<class T>
void binary_tree<T>::MulallElem(tree_elem<T>* curr, int Num)
{
    if (curr) // Проверка на ненулевой указатель
    {
        MulallElem(curr->m_left, Num);
        curr -> SetRelatedDataVal(curr -> GetRelatedDataVal()*Num); //cout << curr->m_data << " ";
        MulallElem(curr->m_right, Num);
    }
}


template<class T>
void binary_tree<T>::insert(int key, T* val)
{
    if(m_size == 0)
    {
        m_root = new tree_elem<T>(key, val);
        m_size = 1;
    }
    else
    {
        tree_elem<T>* curr = m_root;
        while (curr && curr->m_data != key)
        {
            if (curr->m_data > key && curr->m_left == nullptr)
            {
                curr->m_left = new tree_elem<T>(key, val);
                ++m_size;
                return;
            }
            if (curr->m_data < key && curr->m_right == nullptr)
            {
                curr->m_right = new tree_elem<T>(key, val);
                ++m_size;
                return;
            }
            if (curr->m_data > key)
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }
    }
}

template<class T>
void binary_tree<T>::erase(int key)
{
    tree_elem<T>* curr = m_root;
    tree_elem<T>* parent = nullptr;
    while (curr && curr->m_data != key)
    {
        parent = curr;
        if (curr->m_data > key)
        {
            curr = curr->m_left;
        }
        else
        {
            curr = curr->m_right;
        }
    }
    if (!curr)
        return;
    if (curr->m_left == nullptr)
    {
        // Вместо curr подвешивается его правое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_right;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_right;
        --m_size;
        delete curr;
        return;
    }
    if (curr->m_right == nullptr)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_left;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_left;
        --m_size;
        delete curr;
        return;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    tree_elem<T>* replace = curr->m_right;
    while (replace->m_left)
        replace = replace->m_left;
    int replace_value = replace->m_data;
    erase(replace_value);
    curr->m_data = replace_value;
}


