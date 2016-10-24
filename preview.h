#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class Preview;
}

class Preview : public QDialog
{
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

signals:
    void renableButton();

private:
    Ui::Preview *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // PREVIEW_H
