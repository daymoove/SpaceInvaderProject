#include "Player.h";

Player::Player()
{
	Player::hp = 3;
}

void Player::PlayerMovement(float& changeX, int windowsizex,int spriteX) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (spriteX -5.f < 0) {
			changeX = 0;
		}
		else {
			changeX = -5;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (spriteX + 50.f > windowsizex) {
			changeX = 0;
		}
		else {
			changeX = 5;
		}
	}

}

int Player::GetHP()
{
	return hp;
}

void Player::SetHP(int newHp)
{
	hp = newHp;
}

