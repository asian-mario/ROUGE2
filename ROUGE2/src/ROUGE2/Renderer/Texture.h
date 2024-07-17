#pragma once

#include <string>
#include "ROUGE2/Core/Core.h"
namespace ROUGE2 {
	class Texture {
	public:
		virtual ~Texture() = default;
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		
		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}