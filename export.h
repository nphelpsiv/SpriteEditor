/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * Class that represents the UI dialog to allow the user to give specific parameters for the export to an animated gif
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef EXPORT_H
#define EXPORT_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class Export;
}

class Export : public QDialog
{
    Q_OBJECT

signals:
    //signal fired when export is selected in the main window
    void exportSelected(int, std::string, int);

private slots:
    //Catches teh signal that the user has accepted the desired parameters
    void on_buttonBox_accepted();
    //Catches the signal that the user has selected the desired size for the exported gif
    void on_otherSizeRadio_clicked();
    //Catches the signal that the user wishes the gif to be exported as the actual size of the sprite
    void on_actualSizeRadio_clicked();
   //member variables
public:
    explicit Export(QWidget *parent = 0);
    ~Export();

    //Sets the size of export gif
    void setActualSize(int);

private:
    Ui::Export *ui;

    int actualSize;
};

#endif // EXPORT_H
