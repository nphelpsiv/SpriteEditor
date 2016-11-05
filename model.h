#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>
#include <vector>
#include <QPixmap>
#include <string.h>
#include <QColor>
#include <iostream>
#include <QMessageBox>
#include <stdint.h>

using namespace std;

namespace ui {
class Model;
}

class Model: public QWidget
{
    Q_OBJECT
public:
    Model(QWidget *parent = 0);
    QSize size;
    int currentFrame;
    std::vector<QImage> frames;

signals:
    void colorChanged(QColor);
    void frameAdded(std::vector<QImage>);
    void frameRemoved(std::vector<QImage>);
    void updated(QImage, int);
    void framesSaved(QImage, QImage);
    void framesMoved(std::vector<QImage>, int);
    void closeMainSprite();
    void startNewSprite();
    void changeAlphaSlider(int);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void setUp(int canvasSize);

    void penButtonClicked();
    void eraserButtonClicked();
    void rectButtonClicked();
    void lineButtonClicked();
    void ellipseButtonClicked();
    void colorPickerButtonClicked();
    void colorCasterButtonClicked();
    void bucketButtonClicked();
    void mirrorHorizontalButtonToggled(bool checked);
    void mirrorVerticalButtonToggled(bool checked);
    void flipHorizontalButtonClicked();
    void flipVerticalButtonClicked();
    void rotateClockwiseButtonClicked();
    void rotateCounterClockwiseButtonClicked();

    void sliderValueChanged(int change);
    void alphaValueChanged(int a);
    void colorPicked(QColor c);

    void previewButtonClicked();
    void duplicateFrameButtonClicked(int i);
    void removeFrameButtonClicked(int i);
    void moveFrameButtonClicked(int i);
    void clearFrameButtonClicked(int i);
    void FPSSpinBoxChanged(int change);


    // Connections with the model for opening, saving, new actions
    void newButtonClicked(int size);
    void saveButtonClicked(string s);
    void saveAndCloseButtonClicked(string s);
    void saveThenNewButtonClicked(string s);
    void openButtonClicked(string s);

    std::vector<QImage> getFrames();
    void exportSelected(int, std::string, int);

    void addFrame();
    QImage getFrame(int i);
    void changeFrame(int i);

private:
    QImage image;
    int scale;

    QColor currentColor;

    void draw(QPoint);
    void FloodFill(QPoint point);
    QPoint lastPoint;
    QPoint mirrorLastPointX;
    QPoint mirrorLastPointY;
    QPoint mirrorLastPointXY;

    QImage oldFrame;
    QImage newFrame;

    int toolSize;

    enum Tool {Pen, Eraser, Rect, Line, Ellipse, Caster, Picker, Bucket};
    int currentTool;

    bool mirrorHorizontalActive;
    bool mirrorVerticalActive;
    void convertFrameToArray(uint8_t*, int, int);
};

#endif // MODEL_H
