#pragma once

#include "sc-memory/sc_keynodes.hpp"

class ReviewKeynodes : public ScKeynode
{
public:
    static inline ScKeynode const action_left_review{"action_left_review", ScType::ConstNodeClass};
    static inline ScKeynode const nrel_user_review{"nrel_user_review", ScType::ConstNodeNonRole};
    static inline ScKeynode const nrel_review_left{"nrel_review_left", ScType::ConstNodeNonRole};
    static inline ScKeynode const rrel_review{"rrel_review", ScType::ConstNodeRole};
    static inline ScKeynode const rrel_rating{"rrel_rating", ScType::ConstNodeRole};
    static inline ScKeynode const one{"1.0", ScType::ConstNode};
    static inline ScKeynode const two{"2.0", ScType::ConstNode};
    static inline ScKeynode const three{"3.0", ScType::ConstNode};
    static inline ScKeynode const four{"4.0", ScType::ConstNode};
    static inline ScKeynode const five{"5.0", ScType::ConstNode};
    static inline ScKeynode const rating{"rating", ScType::ConstNodeClass};
};