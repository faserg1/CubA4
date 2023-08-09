#pragma once

#include <ui/expressions/ExpressionType.hpp>
#include <memory>

namespace CubA4::render::ui
{
	class Operation;

	class Expression
	{
		friend class ExpressionCalculator;
	public:
		inline Expression();
		inline Expression(ExpressionType type, long double value);
		inline Expression(const Expression &old);
		inline Expression(const Operation &op);
		inline ~Expression();

		inline Expression &operator=(const Expression &other);

		inline void markDirty();

		inline long double getValue();
	private:
		ExpressionType type_;
		long double valueRaw_ = 0.f;
		long double valueExpression_ = 0.f;
		
		bool dirty_ = false;

		std::unique_ptr<Operation> operation_;
	};
}


// Expressions should be like:
// 100vh + ph - 12px
// Where
// vh - viewport height in percentage (like absolute height)
// ph - parent height
// px - pixels

// Expressions should have cache (lazy) and markAsDirty when need to be calculated again