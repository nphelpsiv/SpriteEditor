/**
 * Class designed to represent the action that a frame has been duplicated
 *
*/
#ifndef DUPLICATEFRAMECOMMAND_H
#define DUPLICATEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DuplicateFrameCommand : public QUndoCommand
{
    //member variables
public:
    DuplicateFrameCommand(int duplicatedFrame, Model *mod, QUndoCommand *parent = 0);
    //To undo adding a frame we remove the frame that was added.
    void undo() Q_DECL_OVERRIDE;
    //To undo adding a frame we remove the frame that was added.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
};


#endif // DUPLICATEFRAMECOMMAND_H
