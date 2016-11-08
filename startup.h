/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * Class designed to represent the UI when the user first opens the program
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
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
    //Performs actions if the user has elected to create new project
    void on_NewFileButton_clicked();
    //Performs actions if the user has elected to load an existing project
    void on_LoadFileButton_clicked();

public slots:
    //If the user elects to cancel after electing to load an existing project
    void cancel();

private:
    Ui::Startup *ui;
    MainWindow main;

};

#endif // STARTUP_H
