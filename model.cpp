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

void Model::mirrorHorizontalButtonToggled()
{
    cout << "mirror horizontal (model)" << endl;
}

void Model::mirrorVerticalButtonToggled()
{
    cout << "mirror vertical (model)" << endl;
}

void Model::flipHorizontalButtonClicked()
{
    cout << "flip horizontal (model)" << endl;
}
void Model::flipVerticalButtonClicked()
{
    cout << "flip vertical (model)" << endl;
}

void Model::rotateClockwiseButtonClicked()
{
    cout << "rotate Clockwise (model)" << endl;
}

void Model::rotateCounterClockwiseButtonClicked()
{
    cout << "rotate Counter Clockwise (model)" << endl;
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

void Model::removeFrameButtonClicked()
{
    cout << "removeF (model)" << endl;
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
        for (int i = 1; i < frames.size(); i++)
        {
            curFrame = frames[i];
            stream << "Frame = " << i << endl;

            // Go through the pixels in rows and columns and print them.
            for(int i = 0; i < size.height(); i++)
            {
                for(int j = 0; j < size.width(); j++)
                {
                    QColor color = curFrame.pixelColor(i, j);
                    if (j == size.width() -1 )
                    {
                        stream << color.red() << color.green() << color.blue() << color.alpha();
                    }
                    else
                    {
                        //stream << curFrame.pixelColor(i, j).rgba();
                        stream << color.red() << color.green() << color.blue() << color.alpha() << " ";
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

    int countLine = 0;
    int frameCount = 0;
    int rowLine = 0;
    while(!in.atEnd()) {
        countLine++;
        QString line = in.readLine();

        // split each line by space
        QStringList lineColumn = line.split(" ");
        for (int i = 0; i < lineColumn.count(); i++)
        {
            // if first line setup size
            if (countLine == 1 && i == 0)
            {
                int size = lineColumn.at(0).toInt();
                setUp(size);
            }
            // if second line make that number of frames
            else if (countLine == 2)
            {
               // dont need to do anything
            }
            // if line = "Frame =" then we're on a new frame
            else if (lineColumn.at(i) == "Frame")
            {
                addFrame();
                frameCount++;
                rowLine = 0;
            }
            // Now we're on the info for each pixel, start manipulating that frame
            else
            {

                //QImage curFrame = frames[frameCount];

                if (rowLine >= frames[frameCount].height())
                {
                    break;
                }

                QColor color = lineColumn.at(i);
                color.setRed();
                //QString name = color.name();
                cout << lineColumn.at(i).toStdString();
                cout << "Current Frame = " << frameCount << ". Pixel at " << "(" << rowLine << ", " << i << "): " << lineColumn.at(i).toStdString() << endl;
                QColor c(100, 100, 100, 155);
                frames[frameCount].setPixelColor(rowLine - 1, i, color);

                //Draw frames.
                QPainter newPaint(&frames[frameCount]);
                newPaint.drawImage(QPoint(0, 0), frames[frameCount]);

                update();
            }
        }
        rowLine++;
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
    //Scale the points along with the scale of the image.
    //This is so the points of the mouse coorelate with the points of the new scaled image
    //not the old, small image.
    point.setX(point.x()/scale);
    point.setY(point.y()/scale);

    //Use QPainter to modify QImage to be drawn by paintEvent.
    QPainter painter(&frames[currentFrame]);
    painter.setPen(QPen(Qt::blue, toolSize));

    switch (currentTool)
    {
    case Tool::Pen:
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
