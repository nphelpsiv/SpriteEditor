#include "export.h"
#include "ui_export.h"

Export::Export(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);
}

Export::~Export()
{
    delete ui;
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

    int fps = ui->ExportFPSSpinBox->value();
    emit exportSelected(fps, fileName.toStdString());
    this->hide();
}
