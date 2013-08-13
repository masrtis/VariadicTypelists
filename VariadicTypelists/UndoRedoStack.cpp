#include "UndoRedoStack.h"

void UndoRedoStack::pushRedoCommand(std::unique_ptr<RedoInterface> redoCommand)
{
    if (!redoCommand)
    {
        m_redoStack.push(std::move(redoCommand));
    }
}

void UndoRedoStack::pushUndoCommand(std::unique_ptr<UndoInterface> undoCommand)
{
    if (!undoCommand)
    {
        m_undoStack.push(std::move(undoCommand));
    }
}

void UndoRedoStack::undo()
{
    processTopCommand(m_undoStack, &UndoRedoStack::pushRedoCommand);
}

void UndoRedoStack::redo()
{
    processTopCommand(m_redoStack, &UndoRedoStack::pushUndoCommand);
}
