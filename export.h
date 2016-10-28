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
    void exportSelected(int, std::string);

public:
    explicit Export(QWidget *parent = 0);
    ~Export();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Export *ui;
};

#endif // EXPORT_H
