#include "GenerationData.h"

bool LevelLayout::ProposeNewPoint(glm::ivec2 newPoint)
{
	// Point isn't suitable if it already exists in the layout
	bool samePoint = false;
	for (auto r : layoutRooms)
	{
		if (r->GetRoomPos() == newPoint)
		{
			samePoint = true;
			break;
		}
	}
	if (samePoint)
		return false;


	// Point isn't suitable if it would create a 4 connection room (on itself or any of it's connected rooms)
	std::vector<LevelRoom*> connectedRooms = GetConnectedRoomsAtPoint(newPoint);
	// Checking self
	if (connectedRooms.size() == 4)
	{
		return false;
	}
	// Checking Connections on others
	for (auto a : connectedRooms)
	{
		if (a->GetNumberOfConnections() >= 3)
		{
			return false;
		}
	}


	// Point isn't suitable if it would create a 2 x 2 set of rooms
	// 4 Test Scenarios
	// Newpoint is top left
	if (CreatesSquare(newPoint + glm::ivec2(0, 0), newPoint))
		return false;
	// Newpoint is top right
	if (CreatesSquare(newPoint + glm::ivec2(-1, 0), newPoint))
		return false;
	// Newpoint is bottom left
	if (CreatesSquare(newPoint + glm::ivec2(0, 1), newPoint))
		return false;
	// NewPoint is bottom right
	if (CreatesSquare(newPoint + glm::ivec2(-1, 1), newPoint))
		return false;


	// Otherwise point is suitable and can be added to layout
	return true;
}

void LevelLayout::AddRoom(glm::ivec2 newRoomPoint)
{
	LevelRoom* newRoom = new LevelRoom();
	newRoom->SetRoomPos(newRoomPoint);

	// Getting all the nearby rooms
	std::vector<LevelRoom*> connectedRooms = GetConnectedRoomsAtPoint(newRoomPoint);
	for (auto& a : connectedRooms)
	{
		// Setting own connection data
		glm::ivec2 roomDirection = newRoomPoint - a->GetRoomPos();
		Directions newDirection = DirectionsUtility::ConvertVectorToDirection(roomDirection);
		newRoom->AddConnection(newDirection);


		// Also add self as connection of other room
		Directions oppositeDirection = DirectionsUtility::GetOppositeDirection(newDirection);
		a->AddConnection(oppositeDirection);


		// Connection data to be stored for door generation
		glm::vec2 doorPosition = (newRoomPoint + a->GetRoomPos());
		doorPosition /= 2;
		bool doorToBeRotated = (newDirection == Directions::UP || newDirection == Directions::DOWN) ? true : false;
		std::tuple<glm::vec2, bool> newDoorData = std::tuple<glm::vec2, bool>
		{
			doorPosition,
			doorToBeRotated
		};
		if (!Utility::VectorContains(newDoorData, layoutDoors))
		{
			layoutDoors.push_back(newDoorData);
		}
	}

	layoutRooms.push_back(newRoom);
}


/*
========================================================================================================================================================================================================
Generation Room Adjacency Checking
========================================================================================================================================================================================================
*/
std::vector<LevelRoom*> LevelLayout::GetConnectedRoomsAtPoint(glm::ivec2 point)
{
	std::vector<LevelRoom*> pointConnections;

	for (auto r : layoutRooms)
	{
		if (IsPointConnected(point, r->GetRoomPos()))
		{
			// Gets the direction between the two points
			pointConnections.push_back(r);
		}
	}

	return pointConnections;
}

std::vector<Directions> LevelLayout::GetConnectionDirectionsAtPoint(glm::ivec2 point)
{
	std::vector<Directions> pointConnections;

	for (auto r : layoutRooms)
	{
		if (IsPointConnected(point, r->GetRoomPos()))
		{
			// Gets the direction between the two points
			pointConnections.push_back(DirectionsUtility::ConvertVectorToDirection(r->GetRoomPos() - point));
		}
	}

	return pointConnections;
}

bool LevelLayout::IsPointConnected(glm::ivec2 p1, glm::ivec2 p2)
{
	glm::ivec2 direction = p2 - p1;

	if (std::abs(direction.x) + std::abs(direction.y) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LevelLayout::CreatesSquare(glm::ivec2 topLeftPoint, glm::ivec2 newPoint)
{
	// Top left
	bool topLeftFound = false;
	for (auto r : layoutRooms)
	{
		glm::ivec2 topleft = topLeftPoint + glm::ivec2(0, 0);
		if (r->GetRoomPos() == (topleft) || newPoint == topleft)
		{
			topLeftFound = true;
		}
	}

	// Top Right
	bool topRightFound = false;
	for (auto r : layoutRooms)
	{
		glm::ivec2 topRight = topLeftPoint + glm::ivec2(1, 0);
		if (r->GetRoomPos() == (topRight) || newPoint == topRight)
		{
			topRightFound = true;
		}
	}

	// Bottom Left
	bool bottomLeftFound = false;
	for (auto r : layoutRooms)
	{
		glm::ivec2 bottomLeft = topLeftPoint + glm::ivec2(0, -1);
		if (r->GetRoomPos() == (bottomLeft) || newPoint == bottomLeft)
		{
			bottomLeftFound = true;
		}
	}

	// Bottom Right
	bool bottomRightFound = false;
	for (auto r : layoutRooms)
	{
		glm::ivec2 bottomRight = topLeftPoint + glm::ivec2(1, -1);
		if (r->GetRoomPos() == (bottomRight) || newPoint == bottomRight)
		{
			bottomRightFound = true;
		}
	}


	if (topLeftFound && topRightFound && bottomLeftFound && bottomRightFound)
	{
		return true;
	}
	else
	{
		return false;
	}
}