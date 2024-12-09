#include "left_review_agent.hpp"
#include "keynodes/review_keynodes.hpp"

ScAddr LeftReviewAgent::GetActionClass() const
{
    return ReviewKeynodes::action_left_review;
}

ScResult LeftReviewAgent::DoProgram(ScAction & action)
{
    std::string review_left_str;
    auto const & [user, sight, review_left, rating_left] = action.GetArguments<4>();

    if (!m_context.GetLinkContent(review_left, review_left_str))
    {
        SC_AGENT_LOG_ERROR("Review is empty.");
        return action.FinishWithError();
    }

    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        user,
        ScType::ConstCommonArc,
        ScType::ConstNode,
        ScType::ConstPermPosArc,
        ReviewKeynodes::nrel_review_left
    );
    while (it5->Next())
    {
        if (LeftReviewAgent::GetSight(it5->Get(2)) == sight)
        {
            SC_AGENT_LOG_INFO("Such review exist.");
            m_context.SetLinkContent(LeftReviewAgent::GetReviewText(it5->Get(2)), review_left_str);

            LeftReviewAgent::DeleteOldRating(it5->Get(2));

            SC_AGENT_LOG_INFO("New rating.");
            ScAddr const & rating_arcAddr = m_context.GenerateConnector(ScType::ConstPermPosArc, it5->Get(2), rating_left);
            m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::rrel_rating, rating_arcAddr);

            SC_AGENT_LOG_INFO("Review edited.");
            return action.FinishSuccessfully();
        }
    }

    LeftReviewAgent::CreateReview(user, sight, review_left, rating_left);

    SC_AGENT_LOG_INFO("Review added");
    return action.FinishSuccessfully();
}

ScAddr LeftReviewAgent::GetSight(ScAddr user_review)
{
    SC_AGENT_LOG_INFO("Get sight.");
    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        ScType::ConstNode,
        ScType::ConstCommonArc,
        user_review,
        ScType::ConstPermPosArc,
        ReviewKeynodes::nrel_user_review
    );

    it5->Next();
    return it5->Get(0);
}

ScAddr LeftReviewAgent::GetReviewText(ScAddr user_review)
{
    SC_AGENT_LOG_INFO("Get review text.");
    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        user_review,
        ScType::ConstPermPosArc,
        ScType::ConstNodeLink,
        ScType::ConstPermPosArc,
        ReviewKeynodes::rrel_review
    );
    it5->Next();
    return it5->Get(2);
}

void LeftReviewAgent::DeleteOldRating(ScAddr user_review)
{
    SC_AGENT_LOG_INFO("Get review text.");
    ScIterator5Ptr const it5 = m_context.CreateIterator5(
        user_review,
        ScType::ConstPermPosArc,
        ScType::ConstNode,
        ScType::ConstPermPosArc,
        ReviewKeynodes::rrel_rating
    );
    it5->Next();   
    SC_AGENT_LOG_INFO("Del old rating.");
    m_context.EraseElement(it5->Get(1));
}

void LeftReviewAgent::CreateReview(ScAddr user, ScAddr sight, ScAddr review_left, ScAddr rating_left)
{
    SC_AGENT_LOG_INFO("Create review.");
    ScAddr const & review_Node = m_context.GenerateNode(ScType::ConstNode);

    ScAddr const & review_arcAddr = m_context.GenerateConnector(ScType::ConstPermPosArc, review_Node, review_left);
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::rrel_review, review_arcAddr);
    ScAddr const & rating_arcAddr = m_context.GenerateConnector(ScType::ConstPermPosArc, review_Node, rating_left);
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::rrel_rating, rating_arcAddr);

    ScAddr const & user_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, user, review_Node);
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::nrel_review_left, user_arcAddr);
    ScAddr const & sight_arcAddr = m_context.GenerateConnector(ScType::ConstCommonArc, sight, review_Node);
    m_context.GenerateConnector(ScType::ConstPermPosArc, ReviewKeynodes::nrel_user_review, sight_arcAddr);
}