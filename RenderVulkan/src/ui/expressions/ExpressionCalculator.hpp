#pragma once

#include <ui/expressions/Expressions.hpp>
#include <ui/expressions/Operation.hpp>
#include <ui/expressions/Context.hpp>

namespace CubA4::render::ui
{
	class ExpressionCalculator
	{
	public:
		ExpressionCalculator(Context &ctx);

		void calculate(Expression &expression) const;
	private:
		long double calculate(Operation &operation) const;
	private:
		Context &ctx_;
	};
}