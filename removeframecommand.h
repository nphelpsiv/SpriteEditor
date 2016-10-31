#ifndef REMOVEFRAMECOMMAND_H
#define REMOVEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"


class RemoveFrameCommand : public QUndoCommand
{
public:
    RemoveFrameCommand(int removedFrame, Model *mod, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
    QImage frame;
};

#endif // REMOVEFRAMECOMMAND_H
