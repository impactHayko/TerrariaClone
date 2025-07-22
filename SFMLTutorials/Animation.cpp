#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.size.x = texture->getSize().x / float(imageCount.x);
	uvRect.size.y = texture->getSize().y / float(imageCount.y);
}



Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime)
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

	uvRect.position.x = currentImage.x * uvRect.size.x;
	uvRect.position.y = currentImage.y * uvRect.size.y;
}