#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	frameWidth = texture->getSize().x / float(imageCount.x);
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.size.x = frameWidth;
	uvRect.size.y = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime, bool flipped)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.position.x = currentImage.x * frameWidth;
	uvRect.position.y = currentImage.y * uvRect.size.y;

	if (flipped) {
		uvRect.position.x += frameWidth;
		uvRect.size.x = -frameWidth;
	}

	else {
		uvRect.size.x = frameWidth;
	}
}