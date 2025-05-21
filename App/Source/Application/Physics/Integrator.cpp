#include "Integrator.hpp"

Physics::Integrator::Integrator()
{
}

void Physics::Integrator::verletIntegration(Ball& ball, float dt)
{
	/* Verlet Integration
	Vec3d new_pos = pos + vel * dt + acc * (dt * dt * 0.5);
	Vec3d new_acc = apply_forces();
	Vec3d new_vel = vel + (acc + new_acc) * (dt * 0.5);
	pos = new_pos;
	vel = new_vel;
	acc = new_acc;
	*/
	float newX = ball.x + ball.xVel * dt + ball.xAcc * (dt * dt * 0.5);
	float newY = ball.y + ball.yVel * dt + ball.yAcc * (dt * dt * 0.5);

	float xAcc = ball.xForce;
	float yAcc = ball.yForce;

	float xVel = ball.xVel + (ball.xAcc + xAcc) * (dt * 0.5);
	float yVel = ball.yVel + (ball.yAcc + yAcc) * (dt * 0.5);

	ball.x = newX;
	ball.y = newY;

	ball.xVel = xVel;
	ball.yVel = yVel;
	ball.xAcc = xAcc;
	ball.yAcc = yAcc;

}

void Physics::Integrator::eulerIntegration(Ball& ball, float dt)
{
	ball.xAcc = ball.xForce;
	ball.yAcc = ball.yForce;

	ball.xVel += ball.xAcc * dt;
	ball.yVel += ball.yAcc * dt;

	ball.x += ball.xVel * dt;
	ball.y += ball.yVel * dt;
}

void Physics::Integrator::rebound(Ball& ball)
{
	if (ball.x + ball.radius >= 1400 || ball.x - ball.radius <= 0)
		ball.xVel *= -1;

	if (ball.y + ball.radius >= 1200 || ball.y - ball.radius <= 0)
		ball.yVel *= -1;
}

bool Physics::Integrator::detectCollision(Ball& a, Ball& b)
{

	float xDiff = b.x - a.x;
	float yDiff = b.y - a.y;
	float rSum = a.radius + b.radius;

	//float dist = sqrt(xDiff * xDiff + yDiff * yDiff);
	float dSqr = xDiff * xDiff + yDiff * yDiff;

	return dSqr <= rSum * rSum;
}

void Physics::Integrator::resolveCollision(Ball& a, Ball& b)
{
	float xDiff = b.x - a.x;
	float yDiff = b.y - a.y;
	float rSum = a.radius + b.radius;



	//float dist = sqrt(xDiff * xDiff + yDiff * yDiff);
	float dSqr = xDiff * xDiff + yDiff * yDiff;
	float dist = sqrt(dSqr);

	float xNorm = xDiff / dist;
	float yNorm = yDiff / dist;

	float relX = b.xVel - a.xVel;
	float relY = b.yVel - a.yVel;

	float velAlongNormal = xNorm * relX + yNorm * relY;

	if (velAlongNormal > 0)
		return;

	float e = fmin(a.e, b.e);

	float j = -(1 + e) * velAlongNormal;
	j /= 1 / a.mass + 1 / b.mass;

	float xImpulse = xNorm * j;
	float yImpulse = yNorm * j;

	a.xVel -= xImpulse / a.mass;
	a.yVel -= yImpulse / a.mass;

	b.xVel += xImpulse / b.mass;
	b.yVel += yImpulse / b.mass;
}
