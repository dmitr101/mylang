#include "executor_factory.h"

void executor_factory::register_all()
{
	register_executor<execs::assign>();
	register_executor<execs::declare>();
	register_executor<execs::plus>();
	register_executor<execs::minus>();
	register_executor<execs::mul>();
	register_executor<execs::div>();
	register_executor<execs::and>();
	register_executor<execs::or>();
	register_executor<execs::not>();
	register_executor<execs::equals>();
	register_executor<execs::not_equals>();
	register_executor<execs::less>();
	register_executor<execs::greater>();
	register_executor<execs::greater_equals>();
	register_executor<execs::less_equals>();
	register_executor<execs::read>();
	register_executor<execs::write>();
	register_executor<execs::jmp>();
	register_executor<execs::jmp_false>();
}

executor_factory::product executor_factory::create(rpn::ope_tag tag)
{
	return creators_[tag]();
}
