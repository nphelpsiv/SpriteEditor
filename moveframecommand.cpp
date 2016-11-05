#include "moveframecommand.h"

MoveFrameCommand::MoveFrameCommand(Model *mod, int moveTo, bool moveRight, QUndoCommand *parent) : QUndoCommand(parent)
{
    model = mod;
    frameNumber = mod->currentFrame;
    moveToPosition = moveTo;
    moveFrameRight = moveRight;
}

void MoveFrameCommand::undo()
{
    if(moveFrameRight)
        model->moveFrameButtonClicked(moveToPosition-1);
    else
        model->moveFrameButtonClicked(moveToPosition+1);
}

void MoveFrameCommand::redo()
{
    model->moveFrameButtonClicked(moveToPosition);
}
