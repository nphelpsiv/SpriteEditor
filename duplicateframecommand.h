/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * This class was designed to represent the action that a frame has been duplicated
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef DUPLICATEFRAMECOMMAND_H
#define DUPLICATEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DuplicateFrameCommand : public QUndoCommand
{
    //member variables
public:
    //Constructor with the index of the duplicated frame and a pointer to the model.
    DuplicateFrameCommand(int duplicatedFrame, Model *mod, QUndoCommand *parent = 0);
    //To undo adding a frame we remove the frame that was added.

    //Remove the frame that was duplicated.
    void undo() Q_DECL_OVERRIDE;
    //This function is called when ever an DuplicateFrameCommand is pushed onto the QUndoStack.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
};


#endif // DUPLICATEFRAMECOMMAND_H
