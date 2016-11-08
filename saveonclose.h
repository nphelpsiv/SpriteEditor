/**
  * This is Dialog is used for asking the user if they want to save the file before they Close, Open, or Start a new one.
  * Made by the QT-Pies.
  **/

#ifndef SAVEONCLOSE_H
#define SAVEONCLOSE_H

#include <QDialog>


namespace Ui {
class SaveOnClose;
}

class SaveOnClose : public QDialog
{
    Q_OBJECT

signals:
    void closeMainSprite();
    void saveMainSprite();
    void openNewSprite();
    void saveThenOpenSprite();
    void startNewNoSave();
    void startNewWithSave();

public:
    explicit SaveOnClose(QWidget *parent = 0);
    ~SaveOnClose();

    // The MainWindow will call one of these methods
    void showFromOpen();
    void showFromClose();
    void showFromNew();

private slots:
    void on_SaveCloseYES_clicked();

    void on_SaveCloseNO_clicked();

private:
    Ui::SaveOnClose *ui;

    // Used for determining which actions to take
    bool showOnOpenClicked;
    bool showOnCloseClicked;
    bool showOnNewClicked;
};

#endif // SAVEONCLOSE_H
