#include "Commission.hpp"
#include <iostream>

namespace mt {

    Commission::Commission() : address_("не указан"), inspection_days_(0) {
    }

    Commission::Commission(const std::string& address, const std::vector<std::string>& forbidden_ingredients, int inspection_days)
        : address_(address), forbidden_ingredients_(forbidden_ingredients), inspection_days_(inspection_days) {
    }

    Commission::Commission(const Commission& other) = default;

    Commission::~Commission() {
    }

    void Commission::set_address(const std::string& address) {
        address_ = address;
    }
    std::string Commission::get_address() const { return address_; }

    void Commission::set_forbidden_ingredients(const std::vector<std::string>& fi) {
        forbidden_ingredients_ = fi;
    }
    std::vector<std::string> Commission::get_forbidden_ingredients() const { return forbidden_ingredients_; }

    void Commission::set_inspection_days(int days) {
        inspection_days_ = days;
    }
    int Commission::get_inspection_days() const { return inspection_days_; }

    bool Commission::check_product(const Product& product) const {
        if (product.get_expiration_days() < inspection_days_)
            return false;

        auto comp = product.get_composition();
        for (const auto& ing : comp) {
            if (std::find(forbidden_ingredients_.begin(),
                forbidden_ingredients_.end(),
                ing.name) != forbidden_ingredients_.end()) {
                return false;
            }
        }
        return true;
    }

    void Commission::print() const {
        std::cout << "Комиссия:" << std::endl;
        std::cout << "  Адрес: " << address_ << std::endl;
        std::cout << "  Запрещённые ингредиенты: ";
        if (forbidden_ingredients_.empty()) {
            std::cout << "нет" << std::endl;
        }
        else {
            for (size_t i = 0; i < forbidden_ingredients_.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << forbidden_ingredients_[i];
            }
            std::cout << std::endl;
        }
        std::cout << "  Срок проверки: через " << inspection_days_ << " дней" << std::endl;
    }

} // namespace mt
