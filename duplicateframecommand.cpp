/*
 * Class designed to represent the action that a frame has been duplicated
 */

#include "duplicateframecommand.h"

/*
 * Constructor with the index of the duplicated frame and a pointer to the model.
 */
DuplicateFrameCommand::DuplicateFrameCommand(int duplicatedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = duplicatedFrame;
    model = mod;
}

/*
 * Remove the frame that was duplicated
 */
void DuplicateFrameCommand::undo()
{
    model->removeFrameButtonClicked(frameNumber);
}

/*
 * This function is called when ever an DuplicateFrameCommand is pushed onto the QUndoStack.
 * Redo the frame that duplicated
 */
void DuplicateFrameCommand::redo()
{
    model->duplicateFrameButtonClicked(frameNumber);
}
