#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QString>
#include <QChar>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void reset_text(QLineEdit* line);
    void reset_radio(QRadioButton* button);
    void check_box(bool ok, QLineEdit* line);


    bool is_russian_letter(QChar ch);
    bool is_only_russian_letters(const QString& str);

    bool is_english_letter(QChar ch);
    bool is_only_english_letters(const QString& str);

    bool is_weight_double(const QString& weight);

    bool is_wingspan_correct(const QString& str);

private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;
};

class Bird{
public:
    Bird(const QString& name_ru, const QString& name_eng, const QString& weight, const QString& wingspan, bool fly_ability, std::array<bool,3> features);

    void log_bird();
private:
    bool fly_ability_;
    std::array<bool,3> features_;
    QString name_ru_;
    QString name_eng_;
    QString weight_;
    QString wingspan_;
};

#endif // MAINWINDOW_H
