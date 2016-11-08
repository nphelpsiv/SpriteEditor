#include "saveonclose.h"
#include "ui_saveonclose.h"

SaveOnClose::SaveOnClose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveOnClose)
{
    ui->setupUi(this);
    showOnOpenClicked = false;
    showOnCloseClicked = true;
    showOnNewClicked = false;
}

SaveOnClose::~SaveOnClose()
{
    delete ui;
}

void SaveOnClose::on_SaveCloseYES_clicked()
{
    if(showOnOpenClicked)
    {
        emit openNewSprite();
    }
    else if(showOnCloseClicked)
    {
        emit closeMainSprite();
    }
    else if(showOnNewClicked)
    {
        emit startNewNoSave(); // it seems backwards but it's right
    }
    this->close();
}

void SaveOnClose::on_SaveCloseNO_clicked()
{
    if(showOnOpenClicked)
    {
        emit saveThenOpenSprite();
    }
    else if(showOnCloseClicked)
    {
        emit saveMainSprite();
    }
    else if(showOnNewClicked)
    {
        emit startNewWithSave(); // it seems backwards but it's right
    }
    this->close();
}

void SaveOnClose::showFromOpen()
{
    showOnOpenClicked = true;
    showOnCloseClicked = false;
    showOnNewClicked = false;
    ui->BoldLabel->setText("Are you sure you want to Load without saving?");
    this->show();
}

void SaveOnClose::showFromClose()
{
    showOnCloseClicked = true;
    showOnOpenClicked = false;
    showOnNewClicked = false;
    ui->BoldLabel->setText("Are you sure you want to Close without saving?");
    this->show();
}

void SaveOnClose::showFromNew()
{
    showOnNewClicked = true;
    showOnCloseClicked = false;
    showOnOpenClicked = false;
    ui->BoldLabel->setText("Are you sure you want to Start New without saving?");
    this->show();
}
