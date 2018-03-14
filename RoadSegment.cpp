#include "RoadSegment.h"

int RoadSegment::numSegments = 0;
sf::Texture RoadSegment::treeTexture;

RoadSegment::RoadSegment(sf::Vector2f origin, float width, float height, int curve, int hill)
	: road(4),
	rumbleLeft(4),
	rumbleRight(4),
	grass(4)
{
	if (RoadSegment::numSegments == 0)
		treeTexture.loadFromFile("resources/tree.png");

	tree.setTexture(&treeTexture);
	hasTree = false;

	RoadSegment::numSegments++;

	baseWidth = width;
	baseHeight = height;
	this->curve = curve * CURVE_CONVERSION;
	this->hill = hill * HILL_CONVERSION;
	float halfWidth = width / 2.0;
	float rumbleWidth = width / 10.0;

	road.setPoint(0, sf::Vector2f(origin.x - halfWidth, origin.y));
	road.setPoint(1, sf::Vector2f(origin.x - (halfWidth * DISTANCE_SCALAR), origin.y - (baseHeight * this->hill)));
	road.setPoint(2, sf::Vector2f(origin.x + (halfWidth * DISTANCE_SCALAR), origin.y - (baseHeight * this->hill)));
	road.setPoint(3, sf::Vector2f(origin.x + halfWidth, origin.y));

	float curveOffset = road.getPoint(1).x * curve;

	road.setPoint(1, sf::Vector2f(curveOffset + road.getPoint(1).x, road.getPoint(1).y));
	road.setPoint(2, sf::Vector2f(curveOffset + road.getPoint(2).x, road.getPoint(2).y));

	rumbleLeft.setPoint(0, sf::Vector2f(road.getPoint(0).x - rumbleWidth, road.getPoint(0).y));
	rumbleLeft.setPoint(1, sf::Vector2f(road.getPoint(1).x - (rumbleWidth * DISTANCE_SCALAR), road.getPoint(1).y));
	rumbleLeft.setPoint(2, road.getPoint(1));
	rumbleLeft.setPoint(3, road.getPoint(0));

	rumbleRight.setPoint(3, sf::Vector2f(road.getPoint(3).x + rumbleWidth, road.getPoint(3).y));
	rumbleRight.setPoint(2, sf::Vector2f(road.getPoint(2).x + (rumbleWidth * DISTANCE_SCALAR), road.getPoint(2).y));
	rumbleRight.setPoint(1, road.getPoint(2));
	rumbleRight.setPoint(0, road.getPoint(3));

	grass.setPoint(0, sf::Vector2f(origin.x - 9000.0, origin.y));
	grass.setPoint(1, sf::Vector2f(origin.x - 9000.0, origin.y - (baseHeight * DISTANCE_SCALAR)));
	grass.setPoint(2, sf::Vector2f(origin.x + 9000.0, origin.y - (baseHeight * DISTANCE_SCALAR)));
	grass.setPoint(3, sf::Vector2f(origin.x + 9000.0, origin.y));

	if (RoadSegment::numSegments % 2 == 0)
	{
		road.setFillColor(sf::Color(100, 100, 100));
		rumbleLeft.setFillColor(sf::Color(255, 0, 0));
		rumbleRight.setFillColor(sf::Color(255, 255, 255));
	}
	else
	{
		road.setFillColor(sf::Color(100, 100, 100));
		rumbleLeft.setFillColor(sf::Color(255, 255, 255));
		rumbleRight.setFillColor(sf::Color(255, 0, 0));
	}

	grass.setFillColor(sf::Color::Green);

	tree.setSize(sf::Vector2f(726, 798));
	tree.setPosition(sf::Vector2f(origin.x + (baseWidth * 2), origin.y));

}

RoadSegment::RoadSegment(int curve, int hill)
	: road(4),
	rumbleLeft(4),
	rumbleRight(4),
	grass(4)
{
	RoadSegment::numSegments++;
	hasTree = false;

	this->curve = curve * CURVE_CONVERSION;
	this->hill = hill * HILL_CONVERSION;

	if (RoadSegment::numSegments % 2 == 0)
	{
		road.setFillColor(sf::Color(100, 100, 100));
		rumbleLeft.setFillColor(sf::Color(255, 0, 0));
		rumbleRight.setFillColor(sf::Color(255, 255, 255));
		grass.setFillColor(sf::Color(0, 150, 0));
	}
	else
	{
		road.setFillColor(sf::Color(97, 97, 97));
		rumbleLeft.setFillColor(sf::Color(255, 255, 255));
		rumbleRight.setFillColor(sf::Color(255, 0, 0));
		grass.setFillColor(sf::Color(0, 130, 0));
	}

	if (numSegments % 7 == 0)
	{
		hasTree = true;
		tree.setTexture(&treeTexture);
		tree.setSize(sf::Vector2f(726, 798));
		tree.setOrigin(sf::Vector2f(363, 798));
	}
}

void RoadSegment::updatePosition(RoadSegment sourceSegment)
{
	baseWidth = (sourceSegment.road.getPoint(2).x - sourceSegment.road.getPoint(1).x);
	baseHeight = sourceSegment.baseHeight * DISTANCE_SCALAR;
	visualHeight =  baseHeight * hill;
	origin.x = (sourceSegment.road.getPoint(2).x + sourceSegment.road.getPoint(1).x) / 2.0;
	origin.y = sourceSegment.road.getPoint(1).y;
	float halfWidth = baseWidth / 2.0;
	float rumbleWidth = baseWidth / 10.0;

	road.setPoint(0, sf::Vector2f(origin.x - halfWidth, origin.y));
	road.setPoint(1, sf::Vector2f(origin.x - (halfWidth * DISTANCE_SCALAR), origin.y - visualHeight));
	road.setPoint(2, sf::Vector2f(origin.x + (halfWidth * DISTANCE_SCALAR), origin.y - visualHeight));
	road.setPoint(3, sf::Vector2f(origin.x + halfWidth, origin.y));

	float curveOffset;

	if (curve < 0)
		curveOffset = (road.getPoint(1).x + halfWidth) * curve;
	else
		curveOffset = (road.getPoint(1).x - halfWidth) * curve;

	road.setPoint(1, sf::Vector2f(curveOffset + road.getPoint(1).x, road.getPoint(1).y));
	road.setPoint(2, sf::Vector2f(curveOffset + road.getPoint(2).x, road.getPoint(2).y));

	rumbleLeft.setPoint(0, sf::Vector2f(road.getPoint(0).x - rumbleWidth, road.getPoint(0).y));
	rumbleLeft.setPoint(1, sf::Vector2f(road.getPoint(1).x - (rumbleWidth * DISTANCE_SCALAR), road.getPoint(1).y));
	rumbleLeft.setPoint(2, road.getPoint(1));
	rumbleLeft.setPoint(3, road.getPoint(0));

	rumbleRight.setPoint(3, sf::Vector2f(road.getPoint(3).x + rumbleWidth, road.getPoint(3).y));
	rumbleRight.setPoint(2, sf::Vector2f(road.getPoint(2).x + (rumbleWidth * DISTANCE_SCALAR), road.getPoint(2).y));
	rumbleRight.setPoint(1, road.getPoint(2));
	rumbleRight.setPoint(0, road.getPoint(3));

	grass.setPoint(0, sf::Vector2f(origin.x - 9000.0, origin.y));
	grass.setPoint(1, sf::Vector2f(origin.x - 9000.0, origin.y - visualHeight));
	grass.setPoint(2, sf::Vector2f(origin.x + 9000.0, origin.y - visualHeight));
	grass.setPoint(3, sf::Vector2f(origin.x + 9000.0, origin.y));

	if (hasTree)
	{
		tree.setSize(sf::Vector2f(baseWidth / 2.0, baseWidth / 2.0));
		tree.setOrigin(sf::Vector2f(tree.getSize().x / 2.0, tree.getSize().y));
		tree.setPosition(sf::Vector2f(road.getPoint(0).x - (baseWidth / 3.0), road.getPoint(0).y));
	}

}

void RoadSegment::copyPosition(RoadSegment sourceSegment)
{

	for (int i = 0; i < 4; i++)
	{
		road.setPoint(i, sourceSegment.road.getPoint(i));
		rumbleLeft.setPoint(i, sourceSegment.rumbleLeft.getPoint(i));
		rumbleRight.setPoint(i, sourceSegment.rumbleLeft.getPoint(i));
		grass.setPoint(i, sourceSegment.grass.getPoint(i));
		baseHeight = sourceSegment.baseHeight;
	}

}

void RoadSegment::draw(sf::RenderWindow* window)
{
	window->draw(grass);
	window->draw(road);
	window->draw(rumbleLeft);
	window->draw(rumbleRight);
	if (hasTree)
		window->draw(tree);
}

int RoadSegment::getCurve()
{
	return curve / CURVE_CONVERSION;
}

float RoadSegment::getHill()
{
	return hill / HILL_CONVERSION;
}

void RoadSegment::setHill(float hill)
{
	this->hill = hill * HILL_CONVERSION;
}

float RoadSegment::getSegmentHighestPoint()
{
	return road.getPoint(1).y;
}
