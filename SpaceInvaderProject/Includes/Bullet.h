#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Bullet
{
public:
	sf::Sprite bulletSprite;
	Bullet(sf::Texture& texture);
	sf::FloatRect bulletRect;

private:

};
