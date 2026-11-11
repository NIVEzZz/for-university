#include <iostream>
#include <vector>
#include <algorithm>

// Сортирующее дерево
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // max не root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heap_sort(std::vector<int>& arr) {
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
        heapify(arr, arr.size(), i);

    // перемещение max в конец
    for (int i = arr.size() - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> data = { 6, 5, 3, 1, 8, 7, 2, 4 };

    heap_sort(data);

    for (int x : data) {
        std::cout << x << " ";
    }

    return 0;
}
