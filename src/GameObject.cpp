#include "GameObject.h"
#include "Utilities.h"
#include "BinaryMap.h"


enum class STATE
{
	NONE,
	GOING_LEFT,
	GOING_RIGHT,
	GOING_UP,
	GOING_DOWN
};

enum class INNER_STATE
{
	ENTER,
	UPDATE,
	EXIT
};

GameObjectInst* sGameObjectInstList;
GameObject* sGameObjectList;
unsigned int sGameObjectNum;
unsigned int GAME_OBJECT_INST_NUM_MAX = 200; // Max amount of Object

GameObject::GameObject() : type{ TYPE_OBJECT::EMPTY } , pos { 0, 0 }
{

}

GameObjectInst::GameObjectInst() : pObject{ nullptr }, flag {0}, scale {0}, posCurr {0}, velCurr {0}, dirCurr {0},
transform {0}, gridCollisionFlag {0}, pUserData { nullptr }, state {STATE::NONE}, innerState {INNER_STATE::ENTER},
counter {0}
{

}

GameObjectInst* gameObjInstCreate(unsigned int type, float scale,
	AEVec2* pPos, AEVec2* pVel,
	float dir, enum class STATE startState)
{
	AEVec2 zero;
	AEVec2Zero(&zero);

	AE_ASSERT_PARM(type < sGameObjectNum);

	// loop through the object instance list to find a non-used object instance
	for (unsigned int i = 0; i < GAME_OBJECT_INST_NUM_MAX; i++)
	{
		GameObjectInst* pInst = sGameObjectInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjectList + type;
			pInst->flag = FLAG_ACTIVE | FLAG_VISIBLE;
			pInst->scale = scale;
			pInst->posCurr = pPos ? *pPos : zero;
			pInst->velCurr = pVel ? *pVel : zero;
			pInst->dirCurr = dir;
			pInst->pUserData = 0;
			pInst->gridCollisionFlag = 0;
			pInst->state = startState;
			pInst->innerState = INNER_STATE_ON_ENTER;
			pInst->counter = 0;

			// return the newly created instance
			return pInst;
		}
	}

	return 0;
}