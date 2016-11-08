/*
 * Class designed to represent the action that a frame has been added
 *
 */

#include "addframecommand.h"

/*
 * Constructor with the added frames index and a pointer to the model.
 */
AddFrameCommand::AddFrameCommand(int addedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = addedFrame;
    model = mod;
}

/*
 * Undo command for Removing a Frame
 */
void AddFrameCommand::undo()
{
    model->removeFrameButtonClicked(frameNumber+1);
}

/*
 * Redo command for Removing a Frame
 */
void AddFrameCommand::redo()
{
    model->addFrame();
}
