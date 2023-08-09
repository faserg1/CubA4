#pragma once

#include <ui/expressions/Expressions.hpp>
#include <ui/expressions/Operation.hpp>

namespace CubA4::render::ui
{
	inline Expression operator+(const Expression &left, const Expression &right)
	{
		return Expression(Operation(OperationType::Add, left, right));
	}

	inline Expression operator-(const Expression &left, const Expression &right)
	{
		return Expression(Operation(OperationType::Subtract, left, right));
	}

	inline Expression operator*(const Expression &left, const Expression &right)
	{
		return Expression(Operation(OperationType::Multiply, left, right));
	}

	inline Expression operator/(const Expression &left, const Expression &right)
	{
		return Expression(Operation(OperationType::Divide, left, right));
	}
}