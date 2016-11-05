#include "newproject.h"
#include "ui_newproject.h"
#include <iostream>
#include <string>

NewProject::NewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProject)
{
    ui->setupUi(this);
}

NewProject::~NewProject()
{
    delete ui;
}

void NewProject::on_buttonBox_accepted()
{
    QString value = ui->SizeDrop->currentText();
    size_t found = value.toStdString().find("x");

     //Retrieves the value in SizeDrop as a integer.
    if (found!=std::string::npos)
            emit newSelected(stoi(value.toStdString().substr(0,found)));

    std::cout << "okay clicked" << std::endl;
    this->hide();
}
