#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>
#include <QFile>

void MainWindow::reset_text(QLineEdit* line){
    line->setText("");
    line->setStyleSheet("");
}
void MainWindow::reset_radio(QRadioButton* button){
    if (!button->isChecked()){
        button->setStyleSheet("QRadioButton {"
                              "    spacing: 8px;"
                              "}"
                              "QRadioButton::indicator {"
                              "    width: 16px;"
                              "    height: 16px;"
                              "}");
        return;
    }
    button->setAutoExclusive(false);
    button->setChecked(false);
    button->setAutoExclusive(true);
    button->setStyleSheet("QRadioButton {"
                          "    spacing: 8px;"
                          "}"
                          "QRadioButton::indicator {"
                          "    width: 16px;"
                          "    height: 16px;"
                          "}");
}

void MainWindow::check_box(bool ok, QLineEdit* line){
    if(ok)
        line->setStyleSheet("");

    else
        line->setStyleSheet("background-color: rgba(255, 0, 0, 70);");
}


bool MainWindow::is_russian_letter(QChar ch) {
    unsigned short code = ch.unicode();
    return (code >= 0x0430 && code <= 0x044F) || // а-я
           code == 0x0451;   // ё
}
bool MainWindow::is_only_russian_letters(const QString& str) {
    if (str.isEmpty()){
        return false;
    }
    for (size_t i = 1; i < str.size();++i) {
        QChar ch = str[i];
        if (!is_russian_letter(ch))
            return false;
    }
    unsigned short code = str[0].unicode();
    if ((code >= 0x0410 && code <= 0x042F) || code == 0x0401)//А-Я + Ё
        return true;
    return false;
}

bool MainWindow::is_english_letter(QChar ch) {
    unsigned short code = ch.unicode();
    return (code >= 0x0061 && code <= 0x007A); // a-z
}
bool MainWindow::is_only_english_letters(const QString& str) {
    if (str.isEmpty()){
        return true;
    }
    for (size_t i = 1; i < str.size();++i) {
        QChar ch = str[i];
        if (!is_english_letter(ch))
            return false;
    }
    unsigned short code = str[0].unicode();
    if ((code >= 0x0041 && code <= 0x005A)) //A-Z
        return true;
    return false;
}

bool MainWindow::is_weight_double (const QString& weight){
    bool flag;
    double value = QLocale::c().toDouble(weight,&flag);
    if (flag && value >= std::numeric_limits<double>::min()){
        return true;
    }
    else{
        return false;
    }
}

bool MainWindow::is_wingspan_correct(const QString& str){
    int count = str.count("-");
    if (count == 1){
        int pos = str.indexOf("-");
        QString str_1 = str.left(pos);
        QString str_2 = str.right(str.size()-pos-1);

        bool flag_1;
        int num_1 = str_1.toInt(&flag_1);
        bool flag_2;
        int num_2 = str_2.toInt(&flag_2);
        if (flag_1 && flag_2 && num_1<num_2)
            return true;
    }
    return false;
}

void Bird::log_bird(){
    QFile file("result.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out <<"Птица " << this->name_ru_;
        if(this->name_eng_ != "")
            out << " (" << this->name_eng_ << ")";
        out << Qt::endl;
        out << "Вес: " << this->weight_ << Qt::endl;
        out << "Размах крыльев: " << this->wingspan_ << Qt::endl;
        if(this->fly_ability_)
            out << "Умеет летать" << Qt::endl;
        else
            out << "Не умеет летать" << Qt::endl;
        if (this->features_[0] || this->features_[1] || this->features_[2]){
            out << "Особенности:" << Qt::endl;
            if(this->features_[0])
                out << "Перелетные" << Qt::endl;
            if(this->features_[1])
                out << "Водоплавающие" << Qt::endl;
            if(this->features_[2])
                out << "Домашние" << Qt::endl;
        }
        else
            out << "Нет особенностей" << Qt::endl;
        out << Qt::endl;
        file.close();
    } else {
        // Обработка ошибки
    }
}

Bird::Bird(const QString& name_ru, const QString& name_eng, const QString& weight, const QString& wingspan, bool fly_ability, std::array<bool,3> features):
    name_ru_(name_ru), name_eng_(name_eng), weight_(weight), wingspan_(wingspan), fly_ability_(fly_ability), features_(features){}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_reset_clicked()
{
    reset_text(ui->name_P);
    reset_text(ui->name_L);
    reset_text(ui->weigth);
    reset_text(ui->wingspan);

    reset_radio(ui->radioButton_no);
    reset_radio(ui->radioButton_yes);

    ui->checkBox_migratory->setChecked(false);
    ui->checkBox_waterfowl->setChecked(false);
    ui->checkBox_domestic->setChecked(false);
}


void MainWindow::on_pushButton_save_clicked()
{
    check_box(is_only_russian_letters(ui->name_P->text()), ui->name_P);
    check_box(is_only_english_letters(ui->name_L->text()), ui->name_L);
    check_box(is_weight_double(ui->weigth->text()), ui->weigth);
    check_box(is_wingspan_correct(ui->wingspan->text()), ui->wingspan);
    if (!ui->radioButton_yes->isChecked() && !ui->radioButton_no->isChecked()){
        ui->radioButton_yes->setStyleSheet("QRadioButton::indicator:unchecked {"
                                           "    border: 1px solid #aaa;"
                                           "    border-radius: 8px;"
                                           "    background-color: rgba(255, 0, 0, 70);"
                                           "}");
        ui->radioButton_no->setStyleSheet("QRadioButton::indicator:unchecked {"
                                          "    border: 1px solid #aaa;"
                                          "    border-radius: 8px;"
                                          "    background-color: rgba(255, 0, 0, 70);"
                                          "}");
    }
    else{
        ui->radioButton_yes->setStyleSheet("QRadioButton {"
                                           "    spacing: 8px;"
                                           "}"
                                           "QRadioButton::indicator {"
                                           "    width: 16px;"
                                           "    height: 16px;"
                                           "}");
        ui->radioButton_no->setStyleSheet("QRadioButton {"
                                          "    spacing: 8px;"
                                          "}"
                                          "QRadioButton::indicator {"
                                          "    width: 16px;"
                                          "    height: 16px;"
                                          "}");
    }

    bool data_correct = false;
    if(is_only_russian_letters(ui->name_P->text()) && is_only_english_letters(ui->name_L->text())
        && is_weight_double(ui->weigth->text()) && is_wingspan_correct(ui->wingspan->text())
        && (ui->radioButton_yes->isChecked() || ui->radioButton_no->isChecked())){
        data_correct = true;
    }

    if (data_correct){
        std::array<bool,3> features = {};
        if(ui->checkBox_migratory->isChecked())
            features[0] = true;
        if(ui->checkBox_waterfowl->isChecked())
            features[1] = true;
        if(ui->checkBox_domestic->isChecked())
            features[2] = true;

        Bird bird(ui->name_P->text(), ui->name_L->text(), ui->weigth->text(), ui->wingspan->text(), ui->radioButton_yes->isChecked(), features);
        bird.log_bird();
        ui->name_P->setStyleSheet("background-color: rgba(0, 255, 0, 70);");
    }
}
