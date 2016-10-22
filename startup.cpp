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
}

Startup::~Startup()
{
    delete ui;
}



void Startup::on_NewFileButton_clicked()
{
    QString value = ui->SizeDrop->currentText();
    emit main.getDrawingSize(value.toStdString());
    this->hide();
    main.show();
}

void Startup::on_LoadFileButton_clicked()
{
    this->hide();
    main.show();

}

void Startup::on_SelectFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Sprite"), "/home/McKay", tr("Sprite Files (*.spp)"));
    ui->SelectFileButton->setText(fileName);// = fileName;
}
