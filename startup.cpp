/*
  * This is the dialog that first shows on Startup. It will ask for a size or ask to load a previous sprite.
  */

#include "startup.h"
#include "ui_startup.h"
#include <string>
#include <iostream>

using namespace std;

/*
 * Constructor for setting up the Startup Window
 */
Startup::Startup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startup)
{
    ui->setupUi(this);

    //If there was a cancel this allows it to close smoothly
    connect(&main, SIGNAL(canceld()), this, SLOT(cancel()));
}

/*
 * Destructor
 */
Startup::~Startup()
{
    delete ui;
}

/*
 * When the user selects a Sprite Size and clicks New
 * Get the size chosen and emit to the MainWindow
 * Show the MainWindow and hide this
 * @brief Startup::on_NewFileButton_clicked
 */
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


/*
 * When the user selects Load an old Sprite
 * Hide this and emit to the MainWindow to open a file
 * @brief Startup::on_LoadFileButton_clicked
 */
void Startup::on_LoadFileButton_clicked()
{
    this->hide();
    emit main.loadButtonClicked();
}


/*
 * For gracefully closing when canceling.
 * @brief Startup::cancel
 */
void Startup::cancel()
{
    this->show();
}
