#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>

namespace Ui {
class Preview;
}

class Preview : public QDialog
{
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

private:
    Ui::Preview *ui;
};

#endif // PREVIEW_H
