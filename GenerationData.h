#pragma once
#include "pch.h"
#include "Utility.h"
#include "Directions.h"
#include "RoomTypes.h"

class LevelRoom
{
private:
	glm::ivec2 roomPos;
	
	std::vector<Directions> connectionDirections;
	std::vector<LevelRoom*> connectedRooms;

	RoomTypes roomType = RoomTypes::ROOMTYPE_NORMAL;

public:
	inline glm::ivec2 GetRoomPos() { return roomPos; }
	inline void SetRoomPos(glm::ivec2 newPos) { roomPos = newPos; }

	inline int GetNumberOfConnections() { return connectionDirections.size(); }
	inline std::vector<Directions> GetConnectionDirections() { return connectionDirections; }
	inline std::vector<LevelRoom*> GetConnectedRooms() { return connectedRooms; }

	inline void AddConnection(LevelRoom* connectedRoom, Directions connectionDirection) { connectedRooms.push_back(connectedRoom); connectionDirections.push_back(connectionDirection); }

	void SetRoomType(RoomTypes newRoomType) { roomType = newRoomType; }
	RoomTypes GetRoomType() { return roomType; }
};


class LevelLayout
{
private:
	std::vector<LevelRoom*> layoutRooms;
	std::vector<std::tuple<glm::vec2, bool>> layoutDoors;

public:
	bool ProposeNewPoint(glm::ivec2 newPoint);
	std::vector<LevelRoom*> GetRooms() { return layoutRooms; }
	std::vector<std::tuple<glm::vec2, bool>> GetDoors() { return layoutDoors; }
	void AddRoom(glm::ivec2 newRoomPoint);
	
	std::vector<LevelRoom*> GetConnectedRoomsAtPoint(glm::ivec2 point);
	std::vector<Directions> GetConnectionDirectionsAtPoint(glm::ivec2 point);

	bool IsPointConnected(glm::ivec2 p1, glm::ivec2 p2);

	bool CreatesSquare(glm::ivec2 topLeftPoint, glm::ivec2 newPoint);
};