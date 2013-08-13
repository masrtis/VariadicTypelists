#pragma once

#include <memory>
#include <stack>

#include "Undo.h"

class UndoRedoStack
{
public:
    void pushUndoCommand(std::unique_ptr<UndoInterface> undoCommand);
    void pushRedoCommand(std::unique_ptr<RedoInterface> redoCommand);
    
    void undo();
    void redo();
private:
    template <typename ActionType, typename ResultType>
    void processTopCommand(std::stack<ActionType>& stackToProcess, void (UndoRedoStack::*pushCommand)(std::unique_ptr<ResultType>))
    {
        if (!stackToProcess.empty())
        {
            auto action = std::unique_ptr<ResultType>(stackToProcess.top()->execute());
            (this->*pushCommand)(std::move(action));
            stackToProcess.pop();
        }
    }

    std::stack<std::unique_ptr<UndoInterface>> m_undoStack;
    std::stack<std::unique_ptr<RedoInterface>> m_redoStack;
};
