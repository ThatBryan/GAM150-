// Something something Collision lmao
/******************************************************************************/
/*!
\file		Collision.cpp
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	January 01, 20xx
\brief

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Collision.h"

/**************************************************************************/
/*!

	*/
	/**************************************************************************/
bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2)
{
	/*
	Implement the collision intersection over here.

	The steps are:
	Step 1: Check for static collision detection between rectangles (before moving).
				If the check returns no overlap you continue with the following next steps (dynamics).
				Otherwise you return collision true

	Step 2: Initialize and calculate the new velocity of Vb
			tFirst = 0
			tLast = dt

	Step 3: Working with one dimension (x-axis).
			if(Vb < 0)
				case 1
				case 4
			if(Vb > 0)
				case 2
				case 3

			case 5

	Step 4: Repeat step 3 on the y-axis

	Step 5: Otherwise the rectangles intersect

	*/
	if (!((aabb1.max.x < aabb2.min.x) || (aabb1.min.x > aabb2.max.x) || (aabb1.max.y < aabb2.min.y) || (aabb1.min.y > aabb2.max.y)))
	{
		return TRUE;
	}
	float tFirstx = 0;
	float tFirsty = 0;
	float tLastx = g_dt;
	float tLasty = g_dt;
	AEVec2 Vb;
	Vb.x = vel1.x - vel2.x;
	Vb.y = vel1.y - vel2.y;
	if (Vb.x == 0 || Vb.y == 0)
	{
		return FALSE;
	}
	if (Vb.x < 0)
	{
		// case 1
		if (aabb1.min.x > aabb2.max.x)
		{
			return FALSE;
		}
		// case 4.1
		if (aabb1.max.x < aabb2.min.x)
		{
			tFirstx = max(((aabb1.max.x - aabb2.min.x) / Vb.x), tFirstx);
		}
		// case 4.2
		if (aabb1.min.x < aabb2.max.x)
		{
			tLastx = min(((aabb1.min.x - aabb2.max.x) / Vb.x), tLastx);
		}
	}
	if (Vb.x > 0)
	{
		// case 2.1
		if (aabb1.min.x > aabb2.max.x)
		{
			tFirstx = max(((aabb1.min.x - aabb2.max.x) / Vb.x), tFirstx);
		}
		// case 2.2
		if (aabb1.max.x > aabb2.min.x)
		{
			tLastx = min(((aabb1.max.x - aabb2.min.x) / Vb.x), tLastx);
		}
		// case 3
		if (aabb1.max.x < aabb2.min.x)
		{
			return FALSE;
		}
	}
	if (tFirstx > tLastx)
	{
		return FALSE;
	}
	if (Vb.y < 0)
	{
		// case 1
		if (aabb1.min.y > aabb2.max.y)
		{
			return FALSE;
		}
		// case 4.1
		if (aabb1.max.y < aabb2.min.y)
		{
			tFirsty = max(((aabb1.max.y - aabb2.min.y) / Vb.y), tFirsty);
		}
		// case 4.2
		if (aabb1.min.y < aabb2.max.y)
		{
			tLasty = min(((aabb1.min.y - aabb2.max.y) / Vb.y), tLasty);
		}
	}
	if (Vb.y > 0)
	{
		// case 2.1
		if (aabb1.min.y > aabb2.max.y)
		{
			tFirsty = max(((aabb1.min.y - aabb2.max.y) / Vb.y), tFirsty);
		}
		// case 2.2
		if (aabb1.max.y > aabb2.min.y)
		{
			tLasty = min(((aabb1.max.y - aabb2.min.y) / Vb.y), tLasty);
		}
		// case 3
		if (aabb1.max.y < aabb2.min.y)
		{
			return FALSE;
		}
	}

	if (tFirsty > tLasty)
	{
		return FALSE;
	}
	else if ((tFirstx > tLasty) || (tFirsty > tLastx))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}