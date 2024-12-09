#pragma once
#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_agent.hpp>

class LeftReviewAgent : public ScActionInitiatedAgent
{
public:
    ScAddr GetActionClass() const override;
    ScResult DoProgram(ScAction & action) override;

    ScAddr GetSight(ScAddr user_review);
    ScAddr GetReviewText(ScAddr user_review);
    void DeleteOldRating(ScAddr user_review);
    void CreateReview(ScAddr user, ScAddr sight, ScAddr review_left, ScAddr rating_left);
};