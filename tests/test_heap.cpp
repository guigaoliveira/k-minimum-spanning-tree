#include <iostream>
#include "../heap.hpp"

template class Heap<int>;

int main()
{
    int arr[] = {7, 2, 3, 4, 6, 5, 10};
    Heap<int> heap(100);
    int n = sizeof(arr) / sizeof(int);
    for (int i = 0; i < n; ++i)
    {
        heap.insert(arr[i]);
    }
    std::cout << "Heap Min \n";
    while (heap.getSize() > 0)
    {
        std::cout << heap.remove() << "\n";
    }
    return 0;
}
