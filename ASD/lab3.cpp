#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

short log3(int x) {
    return static_cast<short>(std::log(static_cast<double>(x)) / std::log(3.0));
}

short log5(int x) {
    return static_cast<short>(std::log(static_cast<double>(x)) / std::log(5.0));
}

short log7(int x) {
    return static_cast<short>(std::log(static_cast<double>(x)) / std::log(7.0));
}

int main() {
    int x;
    std::cin >> x;

    if (x < 1) {
        return 0;
    }

    std::vector<int> numbers;

    const short K_MAX = log3(x);
    const short L_MAX = log5(x);
    const short M_MAX = log7(x);

    for (short k = 0; k <= K_MAX; ++k) {
        for (short l = 0; l <= L_MAX; ++l) {
            for (short m = 0; m <= M_MAX; ++m) {
                unsigned long long number = pow(3, k) * pow(5, l) * pow(7, m);
                if (number <= x) {
                    numbers.push_back(number);
                }
            }
        }
    }

    sort(numbers.begin(), numbers.end());

    for (int number : numbers) {
        std::cout << number << " ";
    }
    return 0;
}
