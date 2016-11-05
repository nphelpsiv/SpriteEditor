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
    void newSelected(int);
public:
    explicit NewProject(QWidget *parent = 0);
    ~NewProject();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::newProject *ui;
    //MainWindow main;

};

#endif // NEWPROJECT_H
