/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * Represents the UI that allows the user to pick a new size for the new project
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QDialog>
#include <QFileDialog>


namespace Ui {
class newProject;
}

class NewProject : public QDialog
{
    Q_OBJECT

signals:
    //Signals the new button as been pressed in the main window
    void newSelected(int);
private slots:
    //Catches the signal that the user has accpeted the desired parameters within the UI
    void on_buttonBox_accepted();
//Member variables
public:
    explicit NewProject(QWidget *parent = 0);
    ~NewProject();

private:
    Ui::newProject *ui;
};

#endif // NEWPROJECT_H
