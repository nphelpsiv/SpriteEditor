#include "model.h"
#include <iostream>
#include <QtGui>
#include <queue>
#include <unordered_set>
#include <string>
#include <algorithm>
#include "gif.h"

using namespace std;

Model::Model(QWidget *parent) : QWidget(parent)
{
    //Automatically set Pen tool.
    currentTool = 0;
    QColor startColor(0,0,0,255);
    currentColor = startColor;
    toolSize = 1;

    //Set all mirroring to off.
    mirrorHorizontalActive = false;
    mirrorVerticalActive = false;
}

void Model::paintEvent(QPaintEvent *event)
{
    //Whenever any QPainter draw (or paint) methods are called, this paintEvent is notified.
    //So we paint to the QImage in other methods and then this method paints the QImage to the screen with scale.
    QPainter painter(this);
    QRect rect = event->rect();
    //Background image has already been scaled.
    painter.drawImage(rect, frames[0], rect);

    //Need to scale the currentframe image.
    painter.scale(scale, scale);

    //Copy the frame before drawing so the painter doesn't continuously draw to the image. Important with alpha values.
    QImage drawImage = frames[currentFrame].copy();
    painter.drawImage(rect, drawImage, rect);

    emit updated(frames[currentFrame], currentFrame);
    //Save frame for Undo stack.
    newFrame = frames[currentFrame].copy();
}

void Model::mousePressEvent(QMouseEvent *event)
{
    //Get mouse location
    QPoint loc;
    if(event->button() == Qt::LeftButton)
    {
        //First grab the mouse location and the set as lastpoint to be used later.
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

        //sets old frame to be used in undo/redo.
        oldFrame = frames[currentFrame].copy();
        draw(loc);
    }
}

void Model::mouseMoveEvent(QMouseEvent *event)
{
    QPoint loc;
    if(event->buttons() & Qt::LeftButton)
    {
        //Get mouse location
        loc = event->pos();

        //If bucket or color caster tool is selected, do nothing if mouse is moved while still clicked.
        if(currentTool!=Tool::Bucket && currentTool!=Tool::Caster)
        {
            //Rect, Line, and Ellipse tools set old frame to save for when the mouse is released.
            if(currentTool == Tool::Rect || currentTool == Tool::Line || currentTool == Tool::Ellipse)
            {
                frames[currentFrame] = oldFrame;
                update();
            }
            draw(loc);
        }
    }
}

void Model::mouseReleaseEvent(QMouseEvent *event)
{
    if(oldFrame != frames[currentFrame])
        emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::setUp(int imageSize = 32)
{
    //scale factor will be the size of the drawing pane in GUI (512) divided by size of actual image.
    scale = 512 / imageSize;

    //Create new QImage (Background image) of size and fill in.
    size.setHeight(imageSize);
    size.setWidth(imageSize);
    QImage newImage(QSize(32, 32), QImage::Format_ARGB32);
    newImage.fill(qRgba(120, 120, 120, 255));

    //Fill background with checkerboard pattern
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 32; j+=2)
        {
            if(i % 2 == 0)
                newImage.setPixelColor(i, j, qRgba(160, 160, 160, 255));
            else
                newImage.setPixelColor(i, j + 1, qRgba(160, 160, 160, 255));
        }
    }

    //add background frame to the vector. Position 0.
    //Background image is always a 32x32 grid no matter the size of the sprite.
    QImage scaledImage = newImage.scaled(QSize(512, 512));
    frames.push_back(scaledImage);
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
    currentTool = Tool::Rect;
}

void Model::lineButtonClicked()
{
    currentTool = Tool::Line;
}

void Model::ellipseButtonClicked()
{
    currentTool = Tool::Ellipse;
}

void Model::colorPickerButtonClicked()
{
    currentTool = Tool::Picker;
}

void Model::colorCasterButtonClicked()
{
    currentTool = Tool::Caster;
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
    oldFrame = frames[currentFrame].copy();
    frames[currentFrame] = ((QImage)frames[currentFrame]).mirrored(true, false);
    update();
    if(oldFrame != frames[currentFrame])
        emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::flipVerticalButtonClicked()
{
    oldFrame = frames[currentFrame].copy();
    frames[currentFrame] = ((QImage)frames[currentFrame]).mirrored(false, true);
    update();
    if(oldFrame != frames[currentFrame])
        emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::rotateClockwiseButtonClicked()
{
    oldFrame = frames[currentFrame].copy();

    QTransform transform;
    transform.rotate(90);

    frames[currentFrame] = ((QImage)frames[currentFrame]).transformed(transform);
    update();
    if(oldFrame != frames[currentFrame])
        emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::rotateCounterClockwiseButtonClicked()
{
    oldFrame = frames[currentFrame].copy();

    QTransform transform;
    transform.rotate(-90);

    frames[currentFrame] = ((QImage)frames[currentFrame]).transformed(transform);
    update();
    if(oldFrame != frames[currentFrame])
        emit framesSaved(oldFrame, frames[currentFrame]);
}

void Model::sliderValueChanged(int change)
{
    if(change  > 0){
        toolSize = change;
    }
    else{
        toolSize = 1;
    }
}

void Model::alphaValueChanged(int alpha)
{
    QColor newColor(currentColor.red(), currentColor.green(), currentColor.blue(), alpha);
    currentColor = newColor;

    //Tell mainwindow to update currentColorButton's color.
    emit colorChanged(currentColor);
}

void Model::colorPicked(QColor c)
{
    currentColor = QColor(c.red(), c.green(), c.blue());
    //make sure to move alpha slide when changed.
    emit(changeAlphaSlider(currentColor.alpha()));
    emit colorChanged(currentColor);
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

void Model::moveFrameButtonClicked(int i)
{
    iter_swap(frames.begin() + currentFrame, frames.begin() + i + 1);
    currentFrame = i + 1;
    emit framesMoved(frames, currentFrame);
}

void Model::clearFrameButtonClicked(int i)
{
    oldFrame = frames[currentFrame].copy();

    QImage newImage(size, QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));
    frames[i + 1] = newImage;

    changeFrame(i);

    if(oldFrame != frames[currentFrame])
        emit framesSaved(oldFrame, frames[currentFrame]);
}

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

void Model::changeFrame(int i)
{
    currentFrame = i + 1;

    //Draw frames.
    QImage drawImage = frames[currentFrame].copy();
    QPainter newPaint(&drawImage);
    newPaint.drawImage(QPoint(0, 0), drawImage);
    update();
}

void Model::newButtonClicked(int size)
{
    //Set starting size because the size of frames changes when removed.
   int startingSize = frames.size();
   for (int j = 0; j < startingSize - 1; j++)
   {
       //start removing from the back.
       removeFrameButtonClicked(frames.size() - 2);
   }

   frames.clear();
   setUp(size);

   addFrame();
   removeFrameButtonClicked(0);
   update();
}

void Model::saveButtonClicked(string fileName)
{
   //Set up saving
   //Convert to QString for easy opening of file
   QString qFileName = QString::fromStdString(fileName);
   QFile file(qFileName);


   //Resize the file to clear everything that was in it.
   file.resize(0);


   //Open file to start saving
   if (file.open(QIODevice::ReadWrite))
   {
       QTextStream stream( &file );
       stream << size.height() << " " << size.width() << endl;
       stream << frames.size() - 1 << endl;


       //Go through the vector to get each frame
       QImage curFrame;
       for (int z = 1; z < frames.size(); z++)
       {
           curFrame = frames[z];
           stream << z << endl;


           //Go through the pixels in rows and columns and print them.
           for(int i = 0; i < size.height(); i++)
           {
               for(int j = 0; j < size.width(); j++)
               {
                   QColor color = curFrame.pixelColor(j, i);
                   if (j == size.width() -1 )
                   {
                       stream << color.red() << " " << color.green() << " "  << color.blue() << " "  << color.alpha();
                   }
                   else
                   {
                       stream << color.red() << " " << color.green() << " "  << color.blue() << " "  << color.alpha() << " ";
                   }
               }
               stream << endl;
           }
       }
   }
   file.close();


   emit successfulSave();
}

/*
 * Use the normal saving function
 * Then tell the model to close the application
 */
void Model::saveAndCloseButtonClicked(string s)
{
    saveButtonClicked(s);
    emit closeMainSprite();
}

/*
 * Use the normal saving function
 * Then tell the model to start a new sprite
 */
void Model::saveThenNewButtonClicked(string s)
{
    saveButtonClicked(s);
    emit startNewSprite();
}

void Model::openButtonClicked(string fileName)
{
   //covert to QString for easy opening of file
   QString qFileName = QString::fromStdString(fileName);
   QFile file(qFileName);


   //If there's a problem opening the file
   if(!file.open(QIODevice::ReadOnly)) {
       QMessageBox::information(0, "error", file.errorString());
   }


   //Start reading in
   QTextStream in(&file);


   int countLine = 0;       //line number in .ssp file.
   int frameCount = 0;      //number of frames
   int currentFrameRow = 0; //constrained to (0 to size-1)
   int size = 0;            //size of square frame
   while(!in.atEnd())
   {
       countLine++;
       QString line = in.readLine();

       //split each line by space
       QStringList tokens = line.split(" ");
       for (int i = 0; i < tokens.count(); i+=4)
       {
           //if first line setup size
           if (countLine == 1 && i == 0)
           {
               int startingSize = frames.size();
               for (int j = 0; j < startingSize - 2; j++)
               {
                   removeFrameButtonClicked(frames.size() - 2);
               }

               frames.clear();

               size = tokens.at(0).toInt();
               setUp(size);
           }
           //if second line make that number of frames
           else if (countLine == 2)
           {
              //dont need to do anything
           }
           //if line = "Frame =" then we're on a new frame
           else if (tokens.count() == 1 && countLine != 2)
           {
               if(frameCount != 0)
               {
                   addFrame();
               }

               frameCount++;
               currentFrame = frameCount;
               currentFrameRow = 0;
           }
           //Now we're on the info for each pixel, start manipulating that frame
           else
           {
               if (currentFrameRow > size)
               {
                   break;
               }

               QColor c(tokens.at(i).toInt(), tokens.at(i + 1).toInt(), tokens.at(i + 2).toInt(), tokens.at(i + 3).toInt());

               // So we draw with a painter
               QPainter newPaint(&frames[frameCount]);
               newPaint.setPen(QPen(c,1));
               newPaint.drawPoint(i/4 , currentFrameRow - 1);

               update();
           }
       }
       currentFrameRow++;
   }

   //frames.erase(frames.begin() + frameCount + 1, frames.end());
   //Draw frames.
   for (int i = 0; i < frames.size() - 1; i++)
   {
      changeFrame(i);
   }


   file.close();
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

QImage Model::getFrame(int i)
{
    return frames[i];
}

std::vector<QImage> Model::getFrames()
{
    return frames;
}

/*
 * Helper method to create the uint8_t array that represents the rgba values of each pixel.
 * This method is used with the gif-h library to create a .gif file.
 */
void Model::convertFrameToArray(uint8_t *arr, int frameIndex, int gifSize)
{
    //We first need to scale the frame to the selected value given by user.

    QImage firstFrame(QSize(gifSize, gifSize), QImage::Format_ARGB32);
    firstFrame.fill(qRgba(255, 255, 255, 255));

    QImage newImage = frames[frameIndex].scaled(gifSize, gifSize);
    QPainter newPaint(&firstFrame);
    newPaint.setCompositionMode(QPainter::CompositionMode_SourceOver);
    newPaint.drawImage(QPoint(0, 0), newImage);

    for(int i = 0; i < gifSize; i++)
    {
        for(int j = 0; j < gifSize; j++)
        {
            //Grab pixel colors with .pixelColor method.
            QColor pixColor = firstFrame.pixelColor(j, i);
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

void Model::draw(QPoint point)
{
    QPoint mirrorPointX;
    QPoint mirrorPointY;
    QPoint mirrorPointXY;

    /* Scale the points along with the scale of the image.
     * This is so the points of the mouse coorelate with the points of the new scaled image
     * not the old, small image.*/
    point.setX(point.x()/scale);
    point.setY(point.y()/scale);

    mirrorPointX = point;
    mirrorPointY = point;

    mirrorPointX.setX(size.width()-point.x()-1);
    mirrorPointY.setY(size.height()-point.y()-1);

    mirrorPointXY.setX(mirrorPointX.x());
    mirrorPointXY.setY(mirrorPointY.y());

    //Use QPainter to modify QImage to be drawn by paintEvent.
    QPainter painter(&frames[currentFrame]);
    painter.setPen(QPen(currentColor, toolSize));


    //"Referesh" the composition mode in case it was changed.
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    //If alpha is set to zero, the pen should behave like the eraser.
    if(currentColor.alpha() == 0)
      painter.setCompositionMode(QPainter::CompositionMode_Clear);

    switch (currentTool)
    {
        case Tool::Pen:
        {
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
        }
        case Tool::Eraser:
        {
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
            painter.setPen(QPen(Qt::transparent, toolSize));
            painter.drawLine(lastPoint, point);
            lastPoint = point;
            break;
        }
        case Tool::Rect:
        {
            painter.setPen(QPen(currentColor, toolSize));
            painter.drawPoint(lastPoint);
            painter.drawRect(lastPoint.x(),lastPoint.y(), point.x()-lastPoint.x(), point.y() - lastPoint.y());
            break;
        }
        case Tool::Line:
        {
            painter.setPen(QPen(currentColor, toolSize));
            painter.drawLine(lastPoint, point);
            break;
        }
        case Tool::Ellipse:
        {
            painter.setPen(QPen(currentColor, toolSize));
            painter.drawEllipse(lastPoint.x(),lastPoint.y(), point.x()-lastPoint.x(), point.y() - lastPoint.y());
            break;
        }
        case Tool::Caster:
        {
            painter.setPen(QPen(currentColor, 1));
            QColor colorToCast(((QImage)frames[currentFrame]).pixelColor(point));
            int count = 0;
            for(int y = 0; y < ((QImage)frames[currentFrame]).height(); y++)
            {
              for(int x = 0; x < ((QImage)frames[currentFrame]).width(); x++)
              {
                  if( ((QImage)frames[currentFrame]).pixelColor(x,y) == colorToCast)
                  {
                      count++;
                      painter.drawPoint(x, y);
                  }
              }
            }
            break;
        }
        case Tool::Picker:
        {
            currentColor = ((QImage)frames[currentFrame]).pixelColor(point);
            emit colorChanged(currentColor);
            emit(changeAlphaSlider(currentColor.alpha()));
            break;
        }
        case Tool::Bucket:
        {
            FloodFill(point);
            break;
        }
        default:
            break;
    }

    update();
}

// This method is called when the bucket tool is selected and a pixel is clicked.
void Model::FloodFill(QPoint point)
{
    // Retrieves the color of the clicked pixel.
    QColor replacingColor = frames[currentFrame].pixelColor(point.x(), point.y());

    // If the clicked pixel has a different color than the selected one...
    if (currentColor != replacingColor)
    {
        // A queue takes track of the pixels that are checked, starting with the clicked one.
        queue<QPoint> q;
        QPoint clickedPoint(point.x(), point.y());

        // This stores the coordinates of the pixels that have already been checked, to avoid processing each pixel more than once.
        unordered_set <string> checked;

        // Pushes the coordinates of the clicked pixel into the "checked" unordered set.
        string clickedPointString = to_string(clickedPoint.x()) + "; " + to_string(clickedPoint.y());
        checked.insert(clickedPointString);
        q.push(clickedPoint);

        // While the queue is not empty, the algorithm does not stop.
        while (q.empty()!=true)
        {
            QPoint currentFlood = q.front();
            //Changes the color of the dequeued pixel.
            frames[currentFrame].setPixelColor(currentFlood.x(), currentFlood.y(), currentColor);

            //If there is a pixel on the currently processed pixel's right...
            if (currentFlood.x() != (size.width()-1))
            {
                string rightString = to_string(currentFlood.x()+1) + "; " + to_string(currentFlood.y());
                // If the pixel on the right of the currently processed pixel has not been checked yet.
                if ((checked.count(rightString))<1)
                {
                    //Enqueue the pixel.
                    if (frames[currentFrame].pixelColor(currentFlood.x()+1, currentFlood.y()) == replacingColor)
                    {
                        QPoint rightPoint(currentFlood.x()+1, currentFlood.y());
                        q.push(rightPoint);
                        checked.insert(rightString);
                    }
                }
            }
            //If there is a pixel on the currently processed pixel's left...
            if (currentFlood.x() != 0)
            {
                string leftString = to_string(currentFlood.x()-1) + "; " + to_string(currentFlood.y());
                // If the pixel on the left of the currently processed pixel has not been checked yet.
                if ((checked.count(leftString))<1)
                {
                    //Enqueue the pixel.
                    if (frames[currentFrame].pixelColor(currentFlood.x()-1, currentFlood.y()) == replacingColor)
                    {
                        QPoint leftPoint(currentFlood.x()-1, currentFlood.y());
                        q.push(leftPoint);
                        checked.insert(leftString);
                    }
                }
            }
            //If there is a pixel above the currently processed pixel...
            if (currentFlood.y() != 0)
            {
                string upString = to_string(currentFlood.x()) + "; " + to_string(currentFlood.y()-1);
                // If the pixel above the currently processed pixel has not been checked yet.
                if ((checked.count(upString))<1)
                {
                    //Enqueue the pixel.
                    if (frames[currentFrame].pixelColor(currentFlood.x(), currentFlood.y()-1) == replacingColor)
                    {
                        QPoint upPoint(currentFlood.x(), currentFlood.y()-1);
                        q.push(upPoint);
                        checked.insert(upString);
                    }
                }
            }
            //If there is a pixel below the currently processed pixel...
            if (currentFlood.y() != (size.width()-1))
            {
                string downString = to_string(currentFlood.x()) + "; " + to_string(currentFlood.y()+1);
                // If the pixel below the currently processed pixel has not been checked yet.
                if ((checked.count(downString))<1)
                {
                    //Enqueue the pixel.
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
    }
}
