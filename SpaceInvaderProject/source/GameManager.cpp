#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
	GameManager::changeX = 0;
	GameManager::bulletCooldown.getElapsedTime();
	GameManager::EnemyCooldown.getElapsedTime();
	GameManager::enemyTimer = 0.6f;
	GameManager::drawBullet = false;
	GameManager::shootBullet = true;
	GameManager::shootEnemyBullet = true;
	GameManager::randomEnemy = 0;
	GameManager::drawEnemyBullet = false;
	GameManager::winOrLose = false;
	GameManager::score = 0;
	GameManager::lose = false;
	GameManager::startGame = false;
}


void GameManager::Run()
{
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Simple 2D Game");
	window.setFramerateLimit(60);
	sf::Font font;
	sf::Text textScore;
	sf::Text startText;
	sf::Text textLifePlayer;
	sf::Text Title;
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("sprites\\mec_qui_tire.png"))
	{
	}
	sf::Sprite playerSprite(playerTexture);
	playerSprite.setPosition(500.f, 500.f);


	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("sprites\\closed.png"))
	{
	}
	SpawnEnemy(enemyTexture);

	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("sprites\\bullet.png"))
	{
	}
	Bullet bullet(bulletTexture);
	Bullet enemyBullet(bulletTexture);
	if (!font.loadFromFile("arial.ttf"))
	{
	}
	textScore.setFont(font);
	textScore.setString("Score: " + std::to_string(score));
	textLifePlayer.setFont(font);
	textLifePlayer.setString("Life: " + std::to_string(player.GetHP()));
	textLifePlayer.setPosition(windowX - textLifePlayer.getGlobalBounds().width-10, 0);
	startText.setFont(font);
	startText.setString("Press space bar to start");
	startText.setCharacterSize(24);
	startText.setPosition(windowX / 2 - startText.getGlobalBounds().width / 2, 400);
	Title.setFont(font);
	Title.setString("L'invasion d'lespace");
	Title.setFillColor(sf::Color::Green);
	Title.setCharacterSize(48);
	Title.setPosition(windowX / 2 - Title.getGlobalBounds().width / 2, 0);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
			if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::D) {
				player.PlayerMovement(changeX, window.getSize().x, playerSprite.getPosition().x);
				playerSprite.move(changeX, 0);
			}
			if (shootBullet)
			{
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Space && startGame)
					{
						bullet.bulletSprite.setPosition(playerSprite.getPosition().x + 24, playerSprite.getPosition().y);
						drawBullet = true;
						shootBullet = false;
					}
					else if (event.key.code == sf::Keyboard::Space && !startGame)
					{
						startGame = !startGame;
					}
				}
			}
		}
		if (startGame)
		{
			if (drawBullet)
			{

				bullet.bulletSprite.move(0.f, -10.f);
				for (size_t j = 0; j < listEnemy.size(); j++)
				{
					if (bullet.bulletSprite.getGlobalBounds().intersects(listEnemy[j].enemySprite.getGlobalBounds()))
					{
						listEnemy.erase(listEnemy.begin() + j);
						shootBullet = true;
						drawBullet = false;
						score += 10;
						textScore.setString("Score: " + std::to_string(score));
						break;
					}
				}
				if (bullet.bulletSprite.getPosition().y < -10)
				{
					shootBullet = true;
					drawBullet = false;
				}
			}

			if (shootEnemyBullet && listEnemy.size() > 0)
			{
				randomEnemy = std::rand() % listEnemy.size();
				sf::Vector2f randNumPos = listEnemy[randomEnemy].enemySprite.getPosition();
				for (size_t i = 0; i < listEnemy.size(); i++)
				{
					if (listEnemy[i].enemySprite.getPosition().x == randNumPos.x && listEnemy[i].enemySprite.getPosition().y > randNumPos.y)
					{
						randomEnemy = i;
					}
				}
				enemyBullet.bulletSprite.setPosition(listEnemy[randomEnemy].enemySprite.getPosition().x,
					listEnemy[randomEnemy].enemySprite.getPosition().y);
				shootEnemyBullet = false;
				drawEnemyBullet = true;
			}

			if (drawEnemyBullet)
			{
				enemyBullet.bulletSprite.move(0.f, 5.f);
				if (enemyBullet.bulletSprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds()))
				{
					player.SetHP(player.GetHP() - 1);
					shootEnemyBullet = true;
					drawEnemyBullet = false;
					textLifePlayer.setString("Life: " + std::to_string(player.GetHP()));
				}
				if (enemyBullet.bulletSprite.getPosition().y > windowY)
				{
					shootEnemyBullet = true;
					drawEnemyBullet = false;
				}
			}

			if (listEnemy.size() > 0)
			{
				enemyMove.Move(&listEnemy, windowX, lose);
				if (lose)
				{
					window.close();
					EndMenu(winOrLose);
				}
				for (Enemy enemySprite : listEnemy)
				{
					window.draw(enemySprite.enemySprite);
				}
			}
			else
			{
				window.close();
				winOrLose = true;
				EndMenu(winOrLose);
			}
			if (player.GetHP() > 0)
			{
				window.draw(playerSprite);
			}
			else
			{
				window.close();
				EndMenu(winOrLose);
			}
			if (drawBullet)
			{
				window.draw(bullet.bulletSprite);
			}
			if (drawEnemyBullet)
			{
				window.draw(enemyBullet.bulletSprite);
			}
			window.draw(textLifePlayer);
			window.draw(textScore);
		}
		else
		{
			window.draw(Title);
			window.draw(startText);
		}
		
		window.display();
	}
}

void GameManager::SpawnEnemy(sf::Texture& enemyTexture) {
	float enemyPositionX = 10;
	float enemyPositionY = 40;
	for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			sf::Sprite enemySprite(enemyTexture);
			
			enemySprite.setPosition(enemyPositionX, enemyPositionY);
			Enemy enemy(enemySprite);
			this->listEnemy.push_back(enemy);
			enemyPositionX += 80;
		}
		enemyPositionY += 50;
		enemyPositionX = 10;
	}
}

void GameManager::EndMenu(bool winOrLose)
{
	sf::RenderWindow windowEndMenu(sf::VideoMode(windowX, windowY), "Simple 2D Game");
	windowEndMenu.setFramerateLimit(60);
	sf::Text textEnd;
	sf::Text textRestart;
	sf::Text textScore;
	sf::Font font;
	sf::Clock textCooldown;
	textCooldown.getElapsedTime();
	if (!font.loadFromFile("arial.ttf"))
	{
	}
	textEnd.setFont(font);
	textRestart.setFont(font);
	textScore.setFont(font);
	if (winOrLose)
	{
		textEnd.setString("You WIN");
	}
	else 
	{
		textEnd.setString("You LOSE");
	}
	textEnd.setCharacterSize(48);
	textEnd.setPosition(windowX / 2 - textEnd.getGlobalBounds().width/2, 0);
	textRestart.setString("Press R to restart");
	textRestart.setCharacterSize(24);
	textRestart.setPosition(windowX / 2 - textRestart.getGlobalBounds().width / 2, 400);
	textScore.setString("Score: " + std::to_string(score));
	textScore.setCharacterSize(32);
	textScore.setPosition(windowX / 2 - textScore.getGlobalBounds().width / 2, 200);


	while (windowEndMenu.isOpen())
	{
		windowEndMenu.clear(sf::Color::Black);

		while (windowEndMenu.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				windowEndMenu.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					windowEndMenu.close();
				}
				if (event.key.code == sf::Keyboard::R)
				{
					windowEndMenu.close();
					score = 0;
					player.SetHP(3);
					listEnemy.clear();
					enemyMove.nextSpeedBoost = 21.f;
					enemyMove.speed = 1.f;
					lose = false;
					winOrLose = false;
					Run();
				}
			}
		}
		if (textCooldown.getElapsedTime().asSeconds() >0.5)
		{
			sf::Color color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
			textRestart.setFillColor(color);
			textCooldown.restart();
		}
		windowEndMenu.draw(textEnd);
		windowEndMenu.draw(textRestart);
		windowEndMenu.draw(textScore);
		windowEndMenu.display();
	}
}
