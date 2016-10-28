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
    void exportSelected(int, std::string, int);

public:
    explicit Export(QWidget *parent = 0);
    ~Export();

    void setActualSize(int);

private slots:
    void on_buttonBox_accepted();

    void on_otherSizeRadio_clicked();

    void on_actualSizeRadio_clicked();

private:
    Ui::Export *ui;

    int actualSize;
};

#endif // EXPORT_H
