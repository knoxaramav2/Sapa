#ifndef BIO
#define BIO

#include "NeuroTransmitter.hpp"

#define CT_STEM		0x0
#define CT_MOTOR	0x1
#define CT_SENSORY	0x2
#define CT_LOGICAL	0x3

struct cell
{
	float xpos;
	float ypos;
	float zpos;

	float charge;

	virtual void receive(float, transmitter)=0;
	virtual void update()=0;
	virtual void fire()=0;

	char cellType;

	transmitter inFilter;
	transmitter outFilter;

	cell();
};

struct motor : public cell
{
	motor();
	virtual void receive(float, transmitter);
	virtual void update();
	virtual void fire();
};

struct sensory : public cell
{
	sensory();
	virtual void receive(float, transmitter);
	virtual void update();
	virtual void fire();
};

struct logical : public cell
{
	logical();
	virtual void receive(float, transmitter);
	virtual void update();
	virtual void fire();

	transmitter propagator;
};

#endif