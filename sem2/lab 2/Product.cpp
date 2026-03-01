#include "Product.hpp"
#include <iostream>
#include <algorithm>

void print_vector(const vec& vect) {
    std::cout << "[";
    for (int i = 0; i < vect.size(); ++i) {
        bool flag = true;
        std::cout << vect[i];
        if (i == vect.size() - 1) {
            flag = false;
        }
        if (flag) {
            std::cout << " ";
        }
    }

    std::cout << "]";
    std::cout << std::endl;
}
 // ctor default
    Product::Product() : name_("Не задано"), description_("Не задано"), price_(0), place_("Не указано"), expiration_days_(0), composition_{ "Не задан" } {
        std::cerr << "ctor default" << std::endl;
    }

    // ctor param
    Product::Product(const std::string& name, const std::string& description, double price, int expiration_days, const std::string& place, const vec& composition) :
        name_(name), description_(description), price_(price), place_(place), expiration_days_(expiration_days), composition_(composition) {
        if (!is_price_valid_(price_))
            throw std::invalid_argument("Цена должна быть положительной");
        if (expiration_days_ < 0)
            throw std::invalid_argument("Срок должен быть положительный");

        std::cerr << "ctor param" << std::endl;
    }

    // ctor copy
    Product::Product(const Product& other) : name_(other.name_), description_(other.description_), price_(other.price_), place_(other.place_), expiration_days_(other.expiration_days_), composition_(other.composition_) {
        std::cerr << "ctor copy" << std::endl;
    }

    // dtor
    Product::~Product() {
        composition_.clear();
        std::cerr << "dtor: " << name_ << std::endl;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //Переопределенный оператор =
    Product& Product::operator=(Product& other) {
        if (this != &other) {
            Product tmp(other);
            std::swap(tmp.expiration_days_, expiration_days_);
            std::swap(tmp.name_, name_);
            std::swap(tmp.description_, description_);
            std::swap(tmp.price_, price_);
            std::swap(tmp.place_, place_);
            std::swap(tmp.composition_, composition_);

            std::cerr << "copy assigment operator" << std::endl;
        }
        return *this;
    }

    //Переопределенный оператор +
    Product Product::operator+(Product& other) {
        Product result;
        result.set_name("смесь" + name_ + "и" + other.name_);
        result.set_price((price_ + other.price_) * 0.9);
        result.set_expiration_days(std::min(expiration_days_, other.expiration_days_));
        result.set_composition(composition_);
        result.composition_.reserve(composition_.size() + other.composition_.size());
        for (int i = 0; i < other.composition_.size(); ++i) {
            if (std::count(result.composition_.begin(), result.composition_.end(), other.composition_[i]) == 0) {
                result.composition_.push_back(other.composition_[i]);
            }
        }
        vec v = result.composition_;
        std::sort(v.begin(), v.end());
        auto last = std::unique(v.begin(), v.end());
        v.erase(last, v.end());
        result.set_composition(v);
        v.clear();

        return result;
    }
    Product  Product::operator-(Product& other) {
        Product result;
        result.set_name("выбор" + name_ + "без" + other.name_);
        result.set_price(price_ * 0.9);
        result.set_expiration_days(expiration_days_ - 2);
        result.composition_.clear();
        result.composition_.reserve(composition_.size() + 1);
        for (int i = 0; i < composition_.size(); ++i) {
            if (std::count(other.composition_.begin(), other.composition_.end(), composition_[i]) == 0) {
                result.composition_.push_back(composition_[i]);
            }
        }
        result.composition_.push_back("консервант Т1000");
        return result;
    }
    Product& Product::operator-=(Product& other) {
        this->set_name("выбор" + name_ + "без" + other.name_);
        this->set_price(price_ * 0.9);
        this->set_expiration_days(expiration_days_ - 2);
        for (int i = 0; i < composition_.size(); ++i) {
            if (std::count(other.composition_.begin(), other.composition_.end(), composition_[i]) > 0) {
                composition_.erase(composition_.begin() + i);
            }
        }
        composition_.push_back("консервант Т1000");
        return *this;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    // private  name_ set, get
    void Product::set_name(const std::string& name) {
        if (name.empty()) {
            throw std::invalid_argument("Имя не указанно");
        }
        name_ = name;
    }
    std::string Product::get_name() const { return name_; }

    // private description_ set, get
    void Product::set_description(const std::string& description) {
        if (description.empty()) {
            throw std::invalid_argument("Описание не указанно");
        }
        description_ = description;
    }
    std::string Product::get_description() const { return description_; }

    // private prise_ set, get
    void Product::set_price(double price) {
        if (!is_price_valid_(price))
            throw std::invalid_argument("Цена должна быть положительной");
        price_ = price;
    }
    double Product::get_price() const { return price_; }

    // protected expiration_days_  set, get
    void Product::set_expiration_days(int days) {
        if (days < 0)
            throw std::invalid_argument("Срок годности должен быть не отрицаиельный");
        expiration_days_ = days;
    }
    int Product::get_expiration_days() const { return expiration_days_; }

    // private place_ set, get
    void Product::set_place(const std::string& place) {
        if (place.empty()) {
            throw std::invalid_argument("Место получения не указанно");
        }
        place_ = place;
    }
    std::string Product::get_place() const { return place_; }

    // private composition_ set, get
    void Product::set_composition(const vec& composition) {
        if (composition.empty()) {
            throw std::invalid_argument("Элемент состава не указан");
        }
        composition_ = composition;
    }
    vec Product::get_composition() const { return composition_; }

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    // вывод всей информации
    void Product::print() const {
        std::cout << "Название: " << name_ << std::endl;
        std::cout << "Описание: " << description_ << std::endl;
        std::cout << "Цена: " << price_ << "р" << std::endl;
        std::cout << "Срок годности: " << expiration_days_ << " дней" << std::endl;
        std::cout << "Место получения: " << place_ << std::endl;
        std::cout << "Состав: ";
        print_vector(composition_);
    }

    // вывод информации где получить
    void Product::print_where_to_get(const std::string& info) const {
        std::cout << "Купить можно в: " << place_ << std::endl;
        std::cout << "Информация: " << info << std::endl;
    }

    // уменьшение срока хранения 
    void Product::reduce_expiration() {
        if (expiration_days_ == 0)
            throw std::logic_error("Срок годности истёк");
        expiration_days_ -= 1;
    }

    bool Product::is_price_valid_(double price) const {
        return price >= 0;
    }
