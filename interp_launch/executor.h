#pragma once
#include <memory>
#include "state.h"
#include "../generator/rpn_symbol.h"

class executor_base 
{
public:
	static rpn::ope_tag get_ope_tag() { return rpn::ope_tag::ope_COUNT; }
	virtual void execute(script_state& state) = 0;
};

#define DECLARE_EXECUTOR(ope, tag) \
class ope : public executor_base \
{ \
public:\
	static rpn::ope_tag get_ope_tag() { return tag; }\
	static std::shared_ptr<executor_base> create() {return std::make_shared<ope>();}\
	void execute(script_state& state) override;\
}\

namespace execs
{
	DECLARE_EXECUTOR(assign, rpn::ope_tag::ope_assignment);
	DECLARE_EXECUTOR(declare, rpn::ope_tag::ope_declaration);
	DECLARE_EXECUTOR(plus, rpn::ope_tag::ope_plus);
	DECLARE_EXECUTOR(minus, rpn::ope_tag::ope_minus);
	DECLARE_EXECUTOR(mul, rpn::ope_tag::ope_mul);
	DECLARE_EXECUTOR(div, rpn::ope_tag::ope_div);
	DECLARE_EXECUTOR(and, rpn::ope_tag::ope_and);
	DECLARE_EXECUTOR(or , rpn::ope_tag::ope_or);
	DECLARE_EXECUTOR(not, rpn::ope_tag::ope_not);
	DECLARE_EXECUTOR(equals, rpn::ope_tag::ope_equals);
	DECLARE_EXECUTOR(not_equals, rpn::ope_tag::ope_not_equals);
	DECLARE_EXECUTOR(less, rpn::ope_tag::ope_less);
	DECLARE_EXECUTOR(greater, rpn::ope_tag::ope_greater);
	DECLARE_EXECUTOR(greater_equals, rpn::ope_tag::ope_greater_equals);
	DECLARE_EXECUTOR(less_equals, rpn::ope_tag::ope_less_equals);
	DECLARE_EXECUTOR(read, rpn::ope_tag::ope_read);
	DECLARE_EXECUTOR(write, rpn::ope_tag::ope_write);
	DECLARE_EXECUTOR(jmp, rpn::ope_tag::ope_jmp);
	DECLARE_EXECUTOR(jmp_false, rpn::ope_tag::ope_jmp_false);
}