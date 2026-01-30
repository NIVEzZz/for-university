#include <iostream>
#include <string>

namespace mt {
    class Product {

    public:
        // ctor default
        Product() : name_("Не задано"), description_("Не задано"), price_(0), place_("Не указано"), expiration_days_(0) {
            std::cerr << "ctor default" << std::endl;
        }

        // ctor param
        Product(const std::string& name, const std::string& description, double price, int expiration_days, const std::string& place) : 
        name_(name), description_(description), price_(price), place_(place), expiration_days_(expiration_days) {
            if (!is_price_valid_(price_))
                throw std::invalid_argument("Цена должна быть положительной");
            if (expiration_days_ < 0)
                throw std::invalid_argument("Срок должен быть положительный");

            std::cerr << "ctor param" << std::endl;
        }

        // ctor copy
        Product(const Product& other) : name_(other.name_), description_(other.description_), price_(other.price_), place_(other.place_), expiration_days_(other.expiration_days_) {
            std::cerr << "ctor copy" << std::endl;
        }

        // dtor
        ~Product() {
            std::cerr << "dtor: " << name_ << std::endl;
        }

        // private  name_ set, get
        void set_name(const std::string& name) {
            if (name.empty()) {
                throw std::invalid_argument("Имя не указанно");
            }
            name_ = name;
        }
        std::string get_name() const {return name_;}

        // private description_ set, get
        void set_description(const std::string& description) {
            if (description.empty()) {
                throw std::invalid_argument("Описание не указанно");
            }
            description_ = description;
        }
        std::string get_description() const { return description_; }

        // private prise_ set, get
        void set_price(double price) {
            if (!is_price_valid_(price))
                throw std::invalid_argument("Цена должна быть положительной");
            price_ = price;
        }
        double get_price() const {return price_;}

        // protected expiration_days_  set, get
        void set_expiration_days(int days) {
            if (days < 0)
                throw std::invalid_argument("Срок годности должен быть не отрицаиельный");
            expiration_days_ = days;
        }
        int get_expiration_days() const {return expiration_days_;}

        // private place_ set, get
        void set_place(const std::string& place) {
            if (place.empty()) {
                throw std::invalid_argument("Место получения не указанно");
            }
            place_ = place;
        }
        std::string get_place() const {return place_;}

        // вывод всей информации
        void print() const {
            std::cout << "Название: " << name_ << std::endl;
            std::cout << "Описание: " << description_ << std::endl;
            std::cout << "Цена: " << price_ << "р" << std::endl;
            std::cout << "Срок годности: " << expiration_days_ << " дней" << std::endl;
            std::cout << "Место получения: " << place_ << std::endl;
        }

        // вывод информации где получить
        void print_where_to_get(const std::string& info) const {
            std::cout << "Купить можно в: " << place_ << std::endl;
            std::cout << "Информация: " << info << std::endl;
        }

        // уменьшение срока хранения 
        void reduce_expiration() {
            if (expiration_days_ == 0)
                throw std::logic_error("Срок годности истёк");
            expiration_days_ -= 1;
        }

    protected:
        int expiration_days_;

    private:
        std::string name_;
        std::string description_;
        double price_;
        std::string place_;

        bool is_price_valid_(double price) const {
            return price >= 0;
        }
    };

} //namespace mt

int main() {

    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "Товар по умолчанию" << std::endl;
        mt::Product p1;
        std::cout << "Место в памяти: " << &p1 << std::endl;
        p1.print();

        std::cout << "\nТовар с параметрами" << std::endl;
        mt::Product p2("Торт", "Шоколадный", 600, 30, "Перекресток");
        std::cout << "Место в памяти: " << &p2 << std::endl;
        p2.print();

        std::cout << "\nКопирование товара" << std::endl;
        mt::Product p3 = p2;
        std::cout << "Место в памяти: " << &p3 << std::endl;
        p3.print();

        std::cout << "\nИзменение цены" << std::endl;
        p2.set_price(555.5);
        std::cout << "Новая цена: " << p2.get_price() << "р" << std::endl;

        std::cout << "\nУменьшение срока годности" << std::endl;
        p2.reduce_expiration();
        std::cout << "Осталось дней: " << p2.get_expiration_days() << std::endl;

        std::cout << "\nВ каком отделе" << std::endl;
        p2.print_where_to_get("Отдел молочной продукции");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
