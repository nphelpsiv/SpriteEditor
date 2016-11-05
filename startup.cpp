#include "startup.h"
#include "ui_startup.h"
#include <string>
#include <iostream>

using namespace std;

Startup::Startup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startup)
{
    ui->setupUi(this);

    connect(&main, SIGNAL(canceld()), this, SLOT(cancel()));
}

Startup::~Startup()
{
    delete ui;
}

void Startup::on_NewFileButton_clicked()
{
    QString value = ui->SizeDrop->currentText();
    size_t found = value.toStdString().find("x");

     //Retrieves the value in SizeDrop as a integer.
    if (found!=string::npos)
        emit main.getDrawingSize(stoi(value.toStdString().substr(0,found)));

    this->hide();
    main.show();
}


void Startup::on_LoadFileButton_clicked()
{
    this->hide();
    emit main.loadButtonClicked();
}

void Startup::cancel()
{
    this->show();
}
