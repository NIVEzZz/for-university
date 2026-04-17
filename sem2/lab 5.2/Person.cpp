#include "Person.h"

Person::Person(Type type, const QString& name, int health, const Armor& armor)
    : m_type(type), m_name(name), m_health(health), m_armor(armor) {}

Mag::Mag(const QString& name, const QString& element, int mana, int health, const Armor& armor)
    : Person(MagType, name, health, armor), m_element(element), m_mana(mana) {}

Vrag::Vrag(const QString& name, const QString& rarity, int damage, int health, const Armor& armor)
    : Person(VragType, name, health, armor), m_rarity(rarity), m_damage(damage) {}

// craft override
CardData Mag::craft() const {
    CardData data;

    QString elem = m_element.trimmed().toLower();
    if (elem == "огонь") {
        data.imagePath = ":/images/fire.png";
        data.subtypeDisplay = QString("<font color='yellow'>%1</font>").arg(m_element);
    }
    else if (elem == "вода") {
        data.imagePath = ":/images/water.png";
        data.subtypeDisplay = QString("<font color='blue'>%1</font>").arg(m_element);
    }
    else if (elem == "земля") {
        data.imagePath = ":/images/earth.png";
        data.subtypeDisplay = QString("<font color='brown'>%1</font>").arg(m_element);
    }
    else {
        data.imagePath = ":/images/default.png";
        data.subtypeDisplay = QString("<font color='black'>%1</font>").arg(m_element);
    }

    data.nameDisplay = m_name;
    data.healthDisplay = QString("<font color='green'>%1</font>").arg(m_health);
    data.additionalDisplay = QString("<font color='blue'>%1</font>").arg(m_mana);

    return data;
}

// craft override
CardData Vrag::craft() const {
    CardData data;

    QString rar = m_rarity.trimmed().toLower();
    if (rar == "редкий") {
        data.imagePath = ":/images/rare.png";
        data.nameDisplay = QString("<font color='blue'>%1</font>").arg(m_name);
    }
    else if (rar == "обычный") {
        data.imagePath = ":/images/common.png";
        data.nameDisplay = QString("<font color='green'>%1</font>").arg(m_name);
    }
    else if (rar == "легенда") {
        data.imagePath = ":/images/legendary.png";
        data.nameDisplay = QString("<font color='yellow'>%1</font>").arg(m_name);
    }
    else {
        data.imagePath = ":/images/default.png";
        data.nameDisplay = QString("<font color='black'>%1</font>").arg(m_name);
    }

    data.healthDisplay = QString("<font color='red'>%1</font>").arg(m_health);
    data.subtypeDisplay = m_rarity;
    data.additionalDisplay = QString("%1 / %2 / %3").arg(m_armor.helmet).arg(m_armor.cuirass).arg(m_armor.boots);

    return data;
}
