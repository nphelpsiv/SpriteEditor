/*
  * This is Dialog is used for asking the user if they want to save the file before they Close, Open, or Start a new one.
  */

#include "saveonclose.h"
#include "ui_saveonclose.h"

/*
 * Constructor for setting up the SaveOnClose Window/dialog
 */
SaveOnClose::SaveOnClose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveOnClose)
{
    ui->setupUi(this);
    showOnOpenClicked = false;
    showOnCloseClicked = true;
    showOnNewClicked = false;
}

/*
 * Destructor
 */
SaveOnClose::~SaveOnClose()
{
    delete ui;
}

/*
 * Determine what action to do depending on what cause the window to open and if they accept or decline.
 */
void SaveOnClose::on_SaveCloseYES_clicked()
{
    if(showOnOpenClicked) //If User clicked Open from the MainWindow then emit the main window to Open a File Dialog
    {
        emit openNewSprite();
    }
    else if(showOnCloseClicked) //If User clicked Close from MainWindow then emit to close the window
    {
        emit closeMainSprite();
    }
    else if(showOnNewClicked) //If User clicked New from MainWindow then emit to open a new sprite application.
    {
        emit startNewNoSave(); //it seems backwards but it's right
    }
    this->close();
}

/*
 * Determine what action to do depending on what caused this dialog to open
 * @brief SaveOnClose::on_SaveCloseNO_clicked
 */
void SaveOnClose::on_SaveCloseNO_clicked()
{
    if(showOnOpenClicked) //If User clicked Open from the MainWindow and then emit to Save the current sprite and then open a new one.
    {
        emit saveThenOpenSprite();
    }
    else if(showOnCloseClicked) //If User clicked Close from the MainWindow then emit to Save the current one first.
    {
        emit saveMainSprite();
    }
    else if(showOnNewClicked) //If User clicked New from the MainWindow then emit to Save the current one and then start a new one.
    {
        emit startNewWithSave(); //it seems backwards but it's right
    }
    this->close();
}


/*
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

/*
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

/*
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
