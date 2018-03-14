#include "Track.h"

Track::Track(sf::Vector2f trackOrigin, float trackWidth, float trackHeight)
{
	currentSegment = 0;

	this->trackOrigin = trackOrigin;
	this->trackWidth = trackWidth;
	this->trackHeight = trackHeight;

	track.push_back(RoadSegment(trackOrigin, trackWidth, trackHeight, 0, 100));
}

void Track::addSection(int numSegments, int curve, int hill)
{
	// throttles curve values to be between -100 and 100
	if (curve > 100)
		curve = 100;
	else if (curve < -100)
		curve = -100;

	// creates smooth curves. no jagged edges
	float currentCurve = (*(track.end() - 1)).getCurve();
	float curveStep;

	if (currentCurve < curve)
		curveStep = (curve - currentCurve) / (numSegments / 3);
	else if (currentCurve > curve)
		curveStep = (curve - currentCurve) / (numSegments / 3);
	else
		curveStep = 0;

	for (int i = 0; i < numSegments; i++)
	{
		
		if ((*(track.end() - 1)).getCurve() < curve)
		{
			currentCurve += curveStep;
			track.push_back(RoadSegment(currentCurve, hill));
			(*(track.end() - 1)).updatePosition((*(track.end() - 2)));
		}
		else if ((*(track.end() - 1)).getCurve() > curve)
		{
			currentCurve += curveStep;
			track.push_back(RoadSegment(currentCurve, hill));
			(*(track.end() - 1)).updatePosition((*(track.end() - 2)));
		}
		else
		{
			track.push_back(RoadSegment(currentCurve, hill));
			(*(track.end() - 1)).updatePosition((*(track.end() - 2)));
		}

	}

}

void Track::draw(sf::RenderWindow* window)
{
	// draws road segments from the back to the front, for depth purposes
	for (iter = track.begin() + currentSegment + NUM_DRAW_SEGMENTS; iter > track.begin() + currentSegment; iter--)
	{
		(*iter).draw(window);
	}
}

void Track::advance()
{
	currentSegment++;

	(*(track.begin() + currentSegment)).copyPosition((*(track.begin() + currentSegment - 1)));

	// makes the first 10 track segments visible even if they are below the horizon
	for (int i = 0; i < 10; i++)
	{
		float viewHeight = track[currentSegment + i].getHill() - 100;
		viewHeight *= i * (1.0 / 10.0);
		viewHeight += 100;
		track[currentSegment + i].setHill(viewHeight);
	}

	// recalculates the global positions of all RoadSegments based on the new current segment
	for (iter = track.begin() + currentSegment; iter < track.begin() + currentSegment + NUM_DRAW_SEGMENTS + 1; iter++)
	{
		(*(iter + 1)).updatePosition((*iter));
	}
}

float Track::getTrackHeight()
{
	return track[currentSegment + NUM_DRAW_SEGMENTS].getSegmentHighestPoint();
}

float Track::getCurrentCurve()
{
	return track[currentSegment + 10].getCurve();
}
