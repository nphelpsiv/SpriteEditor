#include "model.h"
#include <iostream>
#include <QtGui>
#include <queue>

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
    currentTool = Tool::Pen;
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

void Model::saveButtonClicked(string fileName)
{
   // Set up saving
   // Convert to QString for easy opening of file
   QString qFileName = QString::fromStdString(fileName);
   QFile file(qFileName);


   // Resize the file to clear everything that was in it.
   file.resize(0);


   // Open file to start saving
   if (file.open(QIODevice::ReadWrite))
   {
       QTextStream stream( &file );
       stream << size.height() << " " << size.width() << endl;
       stream << frames.size() - 1 << endl;


       // Go through the vector to get each frame
       QImage curFrame;
       for (int z = 1; z < frames.size(); z++)
       {
           curFrame = frames[z];
           stream << z << endl;


           // Go through the pixels in rows and columns and print them.
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
}

void Model::openButtonClicked(string fileName)
{
   // covert to QString for easy opening of file
   QString qFileName = QString::fromStdString(fileName);
   QFile file(qFileName);


   // If there's a problem opening the file
   if(!file.open(QIODevice::ReadOnly)) {
       QMessageBox::information(0, "error", file.errorString());
   }


   // Start reading in
   QTextStream in(&file);


   int countLine = 0;       //line number in .ssp file.
   int frameCount = 0;      //number of frames
   int currentFrameRow = 0; //constrained to (0 to size-1)
   int size = 0;            //size of square frame
   while(!in.atEnd()) {
       countLine++;
       QString line = in.readLine();


       // split each line by space
       QStringList tokens = line.split(" ");
       for (int i = 0; i < tokens.count(); i+=4)
       {
           // if first line setup size
           if (countLine == 1 && i == 0)
           {
               //for (int var = 0; var < total; ++var)
               //{
               //    removeFrame();
               //}


               size = tokens.at(0).toInt();
               setUp(size);


               cout << size << endl;
           }
           // if second line make that number of frames
           else if (countLine == 2)
           {
              // dont need to do anything
           }
           // if line = "Frame =" then we're on a new frame
           else if (tokens.count() == 1 && countLine != 2)
           {
               addFrame();
               frameCount++;
               currentFrameRow = 0;
           }
           // Now we're on the info for each pixel, start manipulating that frame
           else
           {
               if (currentFrameRow > size)
               {
                   break;
               }


               //QColor color = lineColumn.at(i);
               //QString name = color.name();
               cout << "Current Frame = " << frameCount << ". Pixel at " << "(" << i/4 << ", " << currentFrameRow - 1 << "): " << tokens.at(i).toStdString() << "," << tokens.at(i + 1).toStdString() << "," << tokens.at(i + 2).toStdString() << "," << tokens.at(i + 3).toStdString() << endl;


                   QColor c(tokens.at(i).toInt(), tokens.at(i + 1).toInt(), tokens.at(i + 2).toInt(), tokens.at(i + 3).toInt());


                   //QPoint position(i/4, currentFrameRow - 1);
                   //((QImage)frames[frameCount]).setPixelColor(position, c);




                   QPainter newPaint(&frames[frameCount]);
                   newPaint.setPen(QPen(c,1));
                   newPaint.drawPoint(i/4 , currentFrameRow - 1);


                   update();
           }


       }
       currentFrameRow++;


   }
   //Draw frames.
   for (int i = 0; i < frames.size() - 1; i++)
   {
      changeFrame(i);
   }


   file.close();
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
    painter.setPen(QPen(currentColor, toolSize));

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
        break;
    case Tool::Caster:
        {
          QColor colorToCast( ((QImage)frames[currentFrame]).pixelColor(point) );

          int count = 0;
          for(int y = 0; y < ((QImage)frames[currentFrame]).height(); y++)
          {
              for(int x = 0; x < ((QImage)frames[currentFrame]).width(); x++)
              {
                  if( ((QImage)frames[currentFrame]).pixelColor(x,y) == colorToCast )
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
        cout<< clickedPoint.x()<< '; '<< clickedPoint.y()<<endl;
        q.push(clickedPoint);
        while (q.empty()!=true)
        {
            QPoint currentFlood = q.front();
            frames[currentFrame].setPixelColor(currentFlood.x(), currentFlood.y(), currentColor);
            if (currentFlood.x() != (size.width()-1))
            {
                if (frames[currentFrame].pixelColor(currentFlood.x()+1, currentFlood.y()) == replacingColor)
                {
                    QPoint rightPoint(currentFlood.x()+1, currentFlood.y());
                    q.push(rightPoint);
                }
            }
            if (currentFlood.x() != 0)
            {
                if (frames[currentFrame].pixelColor(currentFlood.x()-1, currentFlood.y()) == replacingColor)
                {
                    QPoint leftPoint(currentFlood.x()-1, currentFlood.y());
                    q.push(leftPoint);
                }
            }
            if (currentFlood.y() != 0)
            {
                if (frames[currentFrame].pixelColor(currentFlood.x(), currentFlood.y()-1) == replacingColor)
                {
                    QPoint upPoint(currentFlood.x(), currentFlood.y()-1);
                    q.push(upPoint);
                }
            }
            if (currentFlood.y() != (size.width()-1))
            {
                if (frames[currentFrame].pixelColor(currentFlood.x(), currentFlood.y()+1) == replacingColor)
                {
                    QPoint downPoint(currentFlood.x(), currentFlood.y()+1);
                    q.push(downPoint);
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
