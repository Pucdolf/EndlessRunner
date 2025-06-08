/**
 * @file Board.cpp
 * @brief Implementacja klasy Board.
 */

module;
#include "raylib.h"

module BoardModule;
import <array>;
import <vector>;
import <memory>;
import <random>;
import PlayerModule;
import DustModule;
import BatModule;
import PterodactylModule;
import ResourcesModule;
import CollisionHandlingModule;
import ObstacleModule;
import ObstacleFactoryModule;
import ConfigModule;
import ObstacleFactoryModule;

void Board::setDinoTex(const Texture2D& dinoTex) {
	selectedDinoTex = dinoTex;
}

void Board::setDinoFrameCount(int frameCount) {
	selectedDinoFrameCount = frameCount;
}

void Board::setBackgroundType(BackgroundType bgType) {
	currentBgType = bgType;
}

void Board::init(const Texture2D& dinoTex, int windowWidth, int windowHeight) {
	if (selectedDinoTex.id == 0) {
		selectedDinoTex = dinoTex;
		selectedDinoFrameCount = 6;
	}

	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;

	float playerWidth = (static_cast<float>(selectedDinoTex.width) / selectedDinoFrameCount) * Config::PLAYER_SCALE;
	float startX = static_cast<float>(windowWidth - playerWidth) / 2.f;

	player.init(selectedDinoTex, startX, static_cast<float>(windowHeight), Config::PLAYER_SCALE, selectedDinoFrameCount, Config::ANIMATION_UPDATE_TIME);
	Vector2 playerPos = player.getPosition();
	float dustX = playerPos.x - 20;
	float dustY = (windowHeight - 65.f) - (dust.getTexture().height * Config::OBSTACLE_SCALE);
	dust.init(resources.getDustRun(), dustX, dustY, Config::OBSTACLE_SCALE, Config::DUST_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);

	lastObstacleX = static_cast<float>(windowWidth);
	obstacles.clear();
	spawnObstacle(windowHeight);
}

void Board::update(float deltaTime, int windowHeight) {
	this->windowHeight = windowHeight;
	player.update(deltaTime, windowHeight);
	updateObstacles<Obstacle>(deltaTime);
	obstacles.erase(
		std::remove_if(obstacles.begin(), obstacles.end(),
			[](const auto& obs) {return obs->getPositionX() < -200.f; }),
		obstacles.end()
	);

	if (obstacles.empty() || obstacles.back()->getPositionX() < lastObstacleX - getRandomDistance()) {
		spawnObstacle(windowHeight);
	}

	dust.update(deltaTime);

	if (player.isOnGround(windowHeight)) {
		dustSpawnTimer += deltaTime;
		if (dustSpawnTimer >= dustSpawnInterval) {
			spawnDust(windowHeight);
			dustSpawnTimer = 0.f;
		}
	}
}

void Board::draw() const {
	drawObstacles<Obstacle>();
	player.draw();
	dust.draw();
	
}

bool Board::checkLoss() const {
	for (const auto& obstacle : obstacles) {
		if (obstacleCollision(*obstacle, player)) {
			return true;
		}
	}
	return false;
}

const Player& Board::getPlayer() const {
	return player;
}

void Board::spawnDust( int windowHeight) {
	if (!dust.getIsActive()){
		Vector2 playerPos = player.getPosition();
		float dustX = playerPos.x - 20;
		float dustY = (windowHeight - 65.f) - (dust.getTexture().height * Config::OBSTACLE_SCALE);
		dust.init(dust.getTexture(), dustX, dustY, Config::OBSTACLE_SCALE, Config::DUST_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
	}
}

void Board::spawnObstacle( int windowHeight) {
	float startX = lastObstacleX + getRandomDistance();
	float startY = static_cast<float>(windowHeight - 65);
	obstacles.push_back(obstacleFactory.createObstacle(startX, startY, currentBgType));
	lastObstacleX = startX;
}

float Board::getRandomDistance(){
	std::uniform_real_distribution<float> dis(minObstacleDistance, maxObstacleDistance);
	return dis(gen);
}