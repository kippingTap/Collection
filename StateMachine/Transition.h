#pragma once
// transition: contain data that one state enter another state
#include<string>
#include<functional>


class State;
class StateMachine;

typedef std::function<bool()>  transition_condition_funtor;

class Transition
{
	friend	class State;
	friend	class StateMachine;
public:
	Transition();
	Transition(State* fromState, State* toState);
	Transition(State* fromState, State* toState, transition_condition_funtor condition);
	virtual ~Transition();

	State*				GetSourceState(){ return m_scrState; }
	State*				GetTargetState(){ return m_tarState; }
	std::string			GetShowtag(){ return m_showTag; }


	void				SetTargetState(State* s){ m_tarState = s; }
	void				SetSourceState(State* s){ m_scrState = s; }
	void				SetShowtag(const std::string& t){ m_showTag = t; }
	void				SetCondition(transition_condition_funtor condition){ m_condiction = condition; }

	virtual bool		CanEnterToTargetState();


private:
	State*						m_scrState; //from state
	State*						m_tarState; //to state
	std::string					m_showTag;      // src->tar
	transition_condition_funtor		m_condiction;   //if return true, object will enter target state from source state
};