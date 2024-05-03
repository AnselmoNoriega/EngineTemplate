#include "pch.h"
#include "UniformBuffer.h"

#include "NotVoxel/Renderer/RendererAPI.h"
#include "NotVoxel/Renderer/Renderer.h"

#include "Platform/RendererAPI/OpenGL/GLUniformBuffer.h"

namespace VoxelForge
{

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<GLUniformBuffer>(size, binding);
		default:
		{
			CORE_ASSERT(false, "Unknown RendererAPI!"); 
			return nullptr;
		}
		}

	}

}