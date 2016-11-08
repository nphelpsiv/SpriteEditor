/**
 * Class designed to represent the action that a frame has been moved
 *
*/
#ifndef MOVEFRAMECOMMAND_H
#define MOVEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class MoveFrameCommand : public QUndoCommand
{
    //member variables
public:
    MoveFrameCommand(Model *mod, int moveTo, bool moveRight, QUndoCommand *parent = 0);
    //To undo adding a frame we remove the frame that was added.
    void undo() Q_DECL_OVERRIDE;
    //To undo adding a frame we remove the frame that was added.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
    int moveToPosition;
    bool moveFrameRight;
};
#endif // MOVEFRAMECOMMAND_H
