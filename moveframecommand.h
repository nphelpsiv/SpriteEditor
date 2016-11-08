/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * This class was designed to represent the action that a frame has been moved
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef MOVEFRAMECOMMAND_H
#define MOVEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class MoveFrameCommand : public QUndoCommand
{
    //member variables
public:
    //Constructor with a pointer to model, the index to the frame move to and a boolean to to say if your going right or left.
    MoveFrameCommand(Model *mod, int moveTo, bool moveRight, QUndoCommand *parent = 0);

    //Undo drawing by restoring the before frame.
    void undo() Q_DECL_OVERRIDE;
    //This function is called when ever an MoveFrameCommand is pushed onto the QUndoStack.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
    int moveToPosition;
    bool moveFrameRight;
};
#endif // MOVEFRAMECOMMAND_H
