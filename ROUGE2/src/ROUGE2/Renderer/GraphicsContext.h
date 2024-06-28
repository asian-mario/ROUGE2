#pragma once

namespace ROUGE2 {

	class GraphicsContext{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}