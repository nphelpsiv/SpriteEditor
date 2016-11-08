/*
 * QT-PIES SPRITE EDITOR
 *
 * Model Class:
 *
 * This class was designed to represent the action that the current frame has been drawn on
 *
 * QT-Pies:
 *      Justin Bush
 *      Mckay Fenn
 *      Alessandro Ferrero
 *      Monish Gupta
 *      Neal Phelps
 *      John Young
 */
#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DrawCommand : public QUndoCommand
{
    //member variables
public:
    //Constructor with the QImage of frame before and after drawing index and a pointer to the model.
    DrawCommand(QImage beforeF, QImage afterF, Model *mod, QUndoCommand *parent = 0);
    //To undo adding a frame we remove the frame that was added.
    void undo() Q_DECL_OVERRIDE;
    //To undo adding a frame we remove the frame that was added.
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    QImage beforeFrame;
    QImage afterFrame;
    int frameIndex;

    //View the frame that has the edits.
    void viewCorrectFrame();

};

#endif // DRAWCOMMAND_H
