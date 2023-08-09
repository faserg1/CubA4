#include <ui/expressions/ExpressionCalculator.hpp>
using namespace CubA4::render::ui;

ExpressionCalculator::ExpressionCalculator(Context &ctx) :
	ctx_(ctx)
{

}

void ExpressionCalculator::calculate(Expression &expression) const
{
	if (!expression.dirty_)
		return;
	switch (expression.type_)
	{
	case ExpressionType::ParentHeight:
	{
		expression.valueExpression_ = ctx_.parentHeight / 100 * expression.valueRaw_;
		break;
	}
	case ExpressionType::ParentWidth:
	{
		expression.valueExpression_ = ctx_.parentWidth / 100 * expression.valueRaw_;
		break;
	}
	case ExpressionType::ViewportHeight:
	{
		expression.valueExpression_ = ctx_.viewportHeight / 100 * expression.valueRaw_;
		break;
	}
	case ExpressionType::ViewportWidth:
	{
		expression.valueExpression_ = ctx_.parentWidth / 100 * expression.valueRaw_;
		break;
	}
	case ExpressionType::Operation:
	{
		expression.valueExpression_ = calculate(*expression.operation_);
		break;
	}
	case ExpressionType::Pixel:
	{
		expression.valueExpression_ = expression.valueRaw_;
		break;
	}

	}
	expression.dirty_ = false;
}

long double ExpressionCalculator::calculate(Operation &operation) const
{
	calculate(*operation.left_);
	calculate(*operation.right_);

	switch (operation.type_)
	{
	case OperationType::Add:
		return operation.left_->valueExpression_ + operation.right_->valueExpression_;
	case OperationType::Subtract:
		return operation.left_->valueExpression_ - operation.right_->valueExpression_;
	case OperationType::Multiply:
		return operation.left_->valueExpression_ * operation.right_->valueExpression_;
	case OperationType::Divide:
		return operation.left_->valueExpression_ / operation.right_->valueExpression_;
	}
	// TODO: assert
	return 0;
}