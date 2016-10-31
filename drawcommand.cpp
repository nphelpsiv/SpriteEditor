#include "drawcommand.h"

DrawCommand::DrawCommand(QImage beforeF, QImage afterF, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    model = mod;
    beforeFrame = beforeF;
    afterFrame = afterF;
    frameIndex = mod->currentFrame;
}

void DrawCommand::undo()
{

    model->frames[model->currentFrame] = beforeFrame;
    model->update();
}

void DrawCommand::redo()
{

    model->frames[model->currentFrame] = afterFrame;
    model->update();
}
