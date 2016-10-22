#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>
#include <vector>
namespace ui {
class Model;
}

class Model: public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

public slots:
    void undoButtonClicked();
    void redoButtonClicked();
    void penButtonClicked();
    void eraserButtonClicked();
    void rectButtonClicked();
    void lineButtonClicked();
    void colorPickerButtonClicked();
    void colorCasterButtonClicked();
    void bucketButtonClicked();
    void mirrorButtonClicked();
    void rotateButtonClicked();
    void flipButtonClicked();

    void previewButtonClicked();
    void addFrameButtonClicked();
    void duplicateFrameButtonClicked();
    void removeFrameButtonClicked();

private:
    std::vector<QImage> frames;
    int currentFrame;

};

#endif // MODEL_H
