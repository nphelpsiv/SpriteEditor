#include "addframecommand.h"

AddFrameCommand::AddFrameCommand(int addedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = addedFrame;
    model = mod;
}
//To undo adding a frame we remove the frame that was added.
void AddFrameCommand::undo()
{
    model->removeFrameButtonClicked(frameNumber+1);
}
//This function is called when ever an Item is pushed onto the QUndoStack.
void AddFrameCommand::redo()
{
    model->addFrame();
}
