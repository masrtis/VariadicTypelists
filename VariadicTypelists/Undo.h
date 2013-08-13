#pragma once

#include <tuple>
#include <functional>
#include "TypeList.h"

namespace detail
{
    template <int...>
    struct ParameterIndexSequence
    {
    
    };
    
    template <int currentParamIndex, int... remainingIndices>
    struct ConstructParameterIndexSequence : public ConstructParameterIndexSequence<currentParamIndex - 1,
                                                                  currentParamIndex - 1,
                                                                  remainingIndices...>
    {
    
    };
    
    template <int... remainingIndices>
    struct ConstructParameterIndexSequence<0, remainingIndices...>
    {
        typedef ParameterIndexSequence<remainingIndices...> type;
    };
}

class RedoInterface;
class UndoInterface;

class UndoInterface
{
public:
    virtual std::unique_ptr<RedoInterface> execute() const = 0;
    virtual ~UndoInterface() { }
};

class RedoInterface
{
public:
    virtual std::unique_ptr<UndoInterface> execute() const = 0;
    virtual ~RedoInterface() { }
};

template <typename Base, typename Result, typename... Parameters>
class UndoRedoCommand : public Base
{
public:
    template <typename Func>
    explicit UndoRedoCommand(Func&& func, 
                             Parameters... parameters)
        : m_func(std::forward<Func>(func))
        , m_parameters(std::make_tuple(std::move(parameters)...))
    {
        
    }
    
    virtual std::unique_ptr<Result> execute() const
    {
        return callFunc(typename detail::ConstructParameterIndexSequence<sizeof...(Parameters)>::type());
    }
private:
    template <int... numParams>
    std::unique_ptr<Result> callFunc(detail::ParameterIndexSequence<numParams...>) const
    {
        return m_func(std::get<numParams>(m_parameters)...);
    }

    std::function<std::unique_ptr<Result>(Parameters...)> m_func;
    std::tuple<Parameters...>                             m_parameters;
};

template <typename... UndoParameters>
using UndoCommand = UndoRedoCommand<UndoInterface, RedoInterface, UndoParameters...>;

template <typename... RedoParameters>
using RedoCommand = UndoRedoCommand<RedoInterface, UndoInterface, RedoParameters...>;

template <typename Func, typename... Parameters>
std::unique_ptr<UndoInterface> makeUndoCommand(Func&& func,
                                               Parameters... parameters)
{
    return std::unique_ptr<UndoInterface>(new UndoCommand<Parameters...>(std::forward<Func>(func), 
                                                                         std::move(parameters)...));
}

template <typename Func, typename... Parameters>
std::unique_ptr<RedoInterface> makeRedoCommands(Func&& func,
                                                Parameters... parameters)
{    
    return std::unique_ptr<RedoInterface>(new RedoCommand<Parameters...>(std::forward<Func>(func),
                                                                         std::move(parameters)...));
}
