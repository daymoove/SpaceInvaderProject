#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture) {
	Bullet::bulletSprite.setTexture(texture);
	Bullet::bulletRect = bulletSprite.getGlobalBounds();
}