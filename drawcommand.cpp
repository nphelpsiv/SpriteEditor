/*
 * Class designed to represent the action that the current frame has been drawn on
 *
 */

#include "drawcommand.h"
#include "QPainter"

/*
 * Constructor with the QImage of frame before and after drawing index and a pointer to the model.
 */
DrawCommand::DrawCommand(QImage beforeF, QImage afterF, Model *mod, QUndoCommand *parent) : QUndoCommand(parent)
{
    model = mod;
    beforeFrame = beforeF;
    afterFrame = afterF;
    frameIndex = mod->currentFrame;
}

/*
 * Undo the last drawing to the Sprite
 */
void DrawCommand::undo()
{
    if(frameIndex != model->currentFrame)
    {
        viewCorrectFrame();
    }

    model->frames[model->currentFrame] = beforeFrame;
    model->update();
}

/*
 * This function is called when ever an AddFrameCommand is pushed onto the QUndoStack.
 */
void DrawCommand::redo()
{
    if(frameIndex != model->currentFrame)
    {
        viewCorrectFrame();
    }

    model->frames[model->currentFrame] = afterFrame;
    model->update();
}

/*
 * View the frame that has the edits
 */
void DrawCommand::viewCorrectFrame()
{
    model->currentFrame = frameIndex;
    model->changeFrame(model->currentFrame - 1);
}
