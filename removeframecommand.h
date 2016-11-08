/**
 * Class designed to represent the action that a frame has been removed
 *
*/
#ifndef REMOVEFRAMECOMMAND_H
#define REMOVEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"


class RemoveFrameCommand : public QUndoCommand
{
    //Member variables
public:
    RemoveFrameCommand(int removedFrame, Model *mod, QUndoCommand *parent = 0);
    //To undo adding a frame we remove the frame that was added.
    void undo() Q_DECL_OVERRIDE;
    //To undo adding a frame we remove the frame that was added.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
    QImage frame;
};

#endif // REMOVEFRAMECOMMAND_H
