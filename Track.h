#include <SFML/Graphics.hpp>
#include <vector>
#include "RoadSegment.h"

class Track
{
public:
	const int NUM_DRAW_SEGMENTS = 85;

public:
	Track(sf::Vector2f trackOrigin, float trackWidth, float trackHeight);
	void addSection(int numSegments, int curve, int hill);
	void draw(sf::RenderWindow* window);
	void advance();
	float getTrackHeight();
	float getCurrentCurve();

private:
	sf::Vector2f trackOrigin;
	float trackWidth;
	float trackHeight;
	std::vector<RoadSegment> track;
	std::vector<RoadSegment>::iterator iter;
	int currentSegment;

};