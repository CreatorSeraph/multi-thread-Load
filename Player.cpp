#include "DXUT.h"
#include "Player.h"
#include "Actor.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	Vector3 direction = CAMERA->ViewPos() - CAMERA->CameraPos();
	D3DXVec3Normalize(&direction, &direction);

	float f_angle = atan2f(direction.y, direction.x);

	float x = cosf(f_angle);
	float y = sinf(f_angle);

	if (KEYPRESS('W'))
	{
		GetActor()->GetTransform()->Translate(direction * 10);
	}
	if (KEYPRESS('S'))
	{

	}
	if (KEYPRESS('A'))
	{

	}
	if (KEYPRESS('D'))
	{

	}


}

void Player::Destroy()
{
}
