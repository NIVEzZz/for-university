#include "Product.hpp"
#include <algorithm>
#include <iostream>


void print_vector(const vec& vect) {
    std::cout << "[";
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i];
        if (i + 1 < vect.size()) std::cout << " ";
    }
    std::cout << "]" << std::endl;
}


// Объединяет два списка ингредиентов, суммируя объёмы для одинаковых названий.
std::vector<Ingredient> merge_compositions(const std::vector<Ingredient>& a, const std::vector<Ingredient>& b) {

    std::vector<Ingredient> result;

    // Добавляет ингредиент в результат, суммируя объём, если такой уже есть
    auto add_ingredient = [&result](const Ingredient& ing) {
        auto it = std::find_if(result.begin(), result.end(), [&](const Ingredient& x) { return x.name == ing.name; });
        if (it != result.end()) {
            it->volume += ing.volume;
        }
        else {
            result.push_back(ing);
        }
        };

    // Добавляем все ингредиенты из a
    for (const auto& ing : a) {
        add_ingredient(ing);
    }
    // Добавляем все ингредиенты из b
    for (const auto& ing : b) {
        add_ingredient(ing);
    }

    std::sort(result.begin(), result.end(), [](const Ingredient& x, const Ingredient& y) {return x.name < y.name;});

    return result;
}

// Возвращает новый вектор из ингредиентов from, названия которых отсутствуют в what.
std::vector<Ingredient> subtract_compositions(const std::vector<Ingredient>& from, const std::vector<Ingredient>& what) {
    std::vector<Ingredient> result;
    for (const auto& ing : from) {
        if (std::find_if(what.begin(), what.end(),[&](const Ingredient& i) { return i.name == ing.name; }) == what.end()) {
            result.push_back(ing);
        }
    }
    return result;
}

namespace mt {

    //-------------------------------------------------------------
    // Конструкторы / Деструкторы
    //-------------------------------------------------------------

    Product::Product() : name_("Не задано"), description_("Не задано"), price_(0.0), expiration_days_(0), place_("Не указано"), composition_() {
    }

    Product::Product(const std::string& name, const std::string& description, double price, int expiration_days, const std::string& place, const std::vector<Ingredient>& composition)
        : name_(name), description_(description), price_(price), expiration_days_(expiration_days), place_(place), composition_(composition) {
        if (!is_price_valid_(price_))
            throw std::invalid_argument("Цена должна быть неотрицательной");
        if (expiration_days_ < 0)
            throw std::invalid_argument("Срок годности должен быть неотрицательным");
    }

    Product::Product(const Product& other) = default;

    Product::~Product() {
        composition_.clear();
    }

    //-------------------------------------------------------------
    // Операторы
    //-------------------------------------------------------------

    Product& Product::operator=(const Product& other) {
        if (this != &other) {
            Product tmp(other);
            std::swap(tmp.name_, name_);
            std::swap(tmp.description_, description_);
            std::swap(tmp.price_, price_);
            std::swap(tmp.expiration_days_, expiration_days_);
            std::swap(tmp.place_, place_);
            std::swap(tmp.composition_, composition_);
        }
        return *this;
    }

    Product Product::operator+(const Product& other) const {
        Product result;
        result.name_ = "смесь " + name_ + " и " + other.name_;
        result.description_ = "Объединение товаров";
        result.price_ = (price_ + other.price_) * 0.9;
        result.expiration_days_ = std::min(expiration_days_, other.expiration_days_);
        result.composition_ = merge_compositions(composition_, other.composition_);
        result.place_ = "место смешивания";
        return result;
    }

    Product Product::operator-(const Product& other) const {
        Product result;
        result.name_ = "выбор " + name_ + " без " + other.name_;
        result.description_ = description_;
        result.price_ = price_ * 0.9;
        result.expiration_days_ = expiration_days_ - 2;
        if (result.expiration_days_ < 0)
            result.expiration_days_ = 0;
        result.composition_ = subtract_compositions(composition_, other.composition_);
        result.composition_.push_back(Ingredient("консервант Т1000", 1.0));
        result.place_ = place_;
        return result;
    }

    Product& Product::operator-=(const Product& other) {
        *this = *this - other;
        return *this;
    }

    //-------------------------------------------------------------
    // Сеттеры / Геттеры
    //-------------------------------------------------------------

    void Product::set_name(const std::string& name) {
        if (name.empty())
            throw std::invalid_argument("Имя не может быть пустым");
        name_ = name;
    }

    std::string Product::get_name() const { return name_; }

    void Product::set_description(const std::string& description) {
        if (description.empty())
            throw std::invalid_argument("Описание не может быть пустым");
        description_ = description;
    }

    std::string Product::get_description() const { return description_; }

    void Product::set_price(double price) {
        if (!is_price_valid_(price))
            throw std::invalid_argument("Цена должна быть неотрицательной");
        price_ = price;
    }

    double Product::get_price() const { return price_; }

    void Product::set_expiration_days(int days) {
        if (days < 0)
            throw std::invalid_argument("Срок годности должен быть неотрицательным");
        expiration_days_ = days;
    }

    int Product::get_expiration_days() const { return expiration_days_; }

    void Product::set_place(const std::string& place) {
        if (place.empty())
            throw std::invalid_argument("Место получения не может быть пустым");
        place_ = place;
    }

    std::string Product::get_place() const { return place_; }

    void Product::set_composition(const std::vector<Ingredient>& composition) {
        composition_ = composition;
    }

    std::vector<Ingredient> Product::get_composition() const { return composition_; }

    //-------------------------------------------------------------
    // Методы вывода
    //-------------------------------------------------------------

    void Product::print() const {
        std::cout << "Название: " << name_ << std::endl;
        std::cout << "Описание: " << description_ << std::endl;
        std::cout << "Цена: " << price_ << " р" << std::endl;
        std::cout << "Срок годности: " << expiration_days_ << " дней" << std::endl;
        std::cout << "Место получения: " << place_ << std::endl;
        std::cout << "Состав:" << std::endl;;
        if (composition_.empty()) {
            std::cout << "  (пусто)" << std::endl;;
        }
        else {
            for (const auto& ing : composition_) {
                std::cout << "  - " << ing.name << ", объём " << ing.volume << std::endl;;
            }
        }
    }

    void Product::print_where_to_get(const std::string& info) const {
        std::cout << "Купить можно в: " << place_ << std::endl;
        std::cout << "Информация: " << info << std::endl;
    }

    //-------------------------------------------------------------
    // Доп. функции
    //-------------------------------------------------------------

    void Product::reduce_expiration() {
        if (expiration_days_ <= 0)
            throw std::logic_error("Срок годности уже истёк");
        --expiration_days_;
    }

    bool Product::is_price_valid_(double price) const {
        return price >= 0.0;
    }

} // namespace mt
