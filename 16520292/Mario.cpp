#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "PlayScence.h"

CMario::CMario(float x, float y) : CGameObject()
{
	vx = 0.1f;
	vy = 0.1f;
	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	x += vx * dt;
	y += vy * dt;
	int RAND = rand() & 1 ? -1 : 1;
	int RAND1 = rand() & 1 ? -1 : 1;

	int BackBufferWidth = 500;
	int BackBufferHeight = 500;

	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH || y <= 0 || y >= BackBufferHeight - MARIO_HEIGHT) {
	
		vx = RAND * vx;
		vy = RAND1 * vy;

		if (dynamic_cast<CPlayScene*>(CGame::GetInstance()
			->GetCurrentScene())->getObjectSize() < 32) 
		{
			CAnimationSets* animation_sets = CAnimationSets::GetInstance();
			CGameObject* obj = new CMario(x, y);
			LPANIMATION_SET ani_set = animation_sets->Get(1);
			obj->SetAnimationSet(ani_set);
			obj->SetPosition(this->x, this->y);
			obj->SetSpeed(-vx, -vy);
			dynamic_cast<CPlayScene*> (
				CGame::GetInstance()
				->GetCurrentScene()
				)->AddObject(obj);
		}
		if (x <= 0)
		{
			x = 0;
		}
		else if (y <= 0) {
			y = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
		else if (y >= BackBufferHeight - MARIO_HEIGHT) {
			y = (float)(BackBufferWidth - MARIO_HEIGHT);
		}
	}
	CGameObject::Update(dt);
}

void CMario::Render()
{
	animation_set->at(0)->Render(x, y, 255);
}

void CMario::SetState(int state)
{
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
}

