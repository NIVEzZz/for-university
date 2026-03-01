#pragma once
#include <string>

struct Ingredient {
    std::string name;
    double volume;

    Ingredient(const std::string& n = "", double v = 0.0)
        : name(n), volume(v) {
    }

    bool operator==(const Ingredient& other) const {
        return name == other.name;
    }
    bool operator<(const Ingredient& other) const {
        return name < other.name;
    }
};
