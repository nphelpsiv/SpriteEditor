/*
 * Class that represents the UI dialog to allow the user to give specific parameters for the export to an animated gif
 */

#include "export.h"
#include "ui_export.h"
#include <string>
#include <iostream>

/*
 * Set up the Export Window
 */
Export::Export(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);

    ui->actualSizeRadio->setChecked(true);

    ui->sizeComboBox->setEnabled(false);
}

/*
 * Destructor for Export
 */
Export::~Export()
{
    delete ui;
}

/*
 * Used to set the exported gif to the actual size of the sprite
 * If this is not used then the exported gif will be a blown up size
 */
void Export::setActualSize(int size)
{
    actualSize = size;
}

/*
 * Opens a saving dialog for the save location
 * Saves the sprite to a gif with help from the gif-h library
 */
void Export::on_buttonBox_accepted()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Animation"), "~/", tr("Gif Files (*.gif)"));


    //Check if filename already ends with .gif
    if(!fileName.endsWith(".gif"))
    {
        fileName += ".gif";
    }

    int gifSize;

    //Actions based on the what size the user desires
    if(ui->actualSizeRadio->isChecked())
        gifSize = actualSize;
    else
    {
        QString value = ui->sizeComboBox->currentText();
        size_t found = value.toStdString().find("X");

        if(found!=std::string::npos)
            gifSize = stoi(value.toStdString().substr(0,found));
    }

    int fps = ui->ExportFPSSpinBox->value();
    emit exportSelected(fps, fileName.toStdString(), gifSize);
    this->hide();
}

/*
 * Setting UI boxes
 */
void Export::on_otherSizeRadio_clicked()
{
    ui->sizeComboBox->setEnabled(true);
}

/*
 * Setting UI boxes
 */
void Export::on_actualSizeRadio_clicked()
{
    ui->sizeComboBox->setEnabled(false);
}
