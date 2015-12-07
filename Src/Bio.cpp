#include "Bio.hpp"

cell::cell()
{
	xpos = ypos = zpos = 0.0f;
	charge = 0.0f;
	cellType = CT_STEM;
}


motor::motor()
{
	cellType = CT_MOTOR;
}

void motor::receive(float w, transmitter t)
{

}

void motor::update()
{

}

void motor::fire()
{

}


sensory::sensory()
{
	cellType = CT_MOTOR;
}

void sensory::receive(float w, transmitter t)
{

}

void sensory::update()
{

}

void sensory::fire()
{

}


logical::logical()
{
	cellType = CT_MOTOR;
}

void logical::receive(float w, transmitter t)
{

}

void logical::update()
{

}

void logical::fire()
{

}