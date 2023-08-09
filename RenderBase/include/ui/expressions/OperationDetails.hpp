#pragma once

#include <ui/expressions/Operation.hpp>
#include <ui/expressions/Expression.hpp>

namespace CubA4::render::ui
{
	Operation::Operation(OperationType type, const Expression &left, const Expression &right) :
		type_(type), left_(std::make_unique<Expression>(left)), right_(std::make_unique<Expression>(right))
	{
		
	}

	Operation::Operation(const Operation &old) :
		type_(old.type_), left_(std::make_unique<Expression>(*old.left_)), right_(std::make_unique<Expression>(*old.right_))
	{

	}

	Operation::~Operation() = default;

	inline void Operation::markDirty()
	{
		left_->markDirty();
		right_->markDirty();
	}
}