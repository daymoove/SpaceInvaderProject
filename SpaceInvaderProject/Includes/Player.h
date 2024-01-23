#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void PlayerMovement(float& changeX, int windowsizex,int spriteX);
	int GetHP();
	void SetHP(int newHp);

private:
	int hp;
};