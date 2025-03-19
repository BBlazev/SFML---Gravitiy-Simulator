#include "Gravity.h"

Gravity::Gravity(float posX, float posY, float strenght, float mass) :mass(mass), velocity(0.78f, 0.67f), radius(1.f)
{
	pos.x = posX;
	pos.y = posY;


	this->strenght = strenght;
	shape.setPosition(pos);
	shape.setFillColor(sf::Color::White);
	shape.setRadius(10);

}

void Gravity::render(sf::RenderWindow& window)
{
	window.draw(shape);

}

void Gravity::update(std::vector<Gravity>& other_gravities, float dt)
{
	sf::Vector2f total_Force(0.f, 0.f);
	const float G = 6.67430e-1f;

	for (auto& grav : other_gravities) {
		if (&grav == this) continue;

		sf::Vector2f delta = grav.get_pos() - this->get_pos();
		float dist = std::sqrt(pow(delta.x, 2) + pow(delta.y, 2));

		//if (dist < 0.1f) continue;

		float force_mag = (G * this->mass * grav.get_mass()) / (dist * dist);
		force_mag *= 0.1f;
		sf::Vector2f direction = delta / dist;

		total_Force += direction * force_mag;

	}

	sf::Vector2f acceleration = total_Force / this->mass;
	velocity += acceleration * dt;

	pos += velocity * dt;
	shape.setPosition(pos);

}

float Gravity::get_radius()
{
	return radius;
}

sf::Vector2f Gravity::get_pos()
{
	return pos;

}

float Gravity::get_strenght()
{
	return strenght;
}

float Gravity::get_mass()
{
	return mass;
}

void Gravity::set_mass(float mass)
{
	this->mass = mass;
}
