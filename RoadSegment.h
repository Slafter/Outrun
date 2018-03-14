#include <SFML/Graphics.hpp>

class RoadSegment
{
public:
	const float DISTANCE_SCALAR = 0.92;
	const float CURVE_CONVERSION = 0.0004;
	const float HILL_CONVERSION = 0.01;

public:
	RoadSegment(sf::Vector2f origin, float width, float height, int curve, int hill);
	RoadSegment(int curve, int hill);
	void updatePosition(RoadSegment sourceSegment);
	void copyPosition(RoadSegment sourceSegment);
	void draw(sf::RenderWindow* window);
	int getCurve();
	float getHill();
	void setHill(float hill);
	float getSegmentHighestPoint();

private:
	static int numSegments;
	sf::Vector2f origin;
	float baseHeight;
	float visualHeight;
	float baseWidth;
	float curve;
	float hill;
	static sf::Texture treeTexture;
	sf::RectangleShape tree;
	bool hasTree;

	sf::ConvexShape road;
	sf::ConvexShape rumbleLeft;
	sf::ConvexShape rumbleRight;
	sf::ConvexShape grass;

};