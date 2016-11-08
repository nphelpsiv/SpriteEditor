/*
 * Class designed to represent the action that a frame has been moved
 */

#include "moveframecommand.h"

/*
 * Constructor making a MoveFrameCommand. Similar to the duplicateFrame
 */
MoveFrameCommand::MoveFrameCommand(Model *mod, int moveTo, bool moveRight, QUndoCommand *parent) : QUndoCommand(parent)
{
    model = mod;
    frameNumber = mod->currentFrame;
    moveToPosition = moveTo;
    moveFrameRight = moveRight;
}

/*
 * Undo action for moving a frame.
 */
void MoveFrameCommand::undo()
{
    model->changeFrame(moveToPosition);
    if(moveFrameRight)
        model->moveFrameButtonClicked(moveToPosition-1);
    else
        model->moveFrameButtonClicked(moveToPosition+1);
}

/*
 * Redo action for moving a frame
 */
void MoveFrameCommand::redo()
{
    model->changeFrame(frameNumber - 1);
    model->moveFrameButtonClicked(moveToPosition);
}
