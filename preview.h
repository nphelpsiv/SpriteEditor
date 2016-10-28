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

public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

public slots:
    void displayImage(QImage image);
    void actualSizeBoxChecked(int checked);
signals:
    void renableButton();

private:
    Ui::Preview *ui;

    void closeEvent(QCloseEvent *event);

    QLabel *label;


    bool actualSize;
};

#endif // PREVIEW_H
