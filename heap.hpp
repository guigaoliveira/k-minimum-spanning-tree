#include <iostream>

template <class T>
class Heap
{
    int sizeLimit;
    int sizeReal;
    T *list;

    void bubbleUp();
    void bubbleDown();
    void swap(int child, int parent);
    int getLeftChild(int parent);
    int getRightChild(int parent);
    int getParent(int child);

public:
    explicit Heap(int listSize);
    void insert(T);
    T remove();
    int getSize();
};

template <class T>
Heap<T>::Heap(int listMaxSize)
{
    sizeLimit = listMaxSize;
    list = new T[sizeLimit];
    sizeReal = 0;
}

template <class T>
int Heap<T>::getSize()
{
    return sizeReal;
}

template <class T>
void Heap<T>::swap(int child, int parent)
{
    T temp;
    temp = list[child];
    list[child] = list[parent];
    list[parent] = temp;
}

template <class T>
int Heap<T>::getParent(int child)
{
    return (child % 2 == 0) ? (child / 2) - 1 : child / 2;
}

template <class T>
int Heap<T>::getLeftChild(int parent)
{
    return 2 * parent + 1;
}

template <class T>
int Heap<T>::getRightChild(int parent)
{
    return 2 * parent + 2;
}

template <class T>
void Heap<T>::insert(T value)
{

    list[sizeReal++] = value;
    bubbleUp();
}

template <class T>
void Heap<T>::bubbleUp()
{
    int child = sizeReal - 1;
    int parent = getParent(child);

    while (list[child] < list[parent] && child >= 0 && parent >= 0)
    {

        swap(child, parent);
        child = parent;
        parent = getParent(child);
    }
}

template <class T>
T Heap<T>::remove()
{
    int child = sizeReal - 1;
    swap(child, 0);

    T value = list[child];
    list[child] = 0;
    sizeReal--;
    bubbleDown();

    return value;
}

template <class T>
void Heap<T>::bubbleDown()
{
    int parent = 0;

    while (1)
    {
        int left = getLeftChild(parent);
        int right = getRightChild(parent);
        int length = sizeReal;
        int largest = parent;

        if (left < length && list[left] < list[largest])
            largest = left;

        if (right < length && list[right] < list[largest])
            largest = right;

        if (largest != parent)
        {
            swap(largest, parent);
            parent = largest;
        }
        else
            break;
    }
}
