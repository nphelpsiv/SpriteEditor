#ifndef ADDFRAMECOMMAND_H
#define ADDFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"


class AddFrameCommand : public QUndoCommand
{
public:
    AddFrameCommand(int addedFrame, Model *mod, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
};

#endif // ADDFRAMECOMMAND_H
