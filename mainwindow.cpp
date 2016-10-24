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
        tr("Save Sprite"), "/home/McKay", tr("Sprite Files (*.ssp)"));
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

void MainWindow::on_RotateDropdown_currentTextChanged(const QString &arg1)
{

    emit model.rotateDropdownChanged(arg1.toStdString());
}

void MainWindow::on_MirrorDropdown_currentTextChanged(const QString &arg1)
{
    emit model.mirrorDropdownChanged(arg1.toStdString());
}

void MainWindow::on_FlipDropdown_currentTextChanged(const QString &arg1)
{
    emit model.flipDropdownChanged(arg1.toStdString());
}

void MainWindow::renablePreview()
{
    ui->PreviewButton->setEnabled(true);
}
