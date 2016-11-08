/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * Represents the UI/Popup window that asks the user to save the game if desired
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
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
    //Signal when the user attempts to close main window
    void closeMainSprite();
    //Signal when the user attempts to save
    void saveMainSprite();
    //Signal when the user attempts to open new project
    void openNewSprite();
    //Signal when the user attempts to save then open
    void saveThenOpenSprite();
    //Signal when the user attempts to start new with no current save
    void startNewNoSave();
    //Signal when the user attempts to start new with a save
    void startNewWithSave();

private slots:
    //Determine what action to do depending on what caused this dialog to open
    void on_SaveCloseYES_clicked();
    //Determine what action to do depending on what caused this dialog to open
    void on_SaveCloseNO_clicked();

    //member variables and methods
public:
    explicit SaveOnClose(QWidget *parent = 0);
    ~SaveOnClose();

    void showFromOpen();
    /**
     * Called when the MainWindow tries to close the application
     *
     */
    void showFromClose();
    /**
     * Called when the MainWindow tries to Start a new empty sprite
     *
     */
    void showFromNew();

private:
    Ui::SaveOnClose *ui;

    //Used for determining which actions to take
    bool showOnOpenClicked;
    bool showOnCloseClicked;
    bool showOnNewClicked;
};

#endif //SAVEONCLOSE_H
