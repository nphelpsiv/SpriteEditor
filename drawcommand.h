/**
 * Class designed to represent the action that the current frame has been drawn on
 *
*/
#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DrawCommand : public QUndoCommand
{
    //member variables
public:
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

    void viewCorrectFrame();

};

#endif // DRAWCOMMAND_H
