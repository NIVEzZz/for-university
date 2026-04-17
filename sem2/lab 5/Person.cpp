#include "Person.h"

Person::Person(Type type, const QString& name, int health, const Armor& armor)
    : m_type(type), m_name(name), m_health(health), m_armor(armor) {}

Mag::Mag(const QString& name, const QString& element, int mana, int health, const Armor& armor)
    : Person(MagType, name, health, armor), m_element(element), m_mana(mana) {}

Vrag::Vrag(const QString& name, const QString& rarity, int damage, int health, const Armor& armor)
    : Person(VragType, name, health, armor), m_rarity(rarity), m_damage(damage) {}
