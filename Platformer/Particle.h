#pragma once
#include <SFML/Graphics.hpp>
#include "Gravity.h"
class Particle
{
private:
	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::CircleShape shape;

	float mass;



public:
	Particle(float posX, float posY, float velX, float velY, float mass);

	void render(sf::RenderWindow& window);
	void update_phy( Gravity& gravity);
	void check_colision(std::vector<Particle>& particles);
	void set_velocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }

	sf::Vector2f get_pos() { return pos; }
	sf::Vector2f get_velocity() { return velocity; }

	float get_radius() const { return shape.getRadius(); }
	
};

