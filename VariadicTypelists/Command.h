#pragma once

#include <memory>
#include <utility>

template <typename ReturnType, typename... Arguments>
class CommandImplementation
{
public:
    virtual ReturnType operator()(Arguments... funcArgs) = 0;
    virtual CommandImplementation* clone() const = 0;
    virtual ~CommandImplementation() { }
};

template <typename ReturnType, typename... Arguments>
class NullCommandHandler
    : public CommandImplementation<ReturnType, Arguments...>
{
public:
    virtual ReturnType operator()(Arguments...)
    {
        return ReturnType();
    }

    virtual NullCommandHandler* clone() const
    {
        return new NullCommandHandler(*this);
    }
};

template <typename Func, typename ReturnType, typename... Arguments>
class CommandHandler
    : public CommandImplementation<ReturnType, Arguments...>
{
public:
    CommandHandler(const Func& f)
        : m_func(f)
    {

    }

    virtual CommandHandler* clone() const
    {
        return new CommandHandler(*this);
    }

    virtual ReturnType operator()(Arguments... funcArgs)
    {
        return m_func(funcArgs...);
    }
private:
    Func m_func;
};

template <typename ReturnType, typename... Arguments>
class Command
{
public:
    typedef CommandImplementation<ReturnType, Arguments...> Implementation;

    Command() = default;
    ~Command() = default;
    Command(Command&&) = default;
    Command& operator=(Command&&) = default;
    Command(const Command&)
        : m_pImpl(m_pImpl->clone())
    {
        
    }
    
    Command& operator=(Command rhs)
    {
        swap(rhs);
        return *this;
    }

    explicit Command(std::unique_ptr<Implementation> pImpl)
        : m_pImpl(std::move(pImpl))
    {

    }

    template <typename Func>
    Command(const Func& fun)
        : m_pImpl(new CommandHandler<Func, ReturnType, Arguments...>(fun))
    {

    }

    Command(ReturnType(*func)(Arguments...))
        : m_pImpl(new CommandHandler<ReturnType(*)(Arguments...), ReturnType, Arguments...>(func))
    {

    }

    Command(std::nullptr_t)
        : m_pImpl(new NullCommandHandler<ReturnType, Arguments...>())
    {

    }

    ReturnType operator()(Arguments&&... funcArgs) const
    {
        return (*m_pImpl)(funcArgs...);
    }
    
    template <typename OtherReturnType, typename... OtherArguments>
    void swap(Command<OtherReturnType, OtherArguments...>& other)
    {
        m_pImpl.swap(other.m_pImpl);
    }
private:
    std::unique_ptr<Implementation> m_pImpl;
};

template <typename FirstReturnType, typename... FirstArguments, typename SecondReturnType, typename... SecondArguments>
void swap(Command<FirstReturnType, FirstArguments...>& first, Command<SecondReturnType, SecondArguments...>& second)
{
    return first.swap(second);
}
