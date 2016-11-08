#include "export.h"
#include "ui_export.h"
#include <string>
#include <iostream>

Export::Export(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);

    ui->actualSizeRadio->setChecked(true);

    ui->sizeComboBox->setEnabled(false);
}

Export::~Export()
{
    delete ui;
}

void Export::setActualSize(int size)
{
    actualSize = size;
}

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
void Export::on_otherSizeRadio_clicked()
{
    ui->sizeComboBox->setEnabled(true);
}
void Export::on_actualSizeRadio_clicked()
{
    ui->sizeComboBox->setEnabled(false);
}
