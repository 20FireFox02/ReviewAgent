#pragma once

#include "sc-memory/sc_keynodes.hpp"

class ReviewKeynodes : public ScKeynode
{
public:
    static inline ScKeynode const action_left_review{"action_left_review", ScType::ConstNodeClass};
    static inline ScKeynode const review{"review", ScType::ConstNodeClass};
    static inline ScKeynode const nrel_review{"nrel_review", ScType::ConstNodeNonRole};
    static inline ScKeynode const nrel_user_review{"nrel_user_review", ScType::ConstNodeNonRole};
};