#include <iostream>
#include <stdexcept>

using std::cout; using std::endl;

template <class T>
class VectorJ {
private:
    T* data;
    size_t _capacity;
    size_t _size;

    void resize() {
        T* ptrTmp = new T[_size];

        for (size_t i = 0; i < _size; i++)
        {
            ptrTmp[i] = data[i];
        }
        _capacity *= 2;
        data = new T[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            data[i] = ptrTmp[i];
        }
        delete[] ptrTmp;

    }
public:
    VectorJ() {
        _capacity = 1;
        _size = 0;
        data = new T[_capacity];
    }

    VectorJ(size_t capacity) {
        _capacity = capacity;
        _size = 0;
        data = new T[_capacity];
    }

    VectorJ(VectorJ& v2) {
        _capacity = v2._capacity;
        _size = v2._size;
        data = new T[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            data[i] = v2.data[i];
        }

    }

    VectorJ(size_t arrsize, T arr[])
    {
        //size_t arrsize=sizeof(arr)/sizeof(arr[0]);

        _capacity = arrsize + arrsize;
        _size = arrsize;
        data = new T[_capacity];
        for (int i = 0; i < _size; i++)
        {
            data[i] = arr[i];
        }
    }



    size_t size() { return _size; }
    size_t capacity() { return _capacity; }
    T& at(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("ahi no se puede");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("ahi no se puede");
        }
        else {
            return data[index];
        }

    }

    void push_back(T elem) {

        if (_size == _capacity)
        {
            resize();
        }
        data[_size] = elem;

        _size++;

    }

    void pop_back()
    {
        _size--;
        shrink_to_fit();
    }



    void shrink_to_fit()
    {
        if (_capacity > _size)
        {
            reserve(_size);
        }

    }


    void assign(size_t times, T elem)
    {
        if (times < _capacity) {

            //_size=times; 
            for (size_t i = 0; i < times; i++)
            {
                data[i] = elem;
            }

        }
        if (times >= _capacity)
        {
            //resize();// reserve(times); | 
            data = new T[times];
            _size = times;
            for (size_t i = 0; i < times; i++)
            {
                data[i] = elem;
            }
        }
    }

    void erase_at(size_t index)
    {
        for (size_t i = index; i < _size; i++)
        {
            data[i] = data[i + 1];
        }
        _size--;
        //shrink_to_fit();
    }

    void erase(T dat)
    {
        for (size_t i = 0; i < _size; i++) {
            if (data[i] == dat)
            {
                for (size_t j = i; j < _size; j++)
                {
                    data[j] = data[j + 1];

                }
                _size--;
            }
        }
        //shrink_to_fit();
    }

    void swap(size_t i, size_t j)
    {
        if (i < _size && j < _size)
        {
            size_t temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    T front()
    {
        return data[0];
    }

    T back()
    {
        return data[_size - 1];
    }

    void clear()
    {
        _size = 0;
        _capacity = 0;
        delete[] data;
    }

    bool empty()
    {
        return _size == 0;
    }

    void reserve(size_t cap) {

        T* ptrTmp = new T[_size];

        for (size_t i = 0; i < _size; i++)
        {
            ptrTmp[i] = data[i];
        }

        _capacity = cap;
        data = new T[_capacity];
        if (cap < _size)
        {
            _size = cap;
        }
        for (size_t i = 0; i < _size; i++)
        {
            data[i] = ptrTmp[i];
        }

        delete[] ptrTmp;
    }

    void printVector()
    {
        for (int i = 0; i < _size; i++)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

