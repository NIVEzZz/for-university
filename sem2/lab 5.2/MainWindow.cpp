#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CardDialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    qDeleteAll(m_persons);
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString exeDir = QCoreApplication::applicationDirPath();
    QDir projectDir(exeDir);
    projectDir.cdUp();
    projectDir.cdUp();
    QString resourcePath = projectDir.absolutePath() + "/resources";

    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл с данными", resourcePath, "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty())
        return;

    loadFromFile(fileName);
}

void MainWindow::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + filePath);
        return;
    }

    qDeleteAll(m_persons);
    m_persons.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() < 6) continue;

        bool ok;
        int typeCode = parts[0].toInt(&ok);
        if (!ok) continue;

        QString name = parts[1];
        QString subtype = parts[2];
        int stat = parts[3].toInt();
        int health = parts[4].toInt();

        Armor armor;
        if (parts.size() >= 8) {
            armor.helmet = parts[5].toInt();
            armor.cuirass = parts[6].toInt();
            armor.boots = parts[7].toInt();
        } else if (parts.size() == 6) {
            QString armorStr = parts[5];
            armorStr.remove('<');
            armorStr.remove('>');
            QStringList armorParts = armorStr.split('/');
            if (armorParts.size() == 3) {
                armor.helmet = armorParts[0].toInt();
                armor.cuirass = armorParts[1].toInt();
                armor.boots = armorParts[2].toInt();
            }
        }

        Person *person = nullptr;
        if (typeCode == 1) {
            person = new Mag(name, subtype, stat, health, armor);
        } else if (typeCode == 2) {
            person = new Vrag(name, subtype, stat, health, armor);
        }
        if (person) {
            m_persons.append(person);
        }
    }

    updateList();
}

void MainWindow::updateList()
{
    ui->listWidget->clear();
    for (Person *p : m_persons) {
        Armor a = p->armor();
        QString display;
        if (p->type() == Person::MagType) {
            Mag *mag = static_cast<Mag*>(p);
            display = QString("%1 %2 %3 %4 <%5/%6/%7>")
                          .arg(p->name())
                          .arg(mag->element())
                          .arg(mag->mana())
                          .arg(p->health())
                          .arg(a.helmet).arg(a.cuirass).arg(a.boots);
        }
        else {
            Vrag *vrag = static_cast<Vrag*>(p);
            display = QString("%1 %2 %3 %4 <%5/%6/%7>")
                          .arg(p->name())
                          .arg(vrag->rarity())
                          .arg(vrag->damage())
                          .arg(p->health())
                          .arg(a.helmet).arg(a.cuirass).arg(a.boots);
        }
        ui->listWidget->addItem(display);
    }
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    int row = ui->listWidget->currentRow();

    Person *person = m_persons[row];
    CardDialog dialog(person, this);
    connect(&dialog, &CardDialog::printClicked, this, &MainWindow::deletePerson);
    dialog.exec();
}

void MainWindow::deletePerson(Person *person)
{
    int index = m_persons.indexOf(person);
    if (index != -1) {
        delete m_persons.takeAt(index);
        updateList();
    }
}
