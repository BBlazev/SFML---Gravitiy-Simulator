#include "Particle.h"

Particle::Particle(float posX, float posY, float velX, float velY, float mass) : mass(mass)
{
	pos.x = posX;
	pos.y = posY;

	

	velocity.x = velX;
	velocity.y = velY;

	shape.setPosition(pos);
	shape.setFillColor(sf::Color::White);
	shape.setRadius(3 + mass * 0.5f);
}

void Particle::render(sf::RenderWindow& window)
{
	shape.setPosition(pos);
	window.draw(shape);
}

void Particle::update_phy( Gravity& gravity)
{
	float dist_x = gravity.get_pos().x - pos.x;
	float dist_y = gravity.get_pos().y- pos.y;
	float r = std::sqrt(pow(dist_x, 2) + pow(dist_y, 2));

	if (r == 0.f) return;


	float force = gravity.get_strenght() * (mass * gravity.get_mass()) / (r * r);

	float acceleraton = force / mass;

	float nx = dist_x / r;
	float ny = dist_y / r;

	velocity.x += nx * acceleraton;
	velocity.y += ny * acceleraton;

	pos.x += velocity.x;
	pos.y += velocity.y;

	/*
	float dist = sqrt(pow(dist_x, 2) + pow(dist_y, 2));
	 
	float inverse_dist = 1.f / dist;
	float normal_x = inverse_dist * dist_x;
	float normal_y = inverse_dist * dist_y;

	float inv_sq_dropoff = inverse_dist * inverse_dist;


	float acceleration_x = normal_x * gravity.get_strenght() * inv_sq_dropoff;
	float acceleration_y = normal_y * gravity.get_strenght() * inv_sq_dropoff;

	velocity.x += acceleration_x;
	velocity.y += acceleration_y;

	pos.x += velocity.x;
	pos.y += velocity.y;
	*/
	
}

void Particle::check_colision(std::vector<Particle>& particles)
{
	for (auto& other : particles)
	{
		if (&other == this) continue; 

		sf::Vector2f delta = other.get_pos() - this->pos;
		float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
		float minDist = this->get_radius() + other.get_radius();

		if (distance < minDist) 
		{
			sf::Vector2f normal = delta / distance;
			sf::Vector2f tangent(-normal.y, normal.x);

			float v1n = normal.x * velocity.x + normal.y * velocity.y;
			float v2n = normal.x * other.get_velocity().x + normal.y * other.get_velocity().y;

			float v1t = tangent.x * velocity.x + tangent.y * velocity.y;
			float v2t = tangent.x * other.get_velocity().x + tangent.y * other.get_velocity().y;

			float m1 = this->mass, m2 = other.mass;
			float new_v1n = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
			float new_v2n = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

			sf::Vector2f new_v1 = normal * new_v1n + tangent * v1t;
			sf::Vector2f new_v2 = normal * new_v2n + tangent * v2t;

			this->set_velocity(new_v1);
			other.set_velocity(new_v2);

			float overlap = minDist - distance;
			sf::Vector2f correction = normal * (overlap / 2.f);
			pos -= correction;
			other.pos += correction;
		}
	}
}
