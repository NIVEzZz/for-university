#ifndef CARDDIALOG_H
#define CARDDIALOG_H
#include <QDialog>
#include "Person.h"
namespace Ui { class CardDialogMag; class CardDialogVrag; }
class CardDialog : public QDialog {
    Q_OBJECT
public:
    explicit CardDialog(Person *person, QWidget *parent = nullptr);
    ~CardDialog();
signals:
    void printClicked(Person *person);
private slots:
    void on_printButton_clicked();
private:
    void applyPersonDataMag();
    void applyPersonDataVrag();
    Ui::CardDialogMag *uiMag = nullptr;
    Ui::CardDialogVrag *uiVrag = nullptr;
    Person *m_person;
};
#endif
