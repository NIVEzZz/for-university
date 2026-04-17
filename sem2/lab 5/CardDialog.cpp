#include "CardDialog.h"
#include "ui_CardDialogMag.h"
#include "ui_CardDialogVrag.h"
#include <QPixmap>

CardDialog::CardDialog(Person *person, QWidget *parent) : QDialog(parent), m_person(person) {
    if (m_person->type() == Person::MagType) {
        uiMag = new Ui::CardDialogMag();
        uiMag->setupUi(this);
        setFixedSize(350, 400);
        applyPersonDataMag();
        connect(uiMag->printButton, &QPushButton::clicked, this, &CardDialog::on_printButton_clicked);
    } else {
        uiVrag = new Ui::CardDialogVrag();
        uiVrag->setupUi(this);
        setFixedSize(350, 400);
        applyPersonDataVrag();
        connect(uiVrag->printButton, &QPushButton::clicked, this, &CardDialog::on_printButton_clicked);
    }
}
CardDialog::~CardDialog() { delete uiMag; delete uiVrag; }

void CardDialog::applyPersonDataMag() {
    Mag *mag = static_cast<Mag*>(m_person);
    QString imagePath;
    QString elem = mag->element().trimmed().toLower();
    if (elem == "огонь") {
        imagePath = ":/images/fire.png";
        uiMag->subtypeValueLabel->setText(QString("<font color='yellow'>%1</font>").arg(m_person->subtypeValue()));
    }
    else if (elem == "вода"){
        imagePath = ":/images/water.png";
        uiMag->subtypeValueLabel->setText(QString("<font color='blue'>%1</font>").arg(m_person->subtypeValue()));
    }
    else if (elem == "земля"){
        imagePath = ":/images/earth.png";
        uiMag->subtypeValueLabel->setText(QString("<font color='brown'>%1</font>").arg(m_person->subtypeValue()));
    }
    else {
        imagePath = ":/images/default.png";
        uiMag->subtypeValueLabel->setText(QString("<font color='black'>%1</font>").arg(m_person->subtypeValue()));
    }
    uiMag->imageLabel->setPixmap(QPixmap(imagePath));
    uiMag->nameValueLabel->setText(m_person->name());
    uiMag->healthValueLabel->setText(QString("<font color='green'>%1</font>").arg(m_person->health()));
    uiMag->additionalValueLabel->setText(QString("<font color='blue'>%1</font>").arg(mag->mana()));
}

void CardDialog::applyPersonDataVrag() {
    Vrag *vrag = static_cast<Vrag*>(m_person);
    QString imagePath;
    QString rarity = vrag->rarity().trimmed().toLower();
    if (rarity == "редкий"){
        imagePath = ":/images/rare.png";
        uiVrag->nameValueLabel->setText(QString("<font color='blue'>%1</font>").arg(m_person->name()));
    }
    else if (rarity == "обычный") {
        imagePath = ":/images/common.png";
        uiVrag->nameValueLabel->setText(QString("<font color='green'>%1</font>").arg(m_person->name()));
    }
    else if (rarity == "легенда"){
        imagePath = ":/images/legendary.png";
        uiVrag->nameValueLabel->setText(QString("<font color='yellow'>%1</font>").arg(m_person->name()));
    }
    else {
        imagePath = ":/images/default.png";
        uiVrag->nameValueLabel->setText(QString("<font color='black'>%1</font>").arg(m_person->name()));
    }
    uiVrag->imageLabel->setPixmap(QPixmap(imagePath));
    uiVrag->healthValueLabel->setText(QString("<font color='red'>%1</font>").arg(m_person->health()));
    Armor a = m_person->armor();
    uiVrag->armorValueLabel->setText(QString("%1 / %2 / %3").arg(a.helmet).arg(a.cuirass).arg(a.boots));
}

void CardDialog::on_printButton_clicked() { emit printClicked(m_person); accept(); }
