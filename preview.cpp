#include "preview.h"
#include "ui_preview.h"

Preview::Preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout(ui->widget);
    label = new QLabel(ui->widget);
    label->setFixedSize(512, 512);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

Preview::~Preview()
{
    delete ui;
}

void Preview::closeEvent(QCloseEvent *event)
{
    emit renableButton();
    event->ignore();
    hide();
}

void Preview::displayImage(QImage image)
{
    QSize size;
    if(!actualSize){
        size.setHeight(512);
        size.setWidth(512);
    }
    else
    {
        size.setHeight(image.width());
        size.setWidth(image.height());
    }
    label->setPixmap(QPixmap::fromImage(image).scaled(size));
    label->show();
}
void Preview::actualSizeBoxChecked(int checked)
{
    //2 is checked, 0 is unchecked
    if(checked == 2){
       actualSize = true;
    }
    else{
       actualSize = false;
    }

}

