#pragma once
#include <string>
#include <vector>

using vec = std::vector<std::string>;

void print_vector(const vec& vect);

namespace mt {
    class Product {

    public:
        // ctor default
        Product();

        // ctor param
        Product(const std::string& name, const std::string& description, double price, int expiration_days, const std::string& place, const vec& composition);

        // ctor copy
        Product(const Product& other);

        // dtor
        ~Product();

        //------------------------------------------------------------------------------------------------------------------------------------------------------

        //Переопределенный оператор =
        Product& operator=(Product& other);
        //Переопределенный оператор +
        Product operator+(Product& other);
        //Переопределенный оператор -
        Product operator-(Product& other);
        //Переопределенный оператор -=
        Product& operator-=(Product& other);


        //------------------------------------------------------------------------------------------------------------------------------------------------------

        // private  name_ set, get
        void set_name(const std::string& name);
        std::string get_name() const;

        // private description_ set, get
        void set_description(const std::string& description);
        std::string get_description() const;

        // private prise_ set, get
        void set_price(double price);
        double get_price() const;

        // protected expiration_days_  set, get
        void set_expiration_days(int days);
        int get_expiration_days() const;

        // private place_ set, get
        void set_place(const std::string& place);
        std::string get_place() const;

        // private composition_ set, get
        void set_composition(const vec& composition);
        vec get_composition() const;

        //------------------------------------------------------------------------------------------------------------------------------------------------------

        // вывод всей информации
        void print() const;

        // вывод информации где получить
        void print_where_to_get(const std::string& info) const;

        // уменьшение срока хранения 
        void reduce_expiration();

    protected:
        int expiration_days_;
    private:
        std::string name_;
        std::string description_;
        double price_;
        std::string place_;
        vec composition_;

        bool is_price_valid_(double price) const;
    };

} //namespace mt