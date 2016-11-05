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

/**
 * Determine what action to do depending on what caused this dialog to open
 * @brief SaveOnClose::on_SaveCloseNO_clicked
 */
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

/**
 * Determine what action to do depending on what caused this dialog to open
 * @brief SaveOnClose::on_SaveCloseNO_clicked
 */
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


/**
 * Called when the MainWindow tries to open a previously made sprite
 * @brief SaveOnClose::showFromOpen
 */
void SaveOnClose::showFromOpen()
{
    showOnOpenClicked = true;
    showOnCloseClicked = false;
    showOnNewClicked = false;
    ui->BoldLabel->setText("Are you sure you want to Load without saving?");
    this->show();
}

/**
 * Called when the MainWindow tries to close the application
 * @brief SaveOnClose::showFromOpen
 */
void SaveOnClose::showFromClose()
{
    showOnCloseClicked = true;
    showOnOpenClicked = false;
    showOnNewClicked = false;
    ui->BoldLabel->setText("Are you sure you want to Close without saving?");
    this->show();
}

/**
 * Called when the MainWindow tries to Start a new empty sprite
 * @brief SaveOnClose::showFromOpen
 */
void SaveOnClose::showFromNew()
{
    showOnNewClicked = true;
    showOnCloseClicked = false;
    showOnOpenClicked = false;
    ui->BoldLabel->setText("Are you sure you want to Start New without saving?");
    this->show();
}
