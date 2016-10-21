#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>
namespace ui {
class Model;
}

class Model: public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

public slots:
    void undoClicked();
};

#endif // MODEL_H
