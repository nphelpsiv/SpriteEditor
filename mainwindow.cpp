#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_UndoButton_clicked()
{
    emit model.undoButtonClicked();
}

void MainWindow::on_RedoButton_clicked()
{
    emit model.redoButtonClicked();
}

void MainWindow::on_PenButton_clicked()
{
    emit model.penButtonClicked();
}

void MainWindow::on_EraserButton_clicked()
{
    emit model.eraserButtonClicked();
}

void MainWindow::on_RectButton_clicked()
{
    emit model.rectButtonClicked();
}

void MainWindow::on_LineButton_clicked()
{
    emit model.lineButtonClicked();
}

void MainWindow::on_ColorPickerButton_clicked()
{
    emit model.colorPickerButtonClicked();
}

void MainWindow::on_ColorCasterButton_clicked()
{
    emit model.colorCasterButtonClicked();
}

void MainWindow::on_BucketButton_clicked()
{
    emit model.bucketButtonClicked();
}

void MainWindow::on_MirrorButton_clicked()
{
    emit model.mirrorButtonClicked();
}

void MainWindow::on_RotateButton_clicked()
{
    emit model.rotateButtonClicked();
}

void MainWindow::on_FlipButton_clicked()
{
    emit model.flipButtonClicked();
}

void MainWindow::on_PreviewButton_clicked()
{
    emit model.previewButtonClicked();
}

void MainWindow::on_AddFrameButton_clicked()
{
    emit model.addFrameButtonClicked();
}

void MainWindow::on_DuplicateFrameButton_clicked()
{
    emit model.duplicateFrameButtonClicked();
}

void MainWindow::on_RemoveFrameButton_clicked()
{
    emit model.removeFrameButtonClicked();
}
