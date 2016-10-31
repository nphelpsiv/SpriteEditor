#include "model.h"
#include <iostream>
#include <QtGui>
#include <queue>
#include <unordered_set>
#include <string>
#include "gif.h"

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
    QColor startColor(0,0,0,255);
    currentColor = startColor;
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

    mirrorHorizontalActive = false;
    mirrorVerticalActive = false;

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
    newFrame = frames[currentFrame];
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

       oldFrame = frames[currentFrame];
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
        if(currentTool!=Tool::Bucket && currentTool!=Tool::Caster)
            draw(loc);
    }

    //send location to draw to be drawn to screen.
}

void Model::mouseReleaseEvent(QMouseEvent *event)
{
    emit framesSaved(oldFrame, newFrame);
}

void Model::colorPicked(QColor c)
{
    currentColor = c;
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
    currentTool = Tool::Picker;
    cout << "colorP (model)" << endl;
}

void Model::colorCasterButtonClicked()
{
    currentTool = Tool::Caster;
    cout << "Tool is Caster"  << endl;
}

void Model::bucketButtonClicked()
{
    currentTool = Tool::Bucket;
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
    oldFrame = frames[currentFrame];
    frames[currentFrame] = ((QImage)frames[currentFrame]).mirrored(true, false);
    update();
    emit framesSaved(oldFrame, frames[currentFrame]);
}
void Model::flipVerticalButtonClicked()
{
    oldFrame = frames[currentFrame];
    frames[currentFrame] = ((QImage)frames[currentFrame]).mirrored(false, true);
    update();
    emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::rotateClockwiseButtonClicked()
{
    oldFrame = frames[currentFrame];
    QTransform transform;
    transform.rotate(90);

    frames[currentFrame] = ((QImage)frames[currentFrame]).transformed(transform);
    update();
    emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::rotateCounterClockwiseButtonClicked()
{
    oldFrame = frames[currentFrame];
    QTransform transform;
    transform.rotate(-90);

    frames[currentFrame] = ((QImage)frames[currentFrame]).transformed(transform);
    update();
    emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::previewButtonClicked()
{
    cout << "preview (model)" << endl;
}

void Model::duplicateFrameButtonClicked(int i)
{
    frames.insert(frames.begin() + i + 1, frames[i+1]);
    currentFrame++;
    update();

    emit frameAdded(frames);
}

/*
 * When Remove Frame button is pressed this method is notified.
 * It removes the current frame from the frames vector.
 * It then sends a signal that a frame was removed back to mainwindow.
 */
void Model::removeFrameButtonClicked(int i)
{
    frames.erase(frames.begin() + i + 1);

    //If the current frame was the last frame, decrement current frame.
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
void Model::FPSSpinBoxChanged(int change)
{
    cout << "Desired Fps: " << change << endl;
}

/*
 * When gif parameters are selected, this method is notified.
 * Gif-h library is used to create a .gif file and save it to file system.
 */
void Model::exportSelected(int fps, string filename, int gifSize)
{
    const char *file = filename.c_str();

    //Need to create a GifWriter struct -- uninitialized
    GifWriter writer;
    //This method writes the .gif header and initializes the writer struct
    GifBegin(&writer, file, gifSize, gifSize, 100/fps);

    //This is the array of color values from the frames.
    //The values get filled with a call to convertFrameToArray.
    uint8_t* image = new uint8_t[gifSize*gifSize*4];

    for(unsigned int i = 1; i < frames.size(); i++)
    {
        //Here we convert the frames to the image array.
        convertFrameToArray(image, i, gifSize);

        //Then we pass the writer struct and image array to this method.
        //This method adds the frame to the gif with the specifed delay (100/fps). delay is in hundredths of a second.
        GifWriteFrame(&writer, image, gifSize,gifSize,100/fps);
    }
    //Then we end and write the gif to file system by a call to this method.
    GifEnd(&writer);
}

/*
 * Helper method to create the uint8_t array that represents the rgba values of each pixel.
 * This method is used with the gif-h library to create a .gif file.
 */
void Model::convertFrameToArray(uint8_t *arr, int frameIndex, int gifSize)
{
    //We first need to scale the frame to the selected value given by user.
    QImage newImage = frames[frameIndex].scaled(gifSize, gifSize);

    for(int i = 0; i < gifSize; i++)
    {
        for(int j = 0; j < gifSize; j++)
        {
            //Grab pixel colors with .pixelColor method.
            QColor pixColor = newImage.pixelColor(j, i);
            uint8_t red = pixColor.red();
            uint8_t green = pixColor.green();
            uint8_t blue = pixColor.blue();
            uint8_t alpha = pixColor.alpha();

            //Here we have to check if the alpha is 0 because gif-h ignores the alhpa value.
            //So "background" color is simply set to white.
            if(alpha == 0)
            {
                red = 255;
                green = 255;
                blue = 255;
            }

            arr[0] = red;
            arr[1] = green;
            arr[2] = blue;
            arr[3] = alpha;
            arr += 4;
        }
    }
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
 * Adds new frame one location greater than the current frame.
 */
void Model::addFrame()
{
    //create new transparent frame, add it to the vector, and increase currentFrame.
    QImage newImage(size, QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));
    frames.insert(frames.begin() + currentFrame + 1, newImage);
    currentFrame++;

    update();
    emit frameAdded(frames);
}

/*
 * Returns current frame index.
 */
QImage Model::getFrame(int i)
{
    return frames[i];
}

std::vector<QImage> Model::getFrames()
{
    return frames;
}

/*
 * This method changes the current frame and draws the chosen frame.
 */
void Model::changeFrame(int i)
{
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

    /*Scale the points along with the scale of the image.
     *This is so the points of the mouse coorelate with the points of the new scaled image
     *not the old, small image.*/
    point.setX(point.x()/scale);
    point.setY(point.y()/scale);

    mirrorPointX = point;
    mirrorPointY = point;

    mirrorPointX.setX(size.width()-point.x()-1);
    mirrorPointY.setY(size.height()-point.y()-1);

    mirrorPointXY.setX(mirrorPointX.x());
    mirrorPointXY.setY(mirrorPointY.y());

    // Use QPainter to modify QImage to be drawn by paintEvent.
    QPainter painter(&frames[currentFrame]);
    painter.setPen(QPen(currentColor, toolSize));

    switch (currentTool)
    {
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
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
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.setPen(QPen(Qt::transparent, toolSize));
        painter.drawLine(lastPoint, point);
        lastPoint = point;
        break;
    case Tool::Caster:
        {
          QColor colorToCast(((QImage)frames[currentFrame]).pixelColor(point));

          int count = 0;
          for(int y = 0; y < ((QImage)frames[currentFrame]).height(); y++)
          {
              for(int x = 0; x < ((QImage)frames[currentFrame]).width(); x++)
              {
                  if( ((QImage)frames[currentFrame]).pixelColor(x,y) == colorToCast)
                  {
                      count++;
                      //((QImage)frames[currentFrame]).setPixelColor(x, y , currentColor);
                      painter.drawPoint(x, y);
                  }
              }
          }
          cout << count << endl;
        }
        break;
    case Tool::Picker:
        currentColor = ((QImage)frames[currentFrame]).pixelColor(point);
        emit colorChanged(currentColor);
        currentTool = Tool::Pen;
        break;
    case Tool::Bucket:
        QColor replacingColor = frames[currentFrame].pixelColor(point.x(), point.y());
        queue<QPoint> q;
        QPoint clickedPoint(point.x(), point.y());
        unordered_set <string> checked;
        string clickedPointString = to_string(clickedPoint.x()) + "; " + to_string(clickedPoint.y());
        cout<< clickedPointString <<endl;
        checked.insert(clickedPointString);
        q.push(clickedPoint);
        while (q.empty()!=true)
        {
            QPoint currentFlood = q.front();
            frames[currentFrame].setPixelColor(currentFlood.x(), currentFlood.y(), currentColor);
            if (currentFlood.x() != (size.width()-1))
            {
                string rightString = to_string(currentFlood.x()+1) + "; " + to_string(currentFlood.y());
                cout<<(rightString)<<endl;
                cout<<(checked.count(rightString))<<endl;
                if ((checked.count(rightString))<1)
                {
                    if (frames[currentFrame].pixelColor(currentFlood.x()+1, currentFlood.y()) == replacingColor)
                    {
                        QPoint rightPoint(currentFlood.x()+1, currentFlood.y());
                        q.push(rightPoint);
                        checked.insert(rightString);
                    }
                }
            }
            if (currentFlood.x() != 0)
            {
                string leftString = to_string(currentFlood.x()-1) + "; " + to_string(currentFlood.y());
                if ((checked.count(leftString))<1)
                {
                    if (frames[currentFrame].pixelColor(currentFlood.x()-1, currentFlood.y()) == replacingColor)
                    {
                        QPoint leftPoint(currentFlood.x()-1, currentFlood.y());
                        q.push(leftPoint);
                        checked.insert(leftString);
                    }
                }
            }
            if (currentFlood.y() != 0)
            {
                string upString = to_string(currentFlood.x()) + "; " + to_string(currentFlood.y()-1);
                if ((checked.count(upString))<1)
                {
                    if (frames[currentFrame].pixelColor(currentFlood.x(), currentFlood.y()-1) == replacingColor)
                    {
                        QPoint upPoint(currentFlood.x(), currentFlood.y()-1);
                        q.push(upPoint);
                        checked.insert(upString);
                    }
                }
            }
            if (currentFlood.y() != (size.width()-1))
            {
                string downString = to_string(currentFlood.x()) + "; " + to_string(currentFlood.y()+1);
                if ((checked.count(downString))<1)
                {
                    if (frames[currentFrame].pixelColor(currentFlood.x(), currentFlood.y()+1) == replacingColor)
                    {
                        QPoint downPoint(currentFlood.x(), currentFlood.y()+1);
                        q.push(downPoint);
                        checked.insert(downString);
                    }
                }
            }
            q.pop();
        }
        break;
    //default:
    //    break;
    }

    update();
}
