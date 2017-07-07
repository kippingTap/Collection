#pragma once
#include<string>
#include<vector>
#include"Transition.h"

class AnimationClip;
class StateMachine;

class State
{
	friend class  StateMachine;

public:
	State();
	State(const std::string& name);
	virtual ~State();

	//name
private:
	std::string								m_name;
public:
	std::string								GetName(){ return m_name; }
	bool									SetName(const std::string& name);


	//animation
private:
	AnimationClip*							m_animClip;
	float									m_speedAnimClip;
	bool									m_loopAnimClip;
public:
	AnimationClip*							GetAnimationClip(){ return m_animClip; }
	void									SetAnimationClip(AnimationClip* animclip){ m_animClip = animclip; }
	float									GetAnimationClipSpeed(){ return m_speedAnimClip; }
	void									SetAnimationClipSpeed(float speed){ m_speedAnimClip = speed; }
	bool									IsLoopAnimationClip(){ return m_loopAnimClip; }
	void									SetLoopAnimationClip(bool setting){ m_loopAnimClip = setting; }


	//transitions
public:
	typedef std::vector<Transition*>		t_transition_vector;
private:
	t_transition_vector						m_transitions;

public:
	Transition*								AddTransition(State* from, State* to, transition_condition_funtor condition = NULL);
	Transition*								GetTransition(State* from, State* to);
	bool									RegisterTransitionCondition(State* from, State* to, transition_condition_funtor condition);


};