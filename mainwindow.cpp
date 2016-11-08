#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <algorithm>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initialize our Undostack
    undoStack = new QUndoStack(this);
    //Create undo and redo actions.
    createActions();

    canvasLayout = new QGridLayout(ui->Canvas);
    canvasLayout->setMargin(0);
    canvasLayout->addWidget(&model, 0, 0);


    //Timer for the preview window.
    connect(&timer, SIGNAL(timeout()),
            this, SLOT(previewUpdate()));
    connect(&preview, SIGNAL(renableButton()),
            this, SLOT(renablePreview()));

    //Connects for signals when frame is changed.
    connect(&model, SIGNAL(frameAdded(std::vector<QImage>)),
            this, SLOT(frameAdded(std::vector<QImage>)));

    connect(&model, SIGNAL(updated(QImage, int)),
            this, SLOT(frameUpdated(QImage, int)));

    connect(&model, SIGNAL(frameRemoved(std::vector<QImage>)),
            this, SLOT(frameRemoved(std::vector<QImage>)));

    connect(&model, SIGNAL(colorChanged(QColor)),
            this, SLOT(colorChanged(QColor)));

    connect(&exportWindow, SIGNAL(exportSelected(int, std::string, int)),
            &model, SLOT(exportSelected(int, std::string, int)));

    connect(&newProject, SIGNAL(newSelected(int)),
            this, SLOT(newProjectSelected(int)));

    connect(&model, SIGNAL(framesSaved(QImage, QImage)),
            this, SLOT(framesSaved(QImage, QImage)));

    connect(&model, SIGNAL(framesMoved(std::vector<QImage>,int)),
            this, SLOT(frameMoved(std::vector<QImage>,int)));

    connect(&model, SIGNAL(changeAlphaSlider(int)),
            this, SLOT(changeAlphaSlider(int)));

    //Connection from saveonclose to close or save the Main Sprite
    connect(&saveCloseDialog, SIGNAL(closeMainSprite()),
            this, SLOT(closeMainSpriteSelected()));
    connect(&saveCloseDialog, SIGNAL(saveMainSprite()),
            this, SLOT(saveAndClose()));
    connect(&model, SIGNAL(closeMainSprite()),
            this, SLOT(closeMainSpriteSelected()));
    connect(&saveCloseDialog, SIGNAL(openNewSprite()),
            this, SLOT(openFileSelected()));
    connect(&saveCloseDialog, SIGNAL(saveThenOpenSprite()),
            this, SLOT(saveThenOpenSpriteSelected()));
    connect(&saveCloseDialog, SIGNAL(startNewNoSave()),
            this, SLOT(newNoSave()));
    connect(&saveCloseDialog, SIGNAL(startNewWithSave()),
            this, SLOT(newWithSave()));
    connect(&model, SIGNAL(startNewSprite()),
            this, SLOT(newNoSave()));
    connect(&model, SIGNAL(successfulSave()),
            this, SLOT(successfullySaved()));


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
    for(int i = 0; i < 60; i++)
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

        connect(frame, SIGNAL(pressed()),
                this, SLOT(frameButtonPressed()));
    }

    //Show first frame upon start.
    frameButtons[0]->setVisible(true);
    currentFrame = 0;

    layout->addWidget(w);
    layout->addWidget(w1);

    FPS = ui->FPSSpinBox->value();

    // Set the intial alpha value to 255
    //ui->AlphaLabelValue->setText(QString("255"));
    //ui->AlphaSlider->setValue(255);


    on_PenButton_clicked();

    unsavedChanges = false;

    // set up help menu
    //ui->menuHelp->addAction("Help");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PenButton_clicked()
{
    emit model.penButtonClicked();
    ui->PenButton->setChecked(true);
    ui->EraserButton->setChecked(false);
    ui->RectButton->setChecked(false);
    ui->LineButton->setChecked(false);
    ui->EllipseButton->setChecked(false);
    ui->BucketButton->setChecked(false);
    ui->ColorCasterButton->setChecked(false);
    ui->ColorPickerButton->setChecked(false);
}

void MainWindow::on_EraserButton_clicked()
{
    emit model.eraserButtonClicked();
    uncheckAllToolButtons();
    ui->EraserButton->setChecked(true);
}

void MainWindow::on_RectButton_clicked()
{
    emit model.rectButtonClicked();
    uncheckAllToolButtons();
    ui->RectButton->setChecked(true);
}

void MainWindow::on_LineButton_clicked()
{
    emit model.lineButtonClicked();
    uncheckAllToolButtons();
    ui->LineButton->setChecked(true);
}

void MainWindow::on_EllipseButton_clicked()
{
    emit model.ellipseButtonClicked();
    uncheckAllToolButtons();
    ui->EllipseButton->setChecked(true);
}

void MainWindow::on_BucketButton_clicked()
{
    emit model.bucketButtonClicked();
    uncheckAllToolButtons();
    ui->BucketButton->setChecked(true);
}

void MainWindow::on_ColorCasterButton_clicked()
{
    emit model.colorCasterButtonClicked();
    uncheckAllToolButtons();
    ui->ColorCasterButton->setChecked(true);
}

void MainWindow::on_ColorPickerButton_clicked()
{
    emit model.colorPickerButtonClicked();
    uncheckAllToolButtons();
    ui->ColorPickerButton->setChecked(true);
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
    if(checked)
        on_PenButton_clicked();
}

void MainWindow::on_MirrorVerticalButton_toggled(bool checked)
{
    emit model.mirrorVerticalButtonToggled(checked);
    if(checked)
        on_PenButton_clicked();
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

void MainWindow::changeAlphaSlider(int sliderValue)
{
  ui->AlphaSlider->setValue(sliderValue);
}

/*
 * Slot for when frame is added.
 * Recieves a vector of QImages from Model to update all the frames.
 */
void MainWindow::frameAdded(vector<QImage> frames)
{
    for(unsigned int i = 1; i < frames.size(); i++)
    {
        QIcon icon;
        icon.addPixmap(QPixmap::fromImage(frames[i]).scaled(64,64), QIcon::Normal);
        frameButtons[i-1]->setIcon(icon);
        frameButtons[i-1]->setIconSize(QSize(64, 64));
        frameButtons[i-1]->setVisible(true);
    }

    currentFrame++;

    //This is used to send a signal when the geometry of the scroll area has changed.
    //This way the scroll bar can correctly move to that position.
    QScrollBar *bar = ui->FramesViewArea->horizontalScrollBar();
    QObject::connect(bar, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToSelected(int,int)));

    emit model.changeFrame(currentFrame);
}

void MainWindow::moveScrollBarToSelected(int min, int max)
{
    ui->FramesViewArea->ensureWidgetVisible(frameButtons[currentFrame], 300);
}

/*
 * Slot for when frame is updated.
 * This will draw the frame in a mini version as an icon.
 */
void MainWindow::frameUpdated(QImage image, int newIndex)
{
    currentFrame = newIndex - 1;
    QIcon icon;
    icon.addPixmap(QPixmap::fromImage(image.scaled(64,64)), QIcon::Normal);
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
    //Need to update all buttons with the full vector of frames.
    for(unsigned int i = 1; i < frames.size(); i++)
    {
        QIcon icon;
        icon.addPixmap(QPixmap::fromImage(frames[i]).scaled(64,64), QIcon::Normal);
        frameButtons[i-1]->setIcon(icon);
        frameButtons[i-1]->setIconSize(QSize(64, 64));
    }

    //Set any remaining, "removed" frames to be non-visible
    for(unsigned int i = frames.size() - 1; i < frameButtons.size(); i++)
    {
        frameButtons[i]->setVisible(false);
    }

    //decrement currentFrame if it was the last frame that was removed.
    if(currentFrame == frames.size() - 1)
    {
        currentFrame--;
    }

    emit model.changeFrame(currentFrame);
}

void MainWindow::frameMoved(std::vector<QImage> frames, int index)
{
   for(unsigned int i = 1; i < frames.size(); i++)
   {
       QIcon icon;
       icon.addPixmap(QPixmap::fromImage(frames[i]).scaled(64,64), QIcon::Normal);
       frameButtons[i-1]->setIcon(icon);
       frameButtons[i-1]->setIconSize(QSize(64, 64));
   }

   currentFrame = index - 1;

   ui->FramesViewArea->ensureWidgetVisible(frameButtons[currentFrame], 300);
   emit model.changeFrame(currentFrame);
}

void MainWindow::colorChanged(QColor color)
{
  QPixmap px(100, 100);
  px.fill(color);
  ui->ColorButton->setIcon(px);
  update();
}

void MainWindow::framesSaved(QImage oldFrame, QImage newFrame)
{
    QUndoCommand *drawCommand = new DrawCommand(oldFrame, newFrame, &model);
    undoStack->push(drawCommand);
}

//Setting up Actions
void MainWindow::createActions()
{

    //Setting up our undoAction to connnect to our undoStack.
    undoAction = undoStack->createUndoAction(this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setIcon(QIcon(":undo.png"));

    ui->UndoButton->setDefaultAction(undoAction);

    //Setting up our redoAction to connnect to our undoStack.
    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setIcon(QIcon(":redo.png"));

    ui->RedoButton->setDefaultAction(redoAction);

    connect(undoStack, SIGNAL(indexChanged(int)),
            this, SLOT(changesMade()));
    connect(redoAction, SIGNAL(indexChanged(int)),
            this, SLOT(changesMade()));

    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionClose->setShortcut(QKeySequence::Close);
    //connect(ui->actionClose, SIGNAL(triggered(bool)), this, SLOT(close()));
    // I have it closing a different way


}

void MainWindow::uncheckAllToolButtons()
{
    ui->PenButton->setChecked(false);
    ui->EraserButton->setChecked(false);
    ui->RectButton->setChecked(false);
    ui->LineButton->setChecked(false);
    ui->EllipseButton->setChecked(false);
    ui->BucketButton->setChecked(false);
    ui->ColorCasterButton->setChecked(false);
    ui->ColorPickerButton->setChecked(false);
    ui->MirrorHorizontalButton->setChecked(false);
    ui->MirrorVerticalButton->setChecked(false);
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
    //QPushButton button = frameButtons[frameButtons.size() -1];
    //button.
    if(frameButtons[frameButtons.size() -1 ]->isVisible())
    {
        QMessageBox msgBox;
        msgBox.setText("You have reached the maximum amount of frames allowed.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }

    /*
     * Create a command object that contains saved information about the current frame.
     * Also a pointer to the model is passed in as well so it's delete frame
    */
    QUndoCommand *addFrameCommand = new AddFrameCommand(currentFrame, &model);
    //Note* pushing onto the QUndoStack will automatically send a call to the redo function of the QUndoCommand.
    undoStack->push(addFrameCommand);
}

void MainWindow::on_DuplicateFrameButton_clicked()
{
    //User should not be able to add more the defined size (May change that so it is infite later)
    //Should consider creating a dialog box to let user know they have reached their limit.
    if(frameButtons[frameButtons.size() -1 ]->isVisible())
    {
        QMessageBox msgBox;
        msgBox.setText("You have reached the maximum amount of frames allowed.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    QUndoCommand *duplicateFrameCommand = new DuplicateFrameCommand(currentFrame, &model);
    undoStack->push(duplicateFrameCommand);
}

void MainWindow::on_RemoveFrameButton_clicked()
{
    //Don't delete if there is only one frame.
    if(model.frames.size() == 2)
        return;

    QUndoCommand *removeFrameCommand = new RemoveFrameCommand(currentFrame, &model);
    undoStack->push(removeFrameCommand);
}

void MainWindow::getDrawingSize(int size)
{
    exportWindow.setActualSize(size);
    emit model.setUp(size);
}

void MainWindow::newProjectSelected(int size)
{
    std::cout << "size: " << size << std::endl;
    emit model.newButtonClicked(size);
    undoStack->clear();
}

/**
 * Have the saveCloseDialog choose what to do when trying to open a new Sprite
 * @brief MainWindow::on_actionNew_triggered
 */
void MainWindow::on_actionNew_triggered()
{
    // first check to see if the sprite has been modified since the last save
    if(unsavedChanges)
        saveCloseDialog.showFromNew();
    else
        newNoSave();
}

/**
 * Start a New Sprite
 * @brief MainWindow::newNoSave
 */
void MainWindow::newNoSave()
{
    newProject.show();
}

/**
 * Send to the model that it needs saved.
 * This model method is slighlty different in that it will call back
 * to the mainwindow to show the newProjcect window after it has been saved.
 * @brief MainWindow::newWithSave
 */
void MainWindow::newWithSave()
{
    QFileDialog save;
    QString fileName = save.getSaveFileName(this,
       tr("Save Sprite"), "~/", tr("Sprite Files (*.ssp)"));
    if (save.AcceptSave == 1 && !fileName.isNull())
    {
       emit model.saveThenNewButtonClicked(fileName.toStdString());
    }
    else
    {
       QMessageBox msgBox;
       msgBox.setText("Couldn't save. The document needs a name.");
       msgBox.exec();
    }
}

void MainWindow::successfullySaved()
{
    unsavedChanges = false;
}

void MainWindow::on_actionSave_triggered()
{
    QFileDialog save;
       QString fileName = save.getSaveFileName(this,
           tr("Save Sprite"), "~/", tr("Sprite Files (*.ssp)"));
       if (save.AcceptSave == 1 && !fileName.isNull())
       {
           if(!fileName.endsWith(".ssp"))
           {
               fileName += ".ssp";
           }
           emit model.saveButtonClicked(fileName.toStdString());
       }
       else
       {
           QMessageBox msgBox;
           msgBox.setText("Couldn't save. The document needs a name.");
           msgBox.exec();
       }
}

void MainWindow::saveThenOpenSpriteSelected()
{
    on_actionSave_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
    if(unsavedChanges)
        saveCloseDialog.showFromOpen();
    else
        openFileSelected();
}

void MainWindow::openFileSelected()
{
    QFileDialog open;
    QString fileName = open.getOpenFileName(this,
       tr("Open Sprite"), "~/", tr("Sprite Files (*.ssp)"));

       if (!fileName.isNull())
       {
           emit model.openButtonClicked(fileName.toStdString());
           undoStack->clear();
       }
}

void MainWindow::loadButtonClicked()
{
    QFileDialog open;
    QString fileName = open.getOpenFileName(this,
       tr("Open Sprite"), "~/", tr("Sprite Files (*.ssp)"));

       if (!fileName.isNull())
       {

           emit model.openButtonClicked(fileName.toStdString());
           undoStack->clear();
           this->showNormal();
           this->activateWindow();
           this->raise();
           this->show();
       }
       //means user hit cancel
       else
       {
           /*QProcess process;
           process.startDetached("SpriteEditor" ,QStringList());
           qApp->quit();*/
           emit canceld();

       }

}

void MainWindow::on_AlphaSlider_valueChanged(int value)
{
    //ui->AlphaLabelValue->setText(QString::number(value));
    emit model.alphaValueChanged(value);
}

void MainWindow::on_moveFrameLeftButton_clicked()
{
    if(currentFrame == 0)
        return;

    QUndoCommand *moveFrameCommand = new MoveFrameCommand(&model, currentFrame - 1, false);
    undoStack->push(moveFrameCommand);
}

void MainWindow::on_moveFrameRightButton_clicked()
{
    if(!frameButtons[currentFrame + 1]->isVisible())
        return;

    QUndoCommand *moveFrameCommand = new MoveFrameCommand(&model, currentFrame + 1, true);
    undoStack->push(moveFrameCommand);
}

void MainWindow::on_clearFrameButton_clicked()
{
    emit model.clearFrameButtonClicked(currentFrame);
}

/**
 * When trying to close let the SaveCloseDialog determince which actions need to happen.
 * @brief MainWindow::on_actionClose_triggered
 */
void MainWindow::on_actionClose_triggered()
{
    // If the sprite has been changed since the last save, ask if they want to save before closing.
    if(unsavedChanges)
    {
        saveCloseDialog.showFromClose();
    }
    else
    {
        // If it hasn't been saved, at least ask if they're sure they want to close
        QMessageBox msgBox;
        msgBox.setText("Are you sure you want to close?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();


        switch (ret) {
            case QMessageBox::Yes:
                msgBox.close();
                this->close();
                QApplication::quit();
                break;
            case QMessageBox::No:
                msgBox.close();
                break;
            default:
                // should never be reached
                break;
        }
    }
}


/**
 * Close this application
 * @brief MainWindow::closeMainSpriteSelected
 */
void MainWindow::closeMainSpriteSelected()
{
    this->close();
    QApplication::quit();
}


/**
 * Send to the model that it needs saved.
 * This model method is slighlty different in that it will
 * close the application after it's saved.
 * @brief MainWindow::newWithSave
 */
void MainWindow::saveAndClose()
{
    QFileDialog save;
    QString fileName = save.getSaveFileName(this,
       tr("Save Sprite"), "~/", tr("Sprite Files (*.ssp)"));
    if (save.AcceptSave == 1)
    {
       emit model.saveAndCloseButtonClicked(fileName.toStdString());
    }
    else
    {
       QMessageBox msgBox;
       msgBox.setText("Couldn't Save. The document needs a name.");
       msgBox.exec();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // for some reason this is closing very first, it's not acting like it's just a boolean
    if(event->isAccepted())
    {
        event->ignore();
        on_actionClose_triggered();
    }
    //on_actionClose_triggered();
}

void MainWindow::changesMade()
{
    unsavedChanges = true;
}

void MainWindow::on_actionHelp_triggered()
{
    //QFile HelpFile("qrc:SpriteEditorDocumentation.pdf");
    //HelpFile.copy(qApp->applicationDirPath().append(":SpriteEditorDocumentation.pdf"));

    // This is only going to a specific url
    // I think I got the actual pdf into the resources folder
    // But I can't quite get it to open a relative path
    QDesktopServices::openUrl(QUrl("https://docs.google.com/document/d/1W037-r2LDfaEfAxG1syYZ-I2qRfPx6KfBfls0xHNe5c/edit", QUrl::TolerantMode));

    // How it should be with a relative path
        // QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath().append("/myFile.pdf")));
    // But QDir::currentPath() is the build/debug folder.
    // It's easy to go up a folder with QDir::cdUp()
    // but then I don't know how to go into the next one if it'll always be a different name
}
