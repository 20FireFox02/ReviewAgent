#include "review_module.hpp"

#include "agents/left_review_agent.hpp"

SC_MODULE_REGISTER(ReviewModule)
    ->Agent<LeftReviewAgent>();