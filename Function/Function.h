#pragma once
#include <type_traits>
#include <memory>

template <typename Ret, typename... Args>
class _FuncInterface
	{
	public:
		virtual Ret Call(Args&&... args) = 0;
		virtual ~_FuncInterface() = default;
	};

template<typename Callable, typename Ret, typename... Args>
class _FuncBase : public _FuncInterface<Ret, Args...>
	{
	private:
		std::decay_t<Callable> m_call;

	public:
		_FuncBase(Callable&& call) : m_call(std::forward<Callable>(call))
			{}

		Ret Call(Args&&... args) override
			{
			return std::invoke(m_call, std::forward<Args>(args)...);
			}
	};

template<typename T>
class _FunctionBase;

template <typename Ret, typename... Args>
class _FunctionBase<Ret (Args...)>
	{
	private:
		std::unique_ptr<_FuncInterface<Ret, Args...>> m_func;

	public:
		template<typename Callable>
		_FunctionBase(Callable&& call) : m_func(new _FuncBase<Callable, Ret, Args...>(std::forward<Callable>(call)))
			{}

		auto operator()(Args&&... args) const
			{
			return m_func->Call(std::forward<Args>(args)...);
			}
	};


template<typename Func>
class Function : public _FunctionBase<Func>
	{
	public:
		template<typename Callable>
		Function(Callable&& call) : _FunctionBase<Func>(std::forward<Callable>(call))
			{}
	};