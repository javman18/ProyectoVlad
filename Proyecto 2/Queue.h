#include<iostream>
/**
* @class Queue
* @private class Qnode (el nodo del Queue)
* @brief clase para almacenar valores en un Queue
* @tparam T: cualquier tipo de dato.
*/
template<class T>
class Queue {
private:

    class Qnode {
    private:

        Qnode* next = nullptr;
    public:
        T data;

        Qnode() {}
        Qnode(T d) {
            data = d;
        }
        friend class Queue;
    };
    Qnode* root = nullptr;
    Qnode* last = nullptr;

public:
    size_t size;

    Queue() { size = 0; }

    void push(T data);
    void pop();
    T front();
    T back();
    void print();
    size_t getSize() {
        return size;
    }

};
/**
* @param data: elemento insertado.
* @brief agrega un nodo al final del Queue
*/
template <class T>
void Queue<T>::push(T data)
{
    if (!root)
    {
        root = new Qnode(data);
        last = root;
        size++;
        return;
    }
    last->next = new Qnode(data);
    last = last->next;
    size++;
}

/**
* @brief elimina un nodo al inicio del queue
*/
template<class T>
void Queue<T>::pop()
{
    Qnode* tmp = root;
    root = root->next;
    if (!root) {
        last = nullptr;
    }
    delete tmp;
    size--;

}
/*
* @brief regresa el primer dato del nodo
*/
template <class T>
T Queue<T>::front()
{
    if (!root) {
        return 0;
    }
    return root->data;
}

/**
* @brief regresa el dato del ultimo nodo
*/
template <class T>
T Queue<T>::back()
{
    if (!root) {
        return 0;
    }
    return last->data;
}
/**
* @brief imprime el queue
*/
template<class T>
void Queue<T>::print()
{
    while (root) {
        std::cout << root->data << std::endl;
        pop();
    }
}

