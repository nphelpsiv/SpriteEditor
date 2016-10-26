#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>
#include <vector>
#include <QPixmap>
#include <string.h>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

using namespace std;

namespace ui {
class Model;
}

class Model: public QWidget
{
    Q_OBJECT
public:
    Model(QWidget *parent = 0);

signals:
    void frameAdded(QImage);
    void frameDuplicated(QImage, int);
    void updated(QImage);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void setUp(int canvasSize);
    void undoButtonClicked();
    void redoButtonClicked();

    void penButtonClicked();
    void eraserButtonClicked();
    void rectButtonClicked();
    void lineButtonClicked();
    void colorPickerButtonClicked();
    void colorCasterButtonClicked();
    void bucketButtonClicked();
    void mirrorHorizontalButtonToggled();
    void mirrorVerticalButtonToggled();
    void flipHorizontalButtonClicked();
    void flipVerticalButtonClicked();
    void rotateClockwiseButtonClicked();
    void rotateCounterClockwiseButtonClicked();

    void sliderValueChanged(int change);
    void colorPicked(QColor c);

    void previewButtonClicked();
    void addFrameButtonClicked();
    void duplicateFrameButtonClicked(int i);
    void removeFrameButtonClicked();
    void actualSizeBoxChecked(int checked);
    void FPSSpinBoxChanged(int change);

    void saveButtonClicked(string s);
    void openButtonClicked(string s);



    void addFrame();
    QImage getFrame(int i);
    void changeFrame(int i);

private:
    std::vector<QImage> frames;
    int currentFrame;

    QImage image;
    int scale;
    QSize size;

    QColor currentColor;

    void draw(QPoint);
    QPoint lastPoint;

    int toolSize;

    enum Tool {Pen, Eraser};
    int currentTool;


};

#endif // MODEL_H
