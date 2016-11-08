/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * This class defines the model logic which modifies and displays pixel images.
 * Also handles saving, loading, and exporting.
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>
#include <vector>
#include <QPixmap>
#include <string.h>
#include <QColor>
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
    //Model Constructor
    Model(QWidget *parent = 0);

    //Vector which holds the QImages that represent frames.
    std::vector<QImage> frames;
    //Index of current frame within frames vector.
    int currentFrame;

signals:
    /*
     * Signals the color has changed passing the QColor selected.
     */
    void colorChanged(QColor);
    /*
     * Signals a frame was added passing the full vector of frames back to mainwindow.
     */
    void frameAdded(std::vector<QImage>);
    /*
     * Signals when a frame is removed passing the full vector of frames back to mainwindow.
     */
    void frameRemoved(std::vector<QImage>);
    /*
     * Signals that a frame was updated and passes the QImage that was updated along with the index of that image.
     */
    void updated(QImage, int);
    /*
     * Signals that a frame was saved when mouse was released. [This is only used for Rect, Ellipse, and Line tools]
     */
    void framesSaved(QImage, QImage);
    /*
     * Signals that a frame was moved within the frames vector.
     */
    void framesMoved(std::vector<QImage>, int);
    /*
     * Signals to mainwindow that the main window should be closed.
     */
    void closeMainSprite();
    /*
     * Signals to mainwindow that a new sprite will be started.
     */
    void startNewSprite();
    /*
     * Signals to mainwindow that the alpha slider's value was changed.
     */
    void changeAlphaSlider(int);
    /*
     * Signals that a save was successful.
     */
    void successfulSave();

protected:
    /*
     * This method is notified whenever a painter object paints to a QImage. This method draws the frame to the screen.
     */
    void paintEvent(QPaintEvent *event);
    /*
     * This method is notified whenever the mouse is pressed. This is used for coordinates for drawing with a painter.
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    /*
     * This method is notified whenever the mouse has moved while being pressed.
     */
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    /*
     * This method is notified whenever the mouse has moved from a pressed state to a released state.
     */
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    /*
     * Initiating method for the model. This sets up the frames and necessary values.
     */
    void setUp(int canvasSize);

    /*
     * This method is notified when the pen button was clicked.
     */
    void penButtonClicked();
    /*
     * This method is notified when the eraser button was clicked.
     */
    void eraserButtonClicked();
    /*
     * This method is notified when the rectangle button was clicked.
     */
    void rectButtonClicked();
    /*
     * This method is notified when the line button was clicked.
     */
    void lineButtonClicked();
    /*
     * This method is notified when the ellipse button was clicked.
     */
    void ellipseButtonClicked();
    /*
     * This method is notified when the color picker button was clicked.
     */
    void colorPickerButtonClicked();
    /*
     * This method is notified when the color caster button was clicked.
     */
    void colorCasterButtonClicked();
    /*
     * This method is notified when the bucket button was clicked.
     */
    void bucketButtonClicked();
    /*
     * This method is notified when the horizontal mirror button is toggled.
     */
    void mirrorHorizontalButtonToggled(bool checked);
    /*
     * This method is notified when the vertical mirror button is toggled.
     */
    void mirrorVerticalButtonToggled(bool checked);
    /*
     * This method is notified when the horizontal flip button was clicked.
     */
    void flipHorizontalButtonClicked();
    /*
     * This method is notified when the vertical flip button was clicked.
     */
    void flipVerticalButtonClicked();
    /*
     * This method is notified when the clockwise rotate button was clicked.
     */
    void rotateClockwiseButtonClicked();
    /*
     * This method is notified when the counter-clockwise rotate button was clicked.
     */
    void rotateCounterClockwiseButtonClicked();

    /*
     * This method is notified when the tool size slider value was changed.
     */
    void sliderValueChanged(int change);
    /*
     * This method is notified when the alpha slider value was changed.
     */
    void alphaValueChanged(int a);
    /*
     * This method is notified when the color has been changed by the color picker.
     */
    void colorPicked(QColor c);

    /*
     * This method is notified when the duplicate frame button was clicked.
     * It then duplicates the current frame and inserts it into the frames vector.
     */
    void duplicateFrameButtonClicked(int i);
    /*
     * This method is notified when the remove frame button is clicked.
     * It then removes that frame and moves other frames down.
     */
    void removeFrameButtonClicked(int i);
    /*
     * This method is notified when the move left or move right button is clicked.
     * It then moves the frame either to the left or to the right in the vector.
     * i is the index to where it will be moved.
     */
    void moveFrameButtonClicked(int i);
    /*
     * This method is notified when the clear frame button is pressed.
     * It then clears all of the pixels in that frame.
     */
    void clearFrameButtonClicked(int i);
    /*
     * This method is notified when the add frame button is pressed and adds a frame to the vector.
     */
    void addFrame();
    /*
     * This method is notified when the frame was changed so the model can update the current frame.
     */
    void changeFrame(int i);

    /*
     * This method is notified when the new menu item is selected.
     * It will then attempt to open the file specified.
     */
    void newButtonClicked(int size);
    /*
     * This method is notified when the save menu item is selected.
     * It will then save the file under the specified filename.
     */
    void saveButtonClicked(string s);
    /*
     * This method is notified when the user wants to save and then close.
     */
    void saveAndCloseButtonClicked(string s);
    /*
     * This method is notified when the user wants to save then create a new sprite.
     */
    void saveThenNewButtonClicked(string s);
    /*
     * This method is notified when the open menu item is selected.
     * It then opens a dialog to open a .ssp file.
     */
    void openButtonClicked(string s);
    /*
     * This method is notified when the export menu item is selected.
     * This method used the Gif-h library to export the frames in a .gif format.
     */
    void exportSelected(int, std::string, int);

    /*
     * Returns a std::vector of the QImage frames.
     */
    std::vector<QImage> getFrames();
    /*
     * Returns a QImage frame at the specified index.
     */
    QImage getFrame(int i);



private:
    //Size of the image (width, height)
    QSize size;
    //This is a scale factor used to scale the image to 512X512
    int scale;

    //The currently selected color.
    QColor currentColor;

    //This was the last point the was drawn. Used in calculation of tools drawing.
    QPoint lastPoint;
    //This is the last x coordinate used in the mirror tool.
    QPoint mirrorLastPointX;
    //This is the last y coordinate used in the mirror tool.
    QPoint mirrorLastPointY;
    //This is the last x,y coordinate used in the mirror tool.
    QPoint mirrorLastPointXY;

    //Both oldFrame and newFrame used in undo/redo
    QImage oldFrame;
    QImage newFrame;

    //Enum which keeps track of what tool is selected.
    enum Tool {Pen, Eraser, Rect, Line, Ellipse, Caster, Picker, Bucket};
    int currentTool;
    int toolSize;

    //Booleans used for mirror drawing.
    bool mirrorHorizontalActive;
    bool mirrorVerticalActive;

    /*
     * Helper method used in converting to a GIF.
     * This mehtod converts the QImage into a uint8_t array of rgba values.
     * This array is used in the Gif-h library to generate the GIF.
     */
    void convertFrameToArray(uint8_t*, int, int);
    /*
     * This is the main drawing method.
     * All tools use this method to draw to the frame.
     */
    void draw(QPoint);
    /*
     * This method is used by the bucket tool to draw a correct bucket fill.
     */
    void FloodFill(QPoint point);
};

#endif // MODEL_H
