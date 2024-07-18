#include "r2pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace ROUGE2 {
	Scope<RenderCommand> RenderCommand::s_RendererAPI = new OpenGLRendererAPI; // will be created dynamically later
}