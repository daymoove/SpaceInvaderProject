#include "EnemyMove.h"
#include <iostream>



EnemyMove::EnemyMove()
{
	EnemyMove::speed = 1.f;
	EnemyMove::nextSpeedBoost = 21.f;
}

void EnemyMove::Move(std::vector<Enemy>* listEnemy, int windowX,bool& lose)
{
	
	for (size_t i = 0; i < listEnemy->size(); i++)
	{
		(*listEnemy)[i].enemySprite.move(speed, 0);

	}
	for (size_t i = 0; i < listEnemy->size(); i++)
	{
		if ((*listEnemy)[i].enemySprite.getPosition().y >= 400)
		{
			lose = true;
			break;
		}
		if ((*listEnemy)[i].enemySprite.getPosition().x >= windowX - 50 || (*listEnemy)[i].enemySprite.getPosition().x <= 10) {
			speed = -speed;
			for (size_t i = 0; i < listEnemy->size(); i++)
			{
				(*listEnemy)[i].enemySprite.move(0.f, 10);
				(*listEnemy)[i].enemySprite.move(speed, 0);
			}
			break;
		}
	}
	if (listEnemy->size() <= nextSpeedBoost)
	{

		speed = speed *1.3;
		nextSpeedBoost -= 3;
	}
}
