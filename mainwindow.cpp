#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect rect;
    rect.setX(170);
    rect.setY(20);
    rect.setSize(QSize(512,512));

    canvasLayout = new QGridLayout(ui->Canvas);

    canvasLayout->addWidget(&model, 0, 0);
    //ui->Canvas = &model;
    //ui->Canvas->setGeometry(190, 20, 512, 512);

    connect(&preview, SIGNAL(renableButton()),
                        this, SLOT(renablePreview()));

    // Set the background color on startup to black
    QColor originalColor(0,0,0,255);
    QPixmap px(500, 500);
    px.fill(originalColor);
    ui->ColorButton->setIcon(px);
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

void MainWindow::on_PreviewButton_clicked()
{
    preview.show();
    ui->PreviewButton->setEnabled(false);
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

void MainWindow::getDrawingSize(string size)
{
    cout << size << " from mainwindow" << endl;
    //change
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Sprite"), "~/", tr("Sprite Files (*.ssp)"));
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Sprite"), "/home/McKay", tr("Sprite Files (*.spp)"));
}

void MainWindow::on_actionExport_triggered()
{
    exportWindow.show();
}

void MainWindow::on_ActualSizeCheck_stateChanged(int arg1)
{
    emit model.actualSizeBoxChecked(arg1);
}

void MainWindow::on_FPSSpinBox_valueChanged(int arg1)
{
    emit model.FPSSpinBoxChanged(arg1);
}

void MainWindow::on_SizeSlider_valueChanged(int value)
{
    emit model.sliderValueChanged(value);
}

void MainWindow::on_MirrorHorizontalButton_clicked()
{
    emit model.mirrorHorizontalButtonClicked();
}

void MainWindow::on_MirrorVerticalButton_clicked()
{
    emit model.mirrorVerticalButtonClicked();
}

void MainWindow::on_FlipHorizontalButton_clicked()
{
    emit model.flipHorizontalButtonClicked();
}

void MainWindow::on_FlipVerticalButton_clicked()
{
    emit model.flipVerticalButtonClicked();
}

void MainWindow::on_RotateClockwiseButton_clicked()
{
    emit model.rotateClockwiseButtonClicked();
}

void MainWindow::on_RotateCounterClockwiseButton_clicked()
{
    emit model.rotateCounterClockwiseButtonClicked();
}

void MainWindow::renablePreview()
{
    ui->PreviewButton->setEnabled(true);
}

void MainWindow::on_ColorButton_clicked()
{
    // Get the color picked and then set the background of the button to that color.
    QColor color = colorDialog.getColor();
    QPixmap px(100, 100);
    px.fill(color);
    ui->ColorButton->setIcon(px);

    // Now tell the model what color is picked.
    emit model.colorPicked(color);
}

