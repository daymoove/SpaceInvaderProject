#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyMove.h"

class GameManager
{
public:
	GameManager();
	void Run();

private:
	void SpawnEnemy(sf::Texture& enemyTexture);
	void EndMenu(bool winOrLose);

private:
	sf::Event event;
	Player player;
	EnemyMove enemyMove;
	sf::Clock bulletCooldown;
	sf::Clock EnemyCooldown;
	float enemyTimer;
	float changeX;
	const int windowX = 800;
	const int windowY = 600;
	int randomEnemy;
	int score;
	bool drawBullet;
	bool drawEnemyBullet;
	bool shootBullet;
	bool shootEnemyBullet;
	bool winOrLose;
	bool lose;
	bool startGame;
	std::vector<Enemy> listEnemy;
};
