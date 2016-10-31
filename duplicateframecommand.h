#ifndef DUPLICATEFRAMECOMMAND_H
#define DUPLICATEFRAMECOMMAND_H
#include <QUndoCommand>
#include "model.h"

class DuplicateFrameCommand : public QUndoCommand
{
public:
    DuplicateFrameCommand(int duplicatedFrame, Model *mod, QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Model *model;
    int frameNumber;
};


#endif // DUPLICATEFRAMECOMMAND_H
