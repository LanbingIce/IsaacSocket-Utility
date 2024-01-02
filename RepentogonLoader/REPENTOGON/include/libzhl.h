#pragma once

#if defined(libzhl_EXPORTS)
#define LIBZHL_API __declspec(dllexport)
#else
#define LIBZHL_API __declspec(dllimport)
#endif

#define MOD_EXPORT extern "C" __declspec(dllexport)

#include <type_traits>
#include <variant>

template<typename T>
struct IsCallerCleanup {
	static constexpr bool value = false;
};

template<typename R, typename... Args>
struct IsCallerCleanup<R(Args...)> {
	static constexpr bool value = true;
};

template<typename R, typename... Args>
struct IsCallerCleanup<R(*)(Args...)> {
	static constexpr bool value = true;
};

/* template<typename R, typename... Args>
struct IsCallerCleanup<R __cdecl(Args...)> {
	static constexpr bool value = true;
}; */

template<typename C, typename R, typename... Args>
struct IsCallerCleanup<R(__cdecl C::*)(Args...)> {
	static constexpr bool value = true;
};

template<typename C, typename R, typename... Args>
struct IsCallerCleanup<R(__cdecl C::*)(Args...) const> {
	static constexpr bool value = true;
};

template<typename C, typename R, typename... Args>
struct IsCallerCleanup<R(__cdecl C::*)(Args...) volatile> {
	static constexpr bool value = true;
};

template<typename C, typename R, typename... Args>
struct IsCallerCleanup<R(__cdecl C::*)(Args...) volatile const> {
	static constexpr bool value = true;
};

namespace CallerCleanupCheck {
	void f(); // __cdecl by default
	void __cdecl g(); // explicitly cdecl
	void __stdcall h();
	void __fastcall i();

	struct StructCheck {
		void f(); // implicitly __thiscall
		void __stdcall g();
		void __fastcall h();
		void __cdecl i();

		void fc() const;
		void __stdcall gc() const;
		void __fastcall hc() const;
		void __cdecl ic() const;

		void fv() volatile;
		void __stdcall gv() volatile;
		void __fastcall hv() volatile;
		void __cdecl iv() volatile;

		void fcv() const volatile;
		void __stdcall gcv() const volatile;
		void __fastcall hcv() const volatile;
		void __cdecl icv() const volatile;

		static void sf();
		static void __stdcall sg();
		static void __fastcall sh();
		static void __cdecl si();
	};
}

template<typename T, typename... Args>
struct IsInPack;

template<typename T, typename U>
struct IsInPack<T, U> {
	constexpr static bool value = std::is_same_v<T, U>;
};

template<typename T, typename H, typename... Tail>
struct IsInPack<T, H, Tail...> {
	constexpr static bool value = std::is_same_v<T, H> || IsInPack<T, Tail...>::value;
};

template<typename T, typename... Types>
constexpr bool IsInPackV = IsInPack<T, Types...>::value;