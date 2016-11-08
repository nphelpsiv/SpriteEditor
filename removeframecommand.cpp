/*
 * Class designed to represent the action that a frame has been removed
 */

#include "removeframecommand.h"

/*
 * Constructor for RemoveFrameCommand. Similar to MoveFrame and DuplicateFrame
 */
RemoveFrameCommand::RemoveFrameCommand(int removedFrame, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    frameNumber = removedFrame;
    model = mod;
    frame = model->frames[frameNumber+1];
}

/*
 * Action for undoing a remove frame in the MainWindow
 */
void RemoveFrameCommand::undo()
{
    model->frames.insert(model->frames.begin() + frameNumber + 1, frame);
    model->currentFrame++;
    model->update();

    emit model->frameAdded(model->frames);
}

/*
 * Action for redoing an undo remove frame in the MainWindow
 */
void RemoveFrameCommand::redo()
{
    model->removeFrameButtonClicked(frameNumber);
}
