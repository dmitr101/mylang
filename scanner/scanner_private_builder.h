#pragma once
#include "stream_fsm.h"
#include "scanner_private.h"
#include <memory>
class scanner_private_builder
{
public:
    scanner_private_builder();
    ~scanner_private_builder() = default;

    scanner_private_builder& set_fsm(stream_fsm&& fsm);
    scanner_private_builder& add_keyword(std::string const& keyword);
    template<typename CONTAINER>
    scanner_private_builder& add_keywords(CONTAINER const& words)
    {
        for (auto const& word : words)
            add_keyword(word);
        return *this;
    }
    std::unique_ptr<scanner_private> get();

private:
    std::unique_ptr<scanner_private> result_;
};

