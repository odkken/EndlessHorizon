#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"


//describes object which have mass and are subject to gravity (and any other forces)
class NewtonianObject : public VisibleGameObject
{
public:
	NewtonianObject();
	~NewtonianObject();

	void Push(sf::Vector2f force);
	void Stop();
	void StopX();
	void StopY();
	void DoPhysics(sf::Time elapsedTime);
	void OnGround(bool onGround);
	void SetPosition(sf::Vector2f pos);
	
protected:
	void SetVelocity(sf::Vector2f velocity);
	sf::Vector2f GetVelocity();
	void SetMass(float mass);
	float GetMass();
	float _maxSpeed;

private:
	sf::Vector2f _velocity, _netForce, _pos;
	float _mass, _weight;
	float _COF, _FOF; //coefficient and force of friction
	bool _onGround;

};