#include <iostream>
#include <stack>

bool is_correct(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    std::stack<char> brackets;

    for (char symbol : str) {
        if (symbol == '(' || symbol == '{' || symbol == '[') {
            brackets.push(symbol);
        }
        else if (symbol == ')' || symbol == '}' || symbol == ']') {
            if (brackets.empty()) {
                return false;
            }

            char opening_symbol = brackets.top();
            brackets.pop();

            if ((symbol == ')' && opening_symbol != '(') ||
                (symbol == '}' && opening_symbol != '{') ||
                (symbol == ']' && opening_symbol != '[')) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return brackets.empty();
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string str;
    std::cout << "Введите строку: ";
    std::cin >> str;

    if (is_correct(str)) {
        std::cout << "Строка существует" << std::endl;
    }
    else {
        std::cout << "Строка не существует" << std::endl;
    }

    return 0;
}
