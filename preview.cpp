/*
 * Represent the popup window that shows the sprite animation based on desired parameters
 */

#include "preview.h"
#include "ui_preview.h"

/*
 * Constructor setting up the Preview window
 */
Preview::Preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout(ui->widget);
    label = new QLabel(ui->widget);
    label->setMargin(0);
    label->setFixedSize(512, 512);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

/*
 * Destructor for Preview
 */
Preview::~Preview()
{
    delete ui;
}

/*
 * When they close this window reenable the preview button in the MainWindow
 * Then just hide this window
 */
void Preview::closeEvent(QCloseEvent *event)
{
    emit renableButton();
    event->ignore();
    hide();
}

/*
 * Display the QImage to the Preview Window
 */
void Preview::displayImage(QImage image)
{

    QSize size;

    // Change the size to a default size or the actual size
    if(!actualSize){
        size.setHeight(512);
        size.setWidth(512);
    }
    else
    {
        size.setHeight(image.width());
        size.setWidth(image.height());
    }

    // display
    label->setPixmap(QPixmap::fromImage(image).scaled(size));
    label->show();
}

/*
 * If the user wants to see the Preview in the actual size of the Sprite
 */
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

