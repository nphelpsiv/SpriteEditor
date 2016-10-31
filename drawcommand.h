#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DrawCommand : public QUndoCommand
{
public:
    DrawCommand(QImage beforeF, QImage afterF, Model *mod, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    QImage beforeFrame;
    QImage afterFrame;
    int frameIndex;
};

#endif // DRAWCOMMAND_H
