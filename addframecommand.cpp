#include "addframecommand.h"

AddFrameCommand::AddFrameCommand(int addedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = addedFrame;
    model = mod;
}
void AddFrameCommand::undo()
{
    model->removeFrameButtonClicked(frameNumber+1);
}
void AddFrameCommand::redo()
{
    model->addFrame();
}
