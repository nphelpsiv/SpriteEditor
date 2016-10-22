#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

    void on_MirrorButton_clicked();

    void on_RotateButton_clicked();

    void on_FlipButton_clicked();

    void on_PreviewButton_clicked();

    void on_AddFrameButton_clicked();

    void on_DuplicateFrameButton_clicked();

    void on_RemoveFrameButton_clicked();

    void on_actionSave_clicked();

private:
    Ui::MainWindow *ui;

    Model model;
};

#endif // MAINWINDOW_H
