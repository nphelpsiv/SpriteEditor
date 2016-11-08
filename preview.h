/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * Represents the popup window that shows the sprite animation based on desired parameters
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include <QCloseEvent>
#include <QGridLayout>
#include <QImage>
#include <QPen>
#include <QLabel>
#include <QColor>
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <iostream>



namespace Ui {
class Preview;
}

class Preview : public QDialog
{
    Q_OBJECT

public slots:
    //Catches the signal that sends each frame as a Qimage
    void displayImage(QImage image);
    //Catches the signal that the user desires the preview window to display the sprite as its actual size
    void actualSizeBoxChecked(int checked);
signals:
    //Button is enabled a disabled based on if the preview window is open
    void renableButton();
    //Member variables
public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

private:
    Ui::Preview *ui;

    void closeEvent(QCloseEvent *event);

    QLabel *label;


    bool actualSize;
};

#endif // PREVIEW_H
