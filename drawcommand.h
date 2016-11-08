#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DrawCommand : public QUndoCommand
{
public:
    //Constructor with the QImage of frame before and after drawing index and a pointer to the model.
    DrawCommand(QImage beforeF, QImage afterF, Model *mod, QUndoCommand *parent = 0);

    //Undo drawing by restoring the before frame.
    void undo() Q_DECL_OVERRIDE;
    //This function is called when ever an DrawCommand is pushed onto the QUndoStack.
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
