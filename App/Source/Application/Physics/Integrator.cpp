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
	*//*
	float newX = ball.x + ball.xVel * dt + ball.xAcc * (dt * dt * 0.5);
	float newY = ball.y + ball.yVel * dt + ball.yAcc * (dt * dt * 0.5);*/

	Math::Vector2 new_pos = ball.pos + ball.vel * dt + ball.acc * (dt * dt * 0.5);

	Math::Vector2 new_acc = ball.force;

	Math::Vector2 new_vel = ball.vel + (ball.acc + new_acc) * (dt * 0.5);

	ball.pos = new_pos;
	ball.vel = new_vel;
	ball.acc = new_acc;

	ball.boundingBox.min = ball.pos - Math::Vector2(ball.radius, ball.radius);
	ball.boundingBox.max = ball.pos + Math::Vector2(ball.radius, ball.radius);

	/*float xAcc = ball.xForce;
	float yAcc = ball.yForce;

	float xVel = ball.xVel + (ball.xAcc + xAcc) * (dt * 0.5);
	float yVel = ball.yVel + (ball.yAcc + yAcc) * (dt * 0.5);

	ball.x = newX;
	ball.y = newY;

	ball.xVel = xVel;
	ball.yVel = yVel;
	ball.xAcc = xAcc;
	ball.yAcc = yAcc;*/

}

void Physics::Integrator::eulerIntegration(Ball& ball, float dt)
{
	/*ball.xAcc = ball.xForce;
	ball.yAcc = ball.yForce;

	ball.xVel += ball.xAcc * dt;
	ball.yVel += ball.yAcc * dt;

	ball.x += ball.xVel * dt;
	ball.y += ball.yVel * dt;*/

	ball.acc = ball.force;
	ball.vel += ball.acc * dt;
	ball.pos += ball.vel * dt;
}

void Physics::Integrator::rebound(Ball& ball)
{
	if (ball.pos.x + ball.radius >= 1400 || ball.pos.x - ball.radius <= 0)
		ball.vel.x *= -1;

	if (ball.pos.y + ball.radius >= 1200 || ball.pos.y - ball.radius <= 0)
		ball.vel.y *= -1;
}

bool Physics::Integrator::detectCollision(Ball& a, Ball& b)
{

	
	float rSum = a.radius + b.radius;

	//float dist = sqrt(xDiff * xDiff + yDiff * yDiff);
	float dSqr = (b.pos - a.pos).lenSqr();

	return dSqr <= rSum * rSum;
}

void Physics::Integrator::resolveCollision(Ball& a, Ball& b)
{
	//float dist = sqrt(xDiff * xDiff + yDiff * yDiff);

	Math::Vector2 diff = b.pos - a.pos;

	float dist = diff.len();

	Math::Vector2 normal = diff / dist;

	Math::Vector2 relativeVel = (b.vel - a.vel);

	float velAlongNormal = normal.dot(relativeVel);

	if (velAlongNormal > 0)
		return;

	float e = fmin(a.e, b.e);

	float j = -(1 + e) * velAlongNormal;
	j /= 1 / a.mass + 1 / b.mass;

	Math::Vector2 impulse = normal * j;

	a.vel -= impulse / a.mass;
	b.vel += impulse / b.mass;

	solveOverlap(a, b);
}

void Physics::Integrator::solveOverlap(Ball& a, Ball& b)
{
	Math::Vector2 diff = b.pos - a.pos;
	float dist = diff.len();

	float rads = b.radius + a.radius;

	float overlap = (rads - dist) / 2;

	Math::Vector2 normal = diff / dist;

	a.pos -= normal * overlap;
	b.pos += normal * overlap;
}
