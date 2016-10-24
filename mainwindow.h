#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "model.h"
#include "preview.h"
#include "export.h"
#include <string>
#include <iostream>
#include <QGridLayout>
#include <QString>
#include <QPixmap>
#include <QColorDialog>

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
    void getDrawingSize(string s);

    void renablePreview();

private slots:
    void on_UndoButton_clicked();
    void on_RedoButton_clicked();

    void on_PenButton_clicked();
    void on_EraserButton_clicked();
    void on_RectButton_clicked();
    void on_LineButton_clicked();
    void on_ColorPickerButton_clicked();
    void on_ColorCasterButton_clicked();
    void on_BucketButton_clicked();
    void on_MirrorHorizontalButton_clicked();
    void on_MirrorVerticalButton_clicked();
    void on_FlipHorizontalButton_clicked();
    void on_FlipVerticalButton_clicked();
    void on_RotateClockwiseButton_clicked();
    void on_RotateCounterClockwiseButton_clicked();

    void on_SizeSlider_valueChanged(int value);
    void on_ColorButton_clicked();

    void on_PreviewButton_clicked();
    void on_AddFrameButton_clicked();
    void on_DuplicateFrameButton_clicked();
    void on_RemoveFrameButton_clicked();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionExport_triggered();
    void on_ActualSizeCheck_stateChanged(int arg1);
    void on_FPSSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QGridLayout* canvasLayout;

    Model model;

    Preview preview;

    Export exportWindow;

    QColorDialog colorDialog;

};

#endif // MAINWINDOW_H
