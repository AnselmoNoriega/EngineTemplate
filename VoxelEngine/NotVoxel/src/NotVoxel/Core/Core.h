#pragma once

#include  <memory>

#include "PlatformDetection.h"

#include "NotVoxel/Core/Log.h"

#ifdef VOXEL_DEBUG
#if defined(VOXEL_PLATFORM_WINDOWS)
#define DEBUGBREAK() __debugbreak()
#elif defined(VOXEL_PLATFORM_LINUX)
#include <signal.h>
#define DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define VOXEL_ENABLE_ASSERTS
#else
#define DEBUGBREAK()
#endif

#ifdef VOXEL_ENABLE_ASSERTS
#define ASSERT(x, ...) { if(!(x)) { NR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CORE_ASSERT(x, ...) { if(!(x)) { NR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
#define ASSERT(x, ...)
#define CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(fn) [this](auto&&... args)-> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace NR
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}