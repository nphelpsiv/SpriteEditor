#include "duplicateframecommand.h"

DuplicateFrameCommand::DuplicateFrameCommand(int duplicatedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = duplicatedFrame;
    model = mod;
}

void DuplicateFrameCommand::undo()
{
    model->removeFrameButtonClicked(frameNumber);
}

void DuplicateFrameCommand::redo()
{
    model->duplicateFrameButtonClicked(frameNumber);
}
