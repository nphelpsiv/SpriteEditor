/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * This class represents the Main Window of the application.
 * This is where all the main graphical aspects will be presented to the user.
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"
#include "preview.h"
#include "export.h"
#include "newproject.h"
#include "saveonclose.h"
#include "addframecommand.h"
#include "removeframecommand.h"
#include "duplicateframecommand.h"
#include "moveframecommand.h"
#include "drawcommand.h"
#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <QGridLayout>
#include <QString>
#include <QPixmap>
#include <QColorDialog>
#include <QTimer>
#include <QUndoStack>
#include <QProcess>
#include <QMessageBox>
#include <QDesktopServices>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void canceld();

public slots:
    void getDrawingSize(int s);
    void previewUpdate();
    void renablePreview();

    /*
     * Slot for when frame is added.
     * Recieves a vector of QImages from Model to update all the frames.
     */
    void frameAdded(std::vector<QImage>);
    /*
     * Slot for when frame is updated.
     * This will draw the frame in a mini version as an icon.
     */
    void frameUpdated(QImage, int);
    /*
     * Slot for when a frame is selected.
     * Should switch to that frame in the drawing pane.
     */
    void frameButtonPressed();
    void frameRemoved(std::vector<QImage>);
    void frameMoved(std::vector<QImage>, int);
    void moveScrollBarToSelected(int, int);

    //Allows the model to change the color of the colorSelectedButton.
    void colorChanged(QColor color);
    void changeAlphaSlider(int);

    // For dealing with opening, saving, and new actions
    void newProjectSelected(int);
    /*
     * Close this application
     * @brief MainWindow::closeMainSpriteSelected
     */
    void closeMainSpriteSelected();
    void loadButtonClicked();
    void openFileSelected();
    /*
     * Send to the model that it needs saved.
     * This model method is slighlty different in that it will
     * close the application after it's saved.
     * @brief MainWindow::newWithSave
     */
    void saveAndClose();
    void saveThenOpenSpriteSelected();
    /*
     * Send to the model that it needs saved.
     * This model method is slighlty different in that it will call back
     * to the mainwindow to show the newProjcect window after it has been saved.
     * @brief MainWindow::newWithSave
     */
    void newWithSave();
    //Start a New Sprite @brief MainWindow::newNoSave
    void newNoSave();
    void successfullySaved();

private slots:

    /*
     * For the following we let the model know a button has been
     * clicked, and "check" the corresponding button clicked.
     */
    void on_PenButton_clicked();
    void on_EraserButton_clicked();
    void on_RectButton_clicked();
    void on_LineButton_clicked();
    void on_BucketButton_clicked();
    void on_EllipseButton_clicked();
    void on_ColorCasterButton_clicked();
    void on_ColorPickerButton_clicked();
    void on_MirrorHorizontalButton_toggled(bool checked);
    void on_MirrorVerticalButton_toggled(bool checked);
    void on_FlipHorizontalButton_clicked();
    void on_FlipVerticalButton_clicked();
    void on_RotateClockwiseButton_clicked();
    void on_RotateCounterClockwiseButton_clicked();

    void on_SizeSlider_valueChanged(int value);
    void on_AlphaSlider_valueChanged(int value);
    void on_ColorButton_clicked();

    //Sets up and instantiates a prefrabricated preview window.
    void on_PreviewButton_clicked();
    void on_ActualSizeCheck_stateChanged(int arg1);
    void on_FPSSpinBox_valueChanged(int arg1);

    //Called when switching frames in the preview window.
    void on_AddFrameButton_clicked();
    void on_DuplicateFrameButton_clicked();
    void on_RemoveFrameButton_clicked();
    void on_moveFrameLeftButton_clicked();
    void on_moveFrameRightButton_clicked();
    void on_clearFrameButton_clicked();

    void on_actionNew_triggered();
    /**
     * Have the saveCloseDialog choose what to do when trying to open a new Sprite
     * @brief MainWindow::on_actionNew_triggered
     */
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    //Show the export window, this window handles further actions.
    void on_actionExport_triggered();
    /*
     * When trying to close let the SaveCloseDialog determine which actions need to happen.
     * @brief MainWindow::on_actionClose_triggered
     */
    void on_actionClose_triggered();
    void on_actionHelp_triggered();

    void framesSaved(QImage, QImage);

    void uncheckAllToolButtons();

    void changesMade(int);

private:
    //Setting up Actions
    void createActions();
    void closeEvent(QCloseEvent *event);

    Ui::MainWindow *ui;

    QGridLayout* canvasLayout;

    Model model;
    Preview preview;
    Export exportWindow;
    NewProject newProject;
    SaveOnClose saveCloseDialog;

    QColorDialog colorDialog;

    int currentFrame;

    QHBoxLayout *layout;

    std::vector<QPushButton*> frameButtons;

    QTimer timer;

    int FPS;
    int timerFrame;

    QAction *undoAction;
    QAction *redoAction;

    QUndoStack *undoStack;

    bool unsavedChanges;
};

#endif // MAINWINDOW_H
