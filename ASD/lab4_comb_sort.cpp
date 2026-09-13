#include <iostream>
#include <vector>

void comb_sort(std::vector<int>& data) {
    int step = data.size();
    bool swap_flag = false;
    const float reduction_factor = 1.25;

    while (step > 1 || swap_flag) {
        if (step > 1) {
            step = static_cast<int>(step / reduction_factor);
        }

        swap_flag = false;

        for (short i = 0; i + step < data.size(); ++i) {
            if (data[i] > data[i + step]) {
                std::swap(data[i], data[i + step]);
                swap_flag = true;
            }
        }
    }
}

int main() {
    std::vector<int> data = { 9, 4, 7, 1, 3, 8, 2, 6 };
    for (int number : data) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    comb_sort(data);
    for (int number : data) {
        std::cout << number << " ";
    }

    return 0;
}
