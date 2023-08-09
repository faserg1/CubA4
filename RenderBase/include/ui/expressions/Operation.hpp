#pragma once

#include <ui/expressions/OperationType.hpp>
#include <memory>

namespace CubA4::render::ui
{
	class Expression;

	class Operation
	{
		friend class ExpressionCalculator;
	public:
		inline Operation(OperationType type, const Expression &left, const Expression &right);
		inline Operation(const Operation &old);
		inline ~Operation();

		inline void markDirty();
	private:
		OperationType type_;
		std::unique_ptr<Expression> left_;
		std::unique_ptr<Expression> right_;
	};
}
