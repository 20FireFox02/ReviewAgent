#include "left_review_agent.hpp"
#include "keynodes/review_keynodes.hpp"

ScAddr LeftReviewAgent::GetActionClass() const
{
    return ReviewKeynodes::action_left_review;
}

ScResult LeftReviewAgent::DoProgram(ScAction & action)
{
    std::string review_left_str;
    auto const & [user, sight, review_left] = action.GetArguments<3>();


    if (!m_context.GetLinkContent(review_left, review_left_str))
    {
        SC_AGENT_LOG_ERROR("Review is empty.");
        return action.FinishWithError();
    }

    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        user,
        ScType::ConstCommonArc,
        ScType::ConstNodeLink,
        ScType::ConstPermPosArc,
        ReviewKeynodes::nrel_user_review
    );
    while (it5->Next())
    {
        if (LeftReviewAgent::GetSight(it5->Get(2)) == sight)
        {
            SC_AGENT_LOG_INFO("Review edited.");
            m_context.SetLinkContent(it5->Get(2), review_left_str);
            return action.FinishSuccessfully();
        }
    }

    SC_AGENT_LOG_INFO("Review added");
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::review, review_left);
    ScAddr const & user_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, user, review_left);
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::nrel_user_review, user_arcAddr);
    ScAddr const & sight_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, sight, review_left);
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::nrel_review, sight_arcAddr);

    return action.FinishSuccessfully();
}

ScAddr LeftReviewAgent::GetSight(ScAddr user_review)
{
    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        ScType::ConstNode,
        ScType::ConstCommonArc,
        user_review,
        ScType::ConstPermPosArc,
        ReviewKeynodes::nrel_review
    );

    it5->Next();
    return it5->Get(0);
}