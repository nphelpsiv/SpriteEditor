#include "preview.h"
#include "ui_preview.h"

Preview::Preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
}

Preview::~Preview()
{
    delete ui;
}
