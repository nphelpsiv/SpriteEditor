/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * This class was designed to represent the action that a frame has been removed
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef REMOVEFRAMECOMMAND_H
#define REMOVEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"


class RemoveFrameCommand : public QUndoCommand
{
    //Member variables
public:
    //Constructor with the removed frames index and a pointer to the model.
    RemoveFrameCommand(int removedFrame, Model *mod, QUndoCommand *parent = 0);

    //Redo a moved frame by adding a frame to the removed frames location.
    void undo() Q_DECL_OVERRIDE;
    //This function is called when ever an RemoveFrameCommand is pushed onto the QUndoStack.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
    QImage frame;
};

#endif // REMOVEFRAMECOMMAND_H
