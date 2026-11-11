#include <iostream>
#include <vector>

// Соединяй
void merge(std::vector<int>& arr, int i_start, int i_mid, int i_end) {
    int n1 = i_mid - i_start + 1;
    int n2 = i_end - i_mid;

    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[i_start + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[i_mid + 1 + j];

    int i = 0, j = 0, k = i_start;

    // Первый с первым
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Остаток из L
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Остаток из R
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Разделяй
void merge_sort(std::vector<int>& arr, int i_start, int i_end) {
    if (i_start == i_end) {
        return;
    }

    long long i_mid = (i_start + i_end) / 2;

    merge_sort(arr, i_start, i_mid);
    merge_sort(arr, i_mid + 1, i_end);

    merge(arr, i_start, i_mid, i_end);
}

int main() {
    std::vector<int> data = { 6, 5, 3, 1, 8, 7, 2, 4};

    merge_sort(data, 0, data.size() - 1);

    for (int x : data) {
        std::cout << x << " ";
    }

    return 0;
}
