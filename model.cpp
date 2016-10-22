#include "model.h"
#include <iostream>
#include <QtGui>

using namespace std;
Model::Model(QWidget *parent) : QWidget(parent)
{
    //scale factor will be the size of the drawing pane in GUI (512) divided by size of actual image.
    scale = 512 / 32;

    currentTool = 0;

    //Create new QImage of size and fill in.
    QSize size(32,32);
    QImage newImage(size, QImage::Format_ARGB32);
    newImage.fill(qRgba(255, 255, 255, 255));

    //Use QPainter to draw image to screen and set this newImage to iamge.
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), image);
    image = newImage;
}

void Model::paintEvent(QPaintEvent *event)
{
    //Whenever any QPainter draw (or paint) methods are called, this paintEvent is notified.
    //So we paint to the QImage in other methods and then this method paints the QImage to the screen with scale.
    QPainter painter(this);
    painter.scale(scale, scale);
    QRect rect = event->rect();
    painter.drawImage(rect, image, rect);
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

void Model::mirrorButtonClicked()
{
    cout << "mirror (model)" << endl;
}

void Model::rotateButtonClicked()
{
    cout << "rotate (model)" << endl;
}

void Model::flipButtonClicked()
{
    cout << "flip (model)" << endl;
}

void Model::previewButtonClicked()
{
    cout << "preview (model)" << endl;
}

void Model::addFrameButtonClicked()
{
    cout << "addF (model)" << endl;
}

void Model::duplicateFrameButtonClicked()
{
    cout << "dupF (model)" << endl;
}

void Model::removeFrameButtonClicked()
{
    cout << "removeF (model)" << endl;
}


void Model::draw(QPoint point)
{
    //Scale the points along with the scale of the image.
    //This is so the points of the mouse coorelate with the points of the new scaled image
    //not the old, small image.
    point.setX(point.x()/scale);
    point.setY(point.y()/scale);

    //Use QPainter to modify QImage to be drawn by paintEvent.
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, 1));

    switch (currentTool)
    {
    case Tool::Pen:
        painter.drawLine(lastPoint, point);
        lastPoint = point;
        break;
    case Tool::Eraser:
        painter.setPen(QPen(Qt::white, 1));
        painter.drawLine(lastPoint, point);
        lastPoint = point;
    default:
        break;
    }

    //painter.drawPoint(point);
    //painter.drawLine(lastPoint, point);
    //lastPoint = point;
    update();
}
