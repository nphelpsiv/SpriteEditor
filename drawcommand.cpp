#include "drawcommand.h"
#include "QPainter"

DrawCommand::DrawCommand(QImage beforeF, QImage afterF, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    model = mod;
    beforeFrame = beforeF;
    afterFrame = afterF;
    frameIndex = mod->currentFrame;
}

void DrawCommand::undo()
{
    if(frameIndex != model->currentFrame)
    {
        viewCorrectFrame();
    }

    model->frames[model->currentFrame] = beforeFrame;
    model->update();
}

//This function is called when ever an AddFrameCommand is pushed onto the QUndoStack.
void DrawCommand::redo()
{
    if(frameIndex != model->currentFrame)
    {
        viewCorrectFrame();
    }

    model->frames[model->currentFrame] = afterFrame;
    model->update();
}

void DrawCommand::viewCorrectFrame()
{
    model->currentFrame = frameIndex;
    model->changeFrame(model->currentFrame - 1);
}
