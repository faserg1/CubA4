#pragma once

#include <string>

namespace CubA4::render::engine::material
{
	enum class ShaderType
	{
		Vertex,
		Fragment
	};

	class IShader
	{
	public:
		virtual ~IShader() = default;

		virtual ShaderType getType() const = 0;
		virtual const std::string &getEntryPoint() const = 0;
	protected:
		explicit IShader() = default;
	private:
	};
}
