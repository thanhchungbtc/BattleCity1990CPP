#ifndef GUARD_COLLISION_H
#define GUARD_COLLISION_H

#include "SDL.h"
#include "Vector2D.h"

static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
	if((A->y + A->h) <= B->y )  { return false; }

	if(A->y  >= (B->y + B->h) )  { return false; }

	if((A->x + A->w) <= B->x ) { return false; }

	if(A->x >= (B->x + B->w))  { return false; }

	return true;
}
static bool RectOnRect(SDL_Rect* A, SDL_Rect* B) // B is inside A
{
	if (B->x + B->w > A->x && B->x + B->w < A->x + A->w &&
		B->y + B->h > A->y && B->y + B->h < A->y + A->h)
	{
		return true;
	}
	if (B->x + B->w > A->x && B->x + B->w < A->x + A->w &&
		B->y > A->y && B->y < A->y + A->h)
	{
		return true;
	}
	if (B->x > A->x && B->x < A->x + A->w &&
		B->y > A->y && B->y < A->y + A->h)
	{
		return true;
	}
	if (B->x > A->x && B->x < A->x + A->w &&
		B->y > A->y && B->y < A->y + A->h)
	{
		return true;
	}
	return false;
}
#endif // !GUARD_COLLISION_H
