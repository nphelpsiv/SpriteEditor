#ifndef STARTUP_H
#define STARTUP_H

#include <QDialog>
#include <QFileDialog>
#include "mainwindow.h"

namespace Ui {
class Startup;
}

class Startup : public QDialog
{
    Q_OBJECT

public:
    explicit Startup(QWidget *parent = 0);
    ~Startup();

private slots:
    void on_NewFileButton_clicked();

    void on_LoadFileButton_clicked();

    void on_SelectFileButton_clicked();

private:
    Ui::Startup *ui;
    MainWindow main;

};

#endif // STARTUP_H
