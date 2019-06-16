#include <iostream>

// classe que implementa uma heap mínima 
template <class T>
class MinHeap
{
    int sizeLimit;
    int sizeReal;
    T *list;

    void siftUp();
    void siftDown();
    void swap(int child, int parent);
    int getLeftChild(int parent);
    int getRightChild(int parent);
    int getParent(int child);

public:
    explicit MinHeap(int listSize);
    MinHeap(const MinHeap &heap2);
    void insert(T);
    T remove();
    int size();
};

template <class T>
MinHeap<T>::MinHeap(int listMaxSize)  
{
    sizeLimit = listMaxSize;
    list = new T[sizeLimit];
    sizeReal = 0;
}

// retorna a quantidade de elementos inseridos na heap
template <class T>
int MinHeap<T>::size()
{
    return sizeReal;
}

// troca um filho com o pai na árvore
template <class T>
void MinHeap<T>::swap(int child, int parent)
{
    T temp;
    temp = list[child];
    list[child] = list[parent];
    list[parent] = temp;
}

// retorna o pai de um no 
template <class T>
int MinHeap<T>::getParent(int child)
{
    return (child % 2 == 0) ? (child / 2) - 1 : child / 2;
}

// retorna o elemento na esquerda dado um pai 
template <class T>
int MinHeap<T>::getLeftChild(int parent)
{
    return 2 * parent + 1;
}

// retorna o elemento na direita dado um pai 
template <class T>
int MinHeap<T>::getRightChild(int parent)
{
    return 2 * parent + 2;
}

// insere um elemento na heap
template <class T>
void MinHeap<T>::insert(T value)
{

    list[sizeReal++] = value;
    siftUp();
}

// sobe os elementos que precisam para que a heap seja mínima. 
template <class T>
void MinHeap<T>::siftUp()
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

// remove um elemento da heap e o retorna 
template <class T>
T MinHeap<T>::remove()
{
    if (!sizeReal)
        return false;

    int child = sizeReal - 1;
    swap(child, 0);

    T value = list[child];
    list[child] = 0;
    sizeReal--;
    siftDown();

    return value;
}

// desce os elementos que precisam para que a heap seja mínima.
template <class T>
void MinHeap<T>::siftDown()
{
    int parent = 0;

    while (true)
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
