#pragma once

#include <string>

namespace CubA4::render::engine::model
{
	class IRenderModel
	{
	public:
		virtual const std::string &getId() const = 0;
	protected:
		explicit IRenderModel() = default;
		virtual ~IRenderModel() = default;
	private:
	};
}

