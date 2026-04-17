#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void deletePerson(Person *person);

private:
    void loadFromFile(const QString &filePath);
    void updateList();

    Ui::MainWindow *ui;
    QVector<Person*> m_persons;
};

#endif // MAINWINDOW_H
