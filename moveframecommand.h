#ifndef MOVEFRAMECOMMAND_H
#define MOVEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class MoveFrameCommand : public QUndoCommand
{
public:
    MoveFrameCommand(Model *mod, int moveTo, bool moveRight, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
    int moveToPosition;
    bool moveFrameRight;
};
#endif // MOVEFRAMECOMMAND_H
