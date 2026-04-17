#include "CardDialog.h"
#include "ui_CardDialogMag.h"
#include "ui_CardDialogVrag.h"
#include <QPixmap>

CardDialog::CardDialog(Person *person, QWidget *parent)
    : QDialog(parent), m_person(person) {

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

CardDialog::~CardDialog() {
    delete uiMag;
    delete uiVrag;
}

void CardDialog::applyPersonDataMag() {
    Mag *mag = static_cast<Mag*>(m_person);
    CardData data = mag->craft();

    uiMag->imageLabel->setPixmap(QPixmap(data.imagePath));
    uiMag->nameValueLabel->setText(data.nameDisplay);
    uiMag->healthValueLabel->setText(data.healthDisplay);
    uiMag->subtypeValueLabel->setText(data.subtypeDisplay);
    uiMag->additionalValueLabel->setText(data.additionalDisplay);
}

void CardDialog::applyPersonDataVrag() {
    Vrag *vrag = static_cast<Vrag*>(m_person);
    CardData data = vrag->craft();

    uiVrag->imageLabel->setPixmap(QPixmap(data.imagePath));
    uiVrag->nameValueLabel->setText(data.nameDisplay);
    uiVrag->healthValueLabel->setText(data.healthDisplay);
    uiVrag->armorValueLabel->setText(data.additionalDisplay);
}

void CardDialog::on_printButton_clicked() {
    emit printClicked(m_person);
    accept();
}
