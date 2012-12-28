#include "stdafx.h"
#include "NewtonianObject.h"


NewtonianObject::NewtonianObject() : _velocity(0,0), _mass(1.0f), _weight(_mass*9.8f), _COF(1.0f), _FOF(_COF*_weight), _netForce(0,0)
{
	_pos=GetPosition();
}


NewtonianObject::~NewtonianObject()
{
}

void NewtonianObject::SetPosition(sf::Vector2f pos)
{
	_pos=pos;
	GetSprite().setPosition(pos.x, pos.y);
}

void NewtonianObject::Push(sf::Vector2f force)
{
	_netForce+=force;
}

void NewtonianObject::OnGround(bool onGround)
{
	_onGround=onGround;
}

void NewtonianObject::Stop()
{
	_velocity*=0.0f;
}

void NewtonianObject::StopY()
{
	_velocity.y=0.0f;
}

void NewtonianObject::StopX()
{
	_velocity.x=0.0f;
}

sf::Vector2f NewtonianObject::GetVelocity()
{
	return _velocity;
}

void NewtonianObject::DoPhysics(sf::Time elapsedTime)
{
	float deltaT = 15*elapsedTime.asSeconds(); //asMilliseconds doesn't work
	_netForce.y += _weight; //comment out for no gravity

	//temporary ground until real implementation
	if (_pos.y >= 500)
	{
		StopY();
		_netForce.x+= (_velocity.x > 0) ? -_FOF : _FOF;

		//if the only force is friction and the thing is pretty slow, stop it
		if(abs(_velocity.x)<1.0f && abs(_netForce.x)==abs(_FOF))
		{
			_velocity.x=0;
			_netForce.x=0;
		}
		_pos.y=500;
	}

	//good old kinematics
	sf::Vector2f accel = _netForce/_mass;
	sf::Vector2f newVel = _velocity + accel*deltaT;

	//limit horizontal speed
	if(abs(newVel.x) > _maxSpeed)
		newVel= sf::Vector2f((newVel.x > 0) ? _maxSpeed : -_maxSpeed, newVel.y);

	//move the object by averaging the velocity before and after this frame (this is exact for constant accelerations)
	_pos +=(_velocity + newVel)*deltaT/2.0f; //using a dedicated position because I don't trust GetPosition to interpolate between pixels

	SetPosition(_pos);

	//temporary edgeless world
	if(GetPosition().x<0) SetPosition(sf::Vector2f(1024,GetPosition().y));
	if(GetPosition().x>1024) SetPosition(sf::Vector2f(0,GetPosition().y));

	//clean up for next run
	_velocity = newVel;
	_netForce*=0.0f;


}

void NewtonianObject::SetVelocity(sf::Vector2f velocity)
{
	_velocity=velocity;
}

void NewtonianObject::SetMaxSpeed(float speed)
{
	_maxSpeed=speed;
}

float NewtonianObject::GetMaxSpeed()
{
	return _maxSpeed;
}


void NewtonianObject::SetMass(float mass)
{
	_mass=mass;
	_weight=mass*9.8f;
	_FOF=_weight*_COF;
}

float NewtonianObject::GetMass()
{
	return _mass;
}
