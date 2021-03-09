#pragma once
#include "AEEngine.h"

class GameObject
{
	public:
		GameObject();
		TYPE_OBJECT type;
		AEVec2 pos;
};

class GameObjectInst
{
	public:
		GameObjectInst();
		GameObject*		pObject;	// pointer to the 'original'
		unsigned int	flag;		// bit flag or-ed together
		float			scale;
		AEVec2			posCurr;	// object current position
		AEVec2			velCurr;	// object current velocity
		float			dirCurr;	// object current direction

		AEMtx33			transform;	// object drawing matrix

		//AABB			boundingBox;// object bouding box that encapsulates the object

		//Used to hold the current 
		int				gridCollisionFlag;

		// pointer to custom data specific for each object type
		void* pUserData;

		//State of the object instance
		enum class		STATE state;
		enum class		INNER_STATE innerState;

		//General purpose counter (This variable will be used for the enemy state machine)
		double			counter;
};

GameObjectInst* gameObjInstCreate(unsigned int type, float scale,
	AEVec2* pPos, AEVec2* pVel,
	float dir, enum class STATE startState);