#pragma once
#include <vector>
#include "..\lib\Ingredient.hpp"

using vec = std::vector<std::string>;

void print_vector(const vec& vect);

namespace mt {

    class Product {
    public:
        // constructors
        Product();
        Product(const std::string& name, const std::string& description,
            double price, int expiration_days, const std::string& place,
            const std::vector<Ingredient>& composition);
        Product(const Product& other);
        ~Product();

        // operators
        Product& operator=(const Product& other);
        Product operator+(const Product& other) const;
        Product operator-(const Product& other) const;
        Product& operator-=(const Product& other);

        // getters/setters
        void set_name(const std::string& name);
        std::string get_name() const;

        void set_description(const std::string& description);
        std::string get_description() const;

        void set_price(double price);
        double get_price() const;

        void set_expiration_days(int days);
        int get_expiration_days() const;

        void set_place(const std::string& place);
        std::string get_place() const;

        void set_composition(const std::vector<Ingredient>& composition);
        std::vector<Ingredient> get_composition() const;

        // output
        void print() const;
        void print_where_to_get(const std::string& info) const;

        // other methods
        void reduce_expiration();

    protected:
        int expiration_days_;

    private:
        std::string name_;
        std::string description_;
        double price_;
        std::string place_;
        std::vector<Ingredient> composition_;

        bool is_price_valid_(double price) const;
    };

} // namespace mt
