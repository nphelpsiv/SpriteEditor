#include "removeframecommand.h"

RemoveFrameCommand::RemoveFrameCommand(int removedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = removedFrame;
    model = mod;
    frame = model->frames[frameNumber+1];
}

void RemoveFrameCommand::undo()
{
    model->frames.insert(model->frames.begin() + frameNumber + 1, frame);
    model->currentFrame++;
    model->update();

    emit model->frameAdded(model->frames);
}

void RemoveFrameCommand::redo()
{
    model->removeFrameButtonClicked(frameNumber);
}
