#pragma once
#include "Enemy.h"

class EnemyMove
{
public:
	EnemyMove();

	void Move(std::vector<Enemy>* Enemy, int windowX,bool& lose);
	float nextSpeedBoost;
	float speed;
	

private:

};