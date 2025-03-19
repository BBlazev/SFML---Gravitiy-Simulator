#pragma once
#include <SFML/Graphics.hpp>

class Gravity
{
private:
	sf::Vector2f pos;
	float strenght; // yes its misspelled, and im too lazy to change it :)
	float mass;
	float radius;
	sf::CircleShape shape;

public:
	Gravity(float posX, float posY, float strenght, float mass);

	sf::Vector2f get_pos();
	sf::Vector2f velocity;
	float get_strenght(); 
	float get_mass();
	float get_radius();

	void set_mass(float mass);
	void render(sf::RenderWindow& window);
	void update(std::vector<Gravity>& other_gravities, float dt);
	
};
