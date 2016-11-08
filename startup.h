/*
  * This is the dialog that first shows on Startup. It will ask for a size or ask to load a previous sprite.
  * Made by the QT-Pies
  */

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

public slots:
    void cancel();

private:
    Ui::Startup *ui;
    MainWindow main;

};

#endif // STARTUP_H
