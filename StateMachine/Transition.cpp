#include"Transition.h"
#include"State.h"


Transition::Transition()
:m_scrState(nullptr)
, m_tarState(nullptr)
, m_showTag()
{
	m_condiction = nullptr;
}

Transition::Transition(State* fromState, State* toState)
:m_scrState(fromState)
, m_tarState(toState)

{
	m_condiction = nullptr;
	m_showTag = m_scrState->GetName() + "->" + m_tarState->GetName();
}


Transition::Transition(State* fromState, State* toState, transition_condition_funtor condition)
:m_scrState(fromState)
, m_tarState(toState)
{
	m_condiction = condition;
	m_showTag = m_scrState->GetName() + "->" + m_tarState->GetName();
}

Transition::~Transition()
{

}




bool Transition::CanEnterToTargetState()
{
	if (m_condiction)
	{
		return m_condiction();
	}
	return false;
}