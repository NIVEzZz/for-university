#pragma once
#include "..\app\Product.hpp"

namespace mt {

    class Commission {
    public:
        Commission();
        Commission(const std::string& address,
            const std::vector<std::string>& forbidden_ingredients,
            int inspection_days);
        Commission(const Commission& other);
        ~Commission();

        void set_address(const std::string& address);
        std::string get_address() const;

        void set_forbidden_ingredients(const std::vector<std::string>& fi);
        std::vector<std::string> get_forbidden_ingredients() const;

        void set_inspection_days(int days);
        int get_inspection_days() const;

        bool check_product(const Product& product) const;
        void print() const;

    private:
        std::string address_;
        std::vector<std::string> forbidden_ingredients_;
        int inspection_days_;
    };

} // namespace mt
