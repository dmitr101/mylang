#include "scanner_private_builder.h"



scanner_private_builder::scanner_private_builder()
{
    result_ = std::make_unique<scanner_private>();
}

scanner_private_builder& scanner_private_builder::set_fsm(stream_fsm&& fsm)
{
    result_->fsm_ = std::move(fsm);
    return *this;
}

scanner_private_builder& scanner_private_builder::add_keyword(std::string const& keyword)
{
    result_->keywords_.emplace(keyword);
    return *this;
}

std::unique_ptr<scanner_private> scanner_private_builder::get()
{
    return std::move(result_);
}
