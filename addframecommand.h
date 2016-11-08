/**
 * Class designed to represent the action that a frame has been added
 *
*/
#ifndef ADDFRAMECOMMAND_H
#define ADDFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class AddFrameCommand : public QUndoCommand
{
//member variables
public:
    //Constructor with the added frames index and a pointer to the model.
    AddFrameCommand(int addedFrame, Model *mod, QUndoCommand *parent = 0);
    //To undo adding a frame we remove the frame that was added.
    void undo() Q_DECL_OVERRIDE;
    //To undo adding a frame we remove the frame that was added.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
};

#endif // ADDFRAMECOMMAND_H
