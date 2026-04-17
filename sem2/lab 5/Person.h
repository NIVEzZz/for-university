#ifndef PERSON_H
#define PERSON_H

#include <QString>

struct Armor {
    int helmet = 0;
    int cuirass = 0;
    int boots = 0;
};

class Person {
public:
    enum Type { MagType, VragType };

    Person(Type type, const QString& name, int health, const Armor& armor);
    virtual ~Person() = default;

    Type type() const { return m_type; }
    QString name() const { return m_name; }
    int health() const { return m_health; }
    Armor armor() const { return m_armor; }

    virtual QString subtypeString() const = 0;
    virtual QString subtypeValue() const = 0;
    virtual int additionalStat() const = 0;
    virtual QString additionalStatName() const = 0;

protected:
    Type m_type;
    QString m_name;
    int m_health;
    Armor m_armor;
};

class Mag : public Person {
public:
    Mag(const QString& name, const QString& element, int mana, int health, const Armor& armor);

    QString element() const { return m_element; }
    int mana() const { return m_mana; }

    QString subtypeString() const override { return "Стихия"; }
    QString subtypeValue() const override { return m_element; }
    int additionalStat() const override { return m_mana; }
    QString additionalStatName() const override { return "Мана";}

private:
    QString m_element;
    int m_mana;
};

class Vrag : public Person {
public:
    Vrag(const QString& name, const QString& rarity, int damage, int health, const Armor& armor);

    QString rarity() const { return m_rarity; }
    int damage() const { return m_damage; }

    QString subtypeString() const override { return "Редкость"; }
    QString subtypeValue() const override { return m_rarity; }
    int additionalStat() const override { return m_damage; }
    QString additionalStatName() const override { return "Урон"; }
private:
    QString m_rarity;
    int m_damage;
};

#endif // PERSON_H
