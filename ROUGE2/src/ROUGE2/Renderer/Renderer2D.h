#pragma once
#include "OrthoCamera.h"
#include "Texture.h"

namespace ROUGE2 {
	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		//primitive functions
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color); //z defaults to 0
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color); // 'layer'
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, bool linear, const glm::vec4& tintCol = glm::vec4(1.0f), float tileScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, bool linear, const glm::vec4& tintCol = glm::vec4(1.0f), float tileScale = 1.0f);

		static void DrawRotQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color); 
		static void DrawRotQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color); 
		static void DrawRotQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, bool linear, const glm::vec4& tintCol = glm::vec4(1.0f), float tileScale = 1.0f);
		static void DrawRotQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, bool linear, const glm::vec4& tintCol = glm::vec4(1.0f), float tileScale = 1.0f);


	};
}