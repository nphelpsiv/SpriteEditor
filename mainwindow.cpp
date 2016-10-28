#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(previewUpdate()));

    QRect rect;
    rect.setX(170);
    rect.setY(20);
    rect.setSize(QSize(512,512));

    canvasLayout = new QGridLayout(ui->Canvas);

    canvasLayout->addWidget(&model, 0, 0);
    //ui->Canvas = &model;
    //ui->Canvas->setGeometry(190, 20, 512, 512);

    //Connection to renable preview button when preview window is closed.
    connect(&preview, SIGNAL(renableButton()),
                        this, SLOT(renablePreview()));

    //Set the background color on startup to black
    QColor originalColor(0,0,0,255);
    QPixmap px(500, 500);
    px.fill(originalColor);
    ui->ColorButton->setIcon(px);

    //Create the Frame viewing area.
    QWidget *view = new QWidget;
    QWidget *w = new QWidget;
    QWidget *w1 = new QWidget;
    ui->FramesViewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->FramesViewArea->setWidget(view);
    ui->FramesViewArea->setWidgetResizable(true);

    //Horizontal Box Layout
    layout = new QHBoxLayout(view);

    //Fill vector with 30 blank frame buttons.
    for(int i = 0; i < 30; i++)
    {
        QPushButton *frame = new QPushButton("");
        QPalette pal = frame->palette();
        pal.setColor(QPalette::Button, QColor(Qt::white));
        frame->setAutoFillBackground(true);
        frame->setPalette(pal);
        frame->setFixedSize(64,64);
        frame->setFlat(true);
        frame->setVisible(false);
        layout->addWidget(frame);
        frameButtons.push_back(frame);

        connect(frame, SIGNAL(pressed()), this, SLOT(frameButtonPressed()));
    }

    //Show first frame upon start.
    frameButtons[0]->setVisible(true);
    currentFrame = 0;

    layout->addWidget(w);
    layout->addWidget(w1);

    FPS = ui->FPSSpinBox->value();
    //Connects for signals when frame is changed.
    connect(&model, SIGNAL(frameAdded(QImage)),
            this, SLOT(frameAdded(QImage)));

    connect(&model, SIGNAL(updated(QImage)),
            this, SLOT(frameUpdated(QImage)));

    connect(&model, SIGNAL(frameDuplicated(QImage,int)),
            this, SLOT(frameDuplicated(QImage,int)));

    connect(&model, SIGNAL(frameRemoved(std::vector<QImage>)),
            this, SLOT(frameRemoved(std::vector<QImage>)));

    connect(&model, SIGNAL(colorChanged(QColor)),
            this, SLOT(colorChanged(QColor)));

    connect(&exportWindow, SIGNAL(exportSelected(int, std::string, int)),
            &model, SLOT(exportSelected(int, std::string, int)));
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

void MainWindow::on_BucketButton_clicked()
{
    emit model.bucketButtonClicked();
}

void MainWindow::on_PreviewButton_clicked()
{
    timerFrame = 0;
    previewUpdate();
    preview.show();
    ui->PreviewButton->setEnabled(false);
    int eq = 1000/FPS;
    timer.start(eq);

}

void MainWindow::previewUpdate()
{
    timerFrame++;
    timerFrame = timerFrame % (model.getFrames().size());
    if(timerFrame == 0){
        timerFrame = 1;
    }
    emit preview.displayImage(model.getFrame(timerFrame));
}

void MainWindow::on_AddFrameButton_clicked()
{
    emit model.addFrameButtonClicked();
}

void MainWindow::on_DuplicateFrameButton_clicked()
{
    emit model.duplicateFrameButtonClicked(currentFrame);
}

void MainWindow::on_RemoveFrameButton_clicked()
{
    emit model.removeFrameButtonClicked(currentFrame);
}

void MainWindow::getDrawingSize(int size)
{
    exportWindow.setActualSize(size);
    emit model.setUp(size);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Sprite"), "~/", tr("Sprite Files (*.ssp)"));
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Sprite"), "~/", tr("Sprite Files (*.spp)"));
}

void MainWindow::on_actionExport_triggered()
{
    exportWindow.show();
}

void MainWindow::on_ActualSizeCheck_stateChanged(int arg1)
{
    emit preview.actualSizeBoxChecked(arg1);
}

void MainWindow::on_FPSSpinBox_valueChanged(int arg1)
{
    FPS = arg1;
    emit model.FPSSpinBoxChanged(arg1);
}

void MainWindow::on_SizeSlider_valueChanged(int value)
{
    emit model.sliderValueChanged(value);
}

void MainWindow::on_MirrorHorizontalButton_toggled(bool checked)
{
    emit model.mirrorHorizontalButtonToggled(checked);
}

void MainWindow::on_MirrorVerticalButton_toggled(bool checked)
{
    emit model.mirrorVerticalButtonToggled(checked);
}

void MainWindow::on_ColorCasterButton_clicked()
{
    emit model.colorCasterButtonClicked();
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
    timer.stop();
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

/*
 * Slot for when frame is added.
 * Recieves a QImage from Model to add.
 */
void MainWindow::frameAdded(QImage image)
{
    frameButtons[++currentFrame]->setVisible(true);

    QIcon icon;
    icon.addPixmap(QPixmap::fromImage(model.getFrame(currentFrame + 1).scaled(64,64)), QIcon::Normal);
    frameButtons[currentFrame]->setIcon(icon);
    frameButtons[currentFrame]->setIconSize(QSize(64,64));
}

void MainWindow::frameDuplicated(QImage image, int i)
{
    currentFrame = i - 1;
    frameButtons[currentFrame]->setVisible(true);

    QIcon icon;
    icon.addPixmap(QPixmap::fromImage(model.getFrame(currentFrame + 1).scaled(64,64)), QIcon::Normal);
    frameButtons[currentFrame]->setIcon(icon);
    frameButtons[currentFrame]->setIconSize(QSize(64,64));
}

/*
 * Slot for when frame is updated.
 * This will draw the frame in a mini version as an icon.
 */
void MainWindow::frameUpdated(QImage image)
{
    QIcon icon;
    icon.addPixmap(QPixmap::fromImage(model.getFrame(currentFrame + 1).scaled(64,64)), QIcon::Normal);
    frameButtons[currentFrame]->setIcon(icon);
    frameButtons[currentFrame]->setIconSize(QSize(64,64));
}

/*
 * Slot for when a frame is selected.
 * Should switch to that frame in the drawing pane.
 */
void MainWindow::frameButtonPressed()
{
    int frameIndex;

    //From Stackoverflow:
    //http://stackoverflow.com/questions/30611067/solvedqt-i-have-a-qpushbutton-qvector-which-one-was-pressed
    QObject* obj = sender();
    for(unsigned int i = 0; i < frameButtons.size(); i++)
    {
        if(obj == qobject_cast<QObject*>(frameButtons[i]))
        {
            std::cout << "Frame " << i << std::endl;
            frameIndex = i;
        }
    }

    currentFrame = frameIndex;
    emit model.changeFrame(frameIndex);
}

void MainWindow::frameRemoved(std::vector<QImage> frames)
{

    for(unsigned int i = 1; i < frames.size(); i++)
    {
        QIcon icon;
        icon.addPixmap(QPixmap::fromImage(frames[i]).scaled(64,64), QIcon::Normal);
        frameButtons[i-1]->setIcon(icon);
        frameButtons[i-1]->setIconSize(QSize(64, 64));
    }

    for(unsigned int i = frames.size() - 1; i < frameButtons.size(); i++)
    {
        frameButtons[i]->setVisible(false);
    }

    if(currentFrame == frames.size() - 1)
    {
        currentFrame--;
    }

    emit model.changeFrame(currentFrame);
}

void MainWindow::colorChanged(QColor color)
{
  QPixmap px(100, 100);
  px.fill(color);
  ui->ColorButton->setIcon(px);
  update();
}





