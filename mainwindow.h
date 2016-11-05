#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"
#include "preview.h"
#include "export.h"
#include "newproject.h"
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

public slots:
    void getDrawingSize(int s); //Should this really be a slot?
    void previewUpdate();
    void renablePreview();

    void frameAdded(std::vector<QImage>);
    void frameUpdated(QImage, int);
    void frameButtonPressed();
    void frameRemoved(std::vector<QImage>);
    void frameMoved(std::vector<QImage>, int);
    void colorChanged(QColor color);
    void changeAlphaSlider(int);

    void loadButtonClicked();

    void moveScrollBarToSelected(int, int);

    void newProjectSelected(int);
private slots:
    void on_PenButton_clicked();
    void on_EraserButton_clicked();
    void on_RectButton_clicked();
    void on_LineButton_clicked();
    void on_ColorPickerButton_clicked();
    void on_BucketButton_clicked();
    void on_ColorCasterButton_clicked();
    void on_MirrorHorizontalButton_toggled(bool checked);
    void on_MirrorVerticalButton_toggled(bool checked);
    void on_FlipHorizontalButton_clicked();
    void on_FlipVerticalButton_clicked();
    void on_RotateClockwiseButton_clicked();
    void on_RotateCounterClockwiseButton_clicked();

    void on_SizeSlider_valueChanged(int value);
    void on_ColorButton_clicked();

    void on_PreviewButton_clicked();
    void on_DuplicateFrameButton_clicked();
    void on_RemoveFrameButton_clicked();
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionExport_triggered();
    void on_ActualSizeCheck_stateChanged(int arg1);
    void on_FPSSpinBox_valueChanged(int arg1);

    void on_AddFrameButton_clicked();

    void framesSaved(QImage, QImage);

    void on_EllipseButton_clicked();

    void uncheckAllToolButtons();

    void on_AlphaSlider_valueChanged(int value);

    void on_moveFrameLeftButton_clicked();

    void on_moveFrameRightButton_clicked();

    void on_clearFrameButton_clicked();

private:
    void createActions();

    Ui::MainWindow *ui;

    QGridLayout* canvasLayout;

    Model model;

    Preview preview;

    Export exportWindow;

    NewProject newProject;

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

};

#endif // MAINWINDOW_H
