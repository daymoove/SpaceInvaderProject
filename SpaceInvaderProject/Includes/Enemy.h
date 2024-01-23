#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Enemy
{
public:
	std::vector<sf::Sprite> listEnemySprite;
	sf::Sprite enemySprite;

	Enemy(sf::Sprite Sprite);
	sf::FloatRect enemyRect;

private :
	float enemySpeed;
};


