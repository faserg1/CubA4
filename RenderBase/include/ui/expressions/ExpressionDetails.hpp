#pragma once

#include <ui/expressions/Expression.hpp>
#include <ui/expressions/Operation.hpp>

namespace CubA4::render::ui
{
	Expression::Expression() :
		type_(ExpressionType::Pixel)
	{

	}

	Expression::Expression(ExpressionType type, long double value) :
		type_(type), valueRaw_(value)
	{
		// assert type != Operation
		if (type == ExpressionType::Pixel)
		{
			valueExpression_ = value;
		}
		else
			dirty_ = true;
	}
	Expression::Expression(const Operation &op) :
		type_(ExpressionType::Operation), dirty_(true), operation_(std::make_unique<Operation>(op))
	{
	}

	Expression::Expression(const Expression &old) :
		type_(old.type_), valueRaw_(old.valueRaw_), valueExpression_(old.valueExpression_), dirty_(old.dirty_),
		operation_(old.operation_ ? std::make_unique<Operation>(*old.operation_) : std::unique_ptr<Operation>(nullptr))
	{

	}

	Expression::~Expression() = default;

	Expression &Expression::operator=(const Expression &other)
	{
		type_ = other.type_;
		valueRaw_ = other.valueRaw_;
		valueExpression_ = other.valueExpression_;
		dirty_ = (type_ != ExpressionType::Pixel);

		if (other.operation_)
			operation_ = std::make_unique<Operation>(*other.operation_);
		else
			operation_ = {};
		
		return *this;
	}

	void Expression::markDirty()
	{
		dirty_ = true;
		if (operation_)
			operation_->markDirty();
	}

	long double Expression::getValue()
	{
		// TODO: assert !dirty_
		return valueExpression_;
	}
}

namespace CubA4::render::ui_literals
{
	inline CubA4::render::ui::Expression operator""_vh(long double value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ViewportHeight, value);
	}

	inline CubA4::render::ui::Expression operator""_vw(long double value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ViewportWidth, value);
	}

	inline CubA4::render::ui::Expression operator""_ph(long double value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ParentHeight, value);
	}

	inline CubA4::render::ui::Expression operator""_pw(long double value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ParentWidth, value);
	}

	inline CubA4::render::ui::Expression operator""_px(long double value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::Pixel, value);
	}

	inline CubA4::render::ui::Expression operator""_vh(unsigned long long value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ViewportHeight, static_cast<long double>(value));
	}

	inline CubA4::render::ui::Expression operator""_vw(unsigned long long value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ViewportWidth, static_cast<long double>(value));
	}

	inline CubA4::render::ui::Expression operator""_ph(unsigned long long value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ParentHeight, static_cast<long double>(value));
	}

	inline CubA4::render::ui::Expression operator""_pw(unsigned long long value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::ParentWidth, static_cast<long double>(value));
	}

	inline CubA4::render::ui::Expression operator""_px(unsigned long long value)
	{
		return CubA4::render::ui::Expression(CubA4::render::ui::ExpressionType::Pixel, static_cast<long double>(value));
	}
}
