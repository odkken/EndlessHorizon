#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"


//describes object which have mass and are subject to gravity (and any other forces)
class NewtonianObject : public VisibleGameObject
{
public:
	NewtonianObject();
	~NewtonianObject();

	void GroundCalc(float surfacePosition);
	void GroundCollide(bool touchingGround);
	void Push(sf::Vector2f force);
	void Stop();
	void StopX();
	void StopY();
	void DoPhysics(sf::Time elapsedTime);
	void OnGround(bool onGround);
	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetVelocity();
	void SetMaxSpeed(float speed);
	float GetMaxSpeed();
	void SetClosest(const sf::RectangleShape &closestPlatform);

protected:
	void SetVelocity(sf::Vector2f velocity);
	void SetMass(float mass);
	float GetMass();
	float _maxSpeed;
	bool _touchingGround;
	

private:
	sf::FloatRect _closestPlatform;
	sf::Vector2f _velocity, _netForce, _pos;
	float _mass, _weight;
	float _COF, _FOF; //coefficient and force of friction
};