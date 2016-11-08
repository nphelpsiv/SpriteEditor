#ifndef DUPLICATEFRAMECOMMAND_H
#define DUPLICATEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DuplicateFrameCommand : public QUndoCommand
{
public:
    //Constructor with the index of the duplicated frame and a pointer to the model.
    DuplicateFrameCommand(int duplicatedFrame, Model *mod, QUndoCommand *parent = 0);

    //Remove the frame that was duplicated.
    void undo() Q_DECL_OVERRIDE;
    //This function is called when ever an DuplicateFrameCommand is pushed onto the QUndoStack.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
};


#endif // DUPLICATEFRAMECOMMAND_H
