#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>
#include <QFile>
#include <QRegularExpression>
#include <QLocale>
#include <QTextStream>

void MainWindow::reset_text(QLineEdit* line) {
    line->setText("");
    line->setStyleSheet("");
}

void MainWindow::reset_radio(QRadioButton* button) {
    if (!button->isChecked()) {
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

void MainWindow::check_box(bool ok, QLineEdit* line) {
    if (ok)
        line->setStyleSheet("");
    else
        line->setStyleSheet("background-color: rgba(255, 0, 0, 70);");
}


bool MainWindow::is_only_russian_letters(const QString& str) {
    static QRegularExpression re("^[А-ЯЁ][а-яё]*$");
    return re.match(str).hasMatch();
}

bool MainWindow::is_only_english_letters(const QString& str) {
    if (str.isEmpty())
        return true;
    static QRegularExpression re("^[A-Z][a-z]*$");
    return re.match(str).hasMatch();
}

bool MainWindow::is_weight_double(const QString& weight) {
    static QRegularExpression re("^(0|[1-9]\\d*)(\\.\\d+)?$");
    if (!re.match(weight).hasMatch())
        return false;
    bool ok;
    double value = weight.toDouble(&ok);
    return ok && value > 0;
}

bool MainWindow::is_wingspan_correct(const QString& str) {
    static QRegularExpression re("^(\\d+)-(\\d+)$");
    QRegularExpressionMatch match = re.match(str);
    if (!match.hasMatch())
        return false;

    int first = match.captured(1).toInt();
    int second = match.captured(2).toInt();
    return first < second;
}

Bird::Bird(const QString& name_ru, const QString& name_eng,
           const QString& weight, const QString& wingspan,
           bool fly_ability, std::array<bool,3> features)
    : name_ru_(name_ru), name_eng_(name_eng), weight_(weight),
    wingspan_(wingspan), fly_ability_(fly_ability), features_(features) {}

void Bird::log_bird() {
    QFile file("result.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << "Птица " << name_ru_;
    if (!name_eng_.isEmpty())
        out << " (" << name_eng_ << ")";
    out << Qt::endl;
    out << "Вес: " << weight_ << Qt::endl;
    out << "Размах крыльев: " << wingspan_ << Qt::endl;
    out << (fly_ability_ ? "Умеет летать" : "Не умеет летать") << Qt::endl;
    if (features_[0] || features_[1] || features_[2]) {
        out << "Особенности:" << Qt::endl;
        if (features_[0]) out << "Перелетные" << Qt::endl;
        if (features_[1]) out << "Водоплавающие" << Qt::endl;
        if (features_[2]) out << "Домашние" << Qt::endl;
    } else {
        out << "Нет особенностей" << Qt::endl;
    }
    out << Qt::endl;
    file.close();
}

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
    bool nameRuOk = is_only_russian_letters(ui->name_P->text());
    bool nameEngOk = is_only_english_letters(ui->name_L->text());
    bool weightOk = is_weight_double(ui->weigth->text());
    bool wingspanOk = is_wingspan_correct(ui->wingspan->text());

    check_box(nameRuOk, ui->name_P);
    check_box(nameEngOk, ui->name_L);
    check_box(weightOk, ui->weigth);
    check_box(wingspanOk, ui->wingspan);

    bool flyOk = ui->radioButton_yes->isChecked() || ui->radioButton_no->isChecked();
    if (!flyOk) {
        ui->radioButton_yes->setStyleSheet(
            "QRadioButton::indicator:unchecked {"
            "    border: 1px solid #aaa;"
            "    border-radius: 8px;"
            "    background-color: rgba(255, 0, 0, 70);"
            "}"
            );
        ui->radioButton_no->setStyleSheet(
            "QRadioButton::indicator:unchecked {"
            "    border: 1px solid #aaa;"
            "    border-radius: 8px;"
            "    background-color: rgba(255, 0, 0, 70);"
            "}"
            );
    } else {
        ui->radioButton_yes->setStyleSheet(
            "QRadioButton { spacing: 8px; }"
            "QRadioButton::indicator { width: 16px; height: 16px; }"
            );
        ui->radioButton_no->setStyleSheet(
            "QRadioButton { spacing: 8px; }"
            "QRadioButton::indicator { width: 16px; height: 16px; }"
            );
    }

    if (nameRuOk && nameEngOk && weightOk && wingspanOk && flyOk) {
        std::array<bool,3> features = {};
        if (ui->checkBox_migratory->isChecked()) features[0] = true;
        if (ui->checkBox_waterfowl->isChecked()) features[1] = true;
        if (ui->checkBox_domestic->isChecked()) features[2] = true;

        Bird bird(ui->name_P->text(), ui->name_L->text(), ui->weigth->text(),
                  ui->wingspan->text(), ui->radioButton_yes->isChecked(), features);
        bird.log_bird();

        ui->name_P->setStyleSheet("background-color: rgba(0, 255, 0, 70);");
    }
}
