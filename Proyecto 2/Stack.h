#include<iostream>
/**
* @class Stack
* @private class Snode (el nodo del Stack)
* @brief clase para almacenar valores en un Stack
* @tparam T: cualquier tipo de dato.
*/
template<class T>
class Stack {
private:

    class Snode {
    private:

        Snode* next = nullptr;
    public:
        T data;

        Snode() {}
        Snode(T d) {
            data = d;
        }
        friend class Stack;
    };
    Snode* root = nullptr;

public:
    size_t size;

    Stack() { size = 0; }

    T front();
    void push(T data);
    void pop();
    void print();
    size_t getSize() {
        return size;
    }
};
/**
* @param data: elemento insertado.
* @brief agrega un nodo al final del stack
*/
template <class T>
void Stack<T>::push(T data)
{
    if (!root)
    {
        root = new Snode(data);
        size++;
        return;
    }
    Snode* tmp = root;
    root = new Snode(data);
    root->next = tmp;
    size++;
}
/**
* @brief elimina un nodo al inicio del stack
*/
template<class T>
void Stack<T>::pop()
{
    Snode* tmp = root;
    root = root->next;
    if (!root) {
        root = nullptr;
    }
    delete tmp;
    size--;
}

template <class T>
T Stack<T>::front()
{
    if (!root) {
        return 0;
    }
    return root->data;
}

/**
* @brief imprime el stack
*/
template<class T>
void Stack<T>::print()
{
    while (root) {
        std::cout << root->data << std::endl;
        pop();
    }
}