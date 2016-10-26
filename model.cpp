#include "model.h"
#include <iostream>
#include <QtGui>

using namespace std;
Model::Model(QWidget *parent) : QWidget(parent)
{

}

void Model::setUp(int imageSize = 32)
{
    //scale factor will be the size of the drawing pane in GUI (512) divided by size of actual image.
    scale = 512 / imageSize;

    //Automatically set Pen tool.
    currentTool = 0;

    toolSize = 1;

    //Create new QImage (Background image) of size and fill in.
    size.setHeight(imageSize);
    size.setWidth(imageSize);
    QImage newImage(size, QImage::Format_ARGB32);
    newImage.fill(qRgba(120, 120, 120, 255));

    //Fill background with checkerboard pattern
    for(int i = 0; i < imageSize; i++)
    {
        for(int j = 0; j < imageSize; j+=2)
        {
            if(i % 2 == 0)
                newImage.setPixelColor(i, j, qRgba(190, 190, 190, 255));
            else
                newImage.setPixelColor(i, j + 1,qRgba(190, 190, 190, 255));
        }
    }

    //add background frame to the vector. Position 0.
    frames.push_back(newImage);
    currentFrame = 0;

    //create Frame 1 which is filled transparent. Add Frame 1 to vector.
    QImage firstFrame(size, QImage::Format_ARGB32);
    firstFrame.fill(qRgba(0, 0, 0, 0));
    frames.push_back(firstFrame);
    currentFrame = 1;

    //Draw frames.
    QPainter newPaint(&frames[currentFrame]);
    newPaint.drawImage(QPoint(0, 0), frames[currentFrame]);
}

void Model::paintEvent(QPaintEvent *event)
{
    //Whenever any QPainter draw (or paint) methods are called, this paintEvent is notified.
    //So we paint to the QImage in other methods and then this method paints the QImage to the screen with scale.
    QPainter painter(this);
    painter.scale(scale, scale);
    QRect rect = event->rect();
    painter.drawImage(rect, frames[0], rect);
    painter.drawImage(rect, frames[currentFrame], rect);

    emit updated(frames[currentFrame]);
}

void Model::mousePressEvent(QMouseEvent *event)
{
    //Get mouse location
    QPoint loc;
    if(event->button() == Qt::LeftButton)
    {
       loc = event->pos();
       lastPoint = loc;
       lastPoint.setX(lastPoint.x()/scale);
       lastPoint.setY(lastPoint.y()/scale);

       mirrorLastPointX = lastPoint;
       mirrorLastPointY = lastPoint;


       mirrorLastPointX.setX(size.width()-lastPoint.x()-1);
       mirrorLastPointY.setY(size.height()-lastPoint.y()-1);

       mirrorLastPointXY.setX(mirrorLastPointX.x());
       mirrorLastPointXY.setY(mirrorLastPointY.y());
       //newPoint = loc;
       draw(loc);
    }

    //send location to draw to be drawn to screen.

}

void Model::mouseMoveEvent(QMouseEvent *event)
{
    //Get mouse location
    QPoint loc;
    if(event->buttons() & Qt::LeftButton)
    {
        loc = event->pos();
        //newPoint = loc;

        draw(loc);
    }

    //send location to draw to be drawn to screen.
}



void Model::mouseReleaseEvent(QMouseEvent *event)
{

}

void Model::colorPicked(QColor c)
{
    currentColor = c;
}


void Model::undoButtonClicked()
{
    cout << "undoClick (model)" << endl;
}

void Model::redoButtonClicked()
{
    cout << "redoClick (model)" << endl;
}

void Model::penButtonClicked()
{
    currentTool = Tool::Pen;
}

void Model::eraserButtonClicked()
{
    currentTool = Tool::Eraser;
}

void Model::rectButtonClicked()
{
    cout << "rectum (model)" << endl;
}

void Model::lineButtonClicked()
{
    cout << "line (model)" << endl;
}

void Model::colorPickerButtonClicked()
{
    cout << "colorP (model)" << endl;
}

void Model::colorCasterButtonClicked()
{
    cout << "ColorC (model)" << endl;
}

void Model::bucketButtonClicked()
{
    cout << "bucket (model)" << endl;
}

void Model::mirrorHorizontalButtonToggled(bool checked)
{
    mirrorHorizontalActive = checked;
}

void Model::mirrorVerticalButtonToggled(bool checked)
{
    mirrorVerticalActive = checked;
}

void Model::flipHorizontalButtonClicked()
{
  frames[currentFrame] = ((QImage)frames[currentFrame]).mirrored(true, false);
  update();
}
void Model::flipVerticalButtonClicked()
{
  frames[currentFrame] = ((QImage)frames[currentFrame]).mirrored(false, true);
  update();
}

void Model::rotateClockwiseButtonClicked()
{
    QTransform transform;
    transform.rotate(90);

    frames[currentFrame] = ((QImage)frames[currentFrame]).transformed(transform);
    update();
}

void Model::rotateCounterClockwiseButtonClicked()
{
    QTransform transform;
    transform.rotate(-90);

    frames[currentFrame] = ((QImage)frames[currentFrame]).transformed(transform);
    update();
}

void Model::previewButtonClicked()
{
    cout << "preview (model)" << endl;
}

void Model::addFrameButtonClicked()
{
    cout << "addF (model)" << endl;

    addFrame();
}

void Model::duplicateFrameButtonClicked(int i)
{
    cout << "dupF (model) " << i+1 << endl;
    frames.push_back(frames[i+1]);
    currentFrame = frames.size() - 1;
    update();
    emit frameDuplicated(frames[currentFrame], currentFrame);
}

void Model::removeFrameButtonClicked(int i)
{
    if(frames.size() == 2)
    {
        return;
    }

    frames.erase(frames.begin() + i + 1);

    if((i + 1) < frames.size())
        currentFrame = i + 1;
    else
        currentFrame = frames.size() - 1;

    emit frameRemoved(frames);
}

void Model::saveButtonClicked()
{
    cout << "Save button (model)" << endl;
}
void Model::actualSizeBoxChecked(int checked)
{
    //2 is checked, o is unchecked
    if(checked == 2){
        cout << "Checked equals true" << endl;
    }
    else{
        cout << "Checked equals false" << endl;
    }

}
void Model::FPSSpinBoxChanged(int change)
{
    cout << "Desired Fps: " << change << endl;
}

void Model::sliderValueChanged(int change)
{
    cout << "Slider Value: " << change << endl;
    if(change  > 0){
        toolSize = change;
    }
    else{
        toolSize = 1;
    }

}

/*
 * Adds new frame.
 */
void Model::addFrame()
{
    //create new transparent frame, add it to the vector, and increase currentFrame.
    QImage newImage(size, QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));
    frames.push_back(newImage);
    currentFrame += 1;

    update();
    emit frameAdded(frames[currentFrame]);
}

/*
 * Returns current frame index.
 */
QImage Model::getFrame(int i)
{
    return frames[i];
}

void Model::changeFrame(int i)
{
    std::cout << "changeFrame " << i << std::endl;
    currentFrame = i + 1;

    //Draw frames.
    QPainter newPaint(&frames[currentFrame]);
    newPaint.drawImage(QPoint(0, 0), frames[currentFrame]);
    update();
}

void Model::draw(QPoint point)
{
    QPoint mirrorPointX;
    QPoint mirrorPointY;
    QPoint mirrorPointXY;

    //Scale the points along with the scale of the image.
    //This is so the points of the mouse coorelate with the points of the new scaled image
    //not the old, small image.
    point.setX(point.x()/scale);
    point.setY(point.y()/scale);

    mirrorPointX = point;
    mirrorPointY = point;

    mirrorPointX.setX(size.width()-point.x()-1);
    mirrorPointY.setY(size.height()-point.y()-1);

    mirrorPointXY.setX(mirrorPointX.x());
    mirrorPointXY.setY(mirrorPointY.y());

    //cout << "(" << point.x() << "," << point.y() << ")" << endl;
    //Use QPainter to modify QImage to be drawn by paintEvent.
    QPainter painter(&frames[currentFrame]);
    painter.setPen(QPen(Qt::blue, toolSize));

    switch (currentTool)
    {
    case Tool::Pen:
        if(mirrorHorizontalActive)
        {
            painter.setPen(QPen(currentColor, toolSize));
            painter.drawLine(mirrorLastPointX, mirrorPointX);
            mirrorLastPointX = mirrorPointX;
        }
        if(mirrorVerticalActive)
        {
            painter.setPen(QPen(currentColor, toolSize));
            painter.drawLine(mirrorLastPointY, mirrorPointY);
            mirrorLastPointY = mirrorPointY;
        }
        if(mirrorHorizontalActive && mirrorVerticalActive)
        {
            painter.setPen(QPen(currentColor, toolSize));
            painter.drawLine(mirrorLastPointXY, mirrorPointXY);
            mirrorLastPointXY = mirrorPointXY;
        }
        painter.setPen(QPen(currentColor, toolSize));
        painter.drawLine(lastPoint, point);
        lastPoint = point;
        break;
    case Tool::Eraser:
        painter.setPen(QPen(Qt::white, toolSize));
        painter.drawLine(lastPoint, point);
        lastPoint = point;
    default:
        break;
    }

    update();
}
