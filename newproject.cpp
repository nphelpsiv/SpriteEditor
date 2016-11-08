/*
 * Represents the UI that allows the user to pick a new size for the new project
 */

#include "newproject.h"
#include "ui_newproject.h"
#include <iostream>
#include <string>

/*
 * Setting up a NewProject window
 */
NewProject::NewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProject)
{
    ui->setupUi(this);
}

/*
 * Destructor for NewProject
 */
NewProject::~NewProject()
{
    delete ui;
}

/*
 * When a user accepts action for making a New Project
 * emit to the mainwindow to clear everything and start a new application
 */
void NewProject::on_buttonBox_accepted()
{
    QString value = ui->SizeDrop->currentText();
    size_t found = value.toStdString().find("x");

     //Retrieves the value in SizeDrop as a integer.
    if (found!=std::string::npos)
            emit newSelected(stoi(value.toStdString().substr(0,found)));

    this->hide();
}
