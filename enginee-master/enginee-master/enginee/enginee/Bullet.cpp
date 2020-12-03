#include "stdafx.h"
#include "Bullet.h"
#include "Animation.h"
#include "Camera.h"

Bullet::Bullet():
	direction({0.0f, 0.0f}),
	speed(0.0f),
	spawnTime(clock()),
	aliveTime(3000)
{
}


Bullet::~Bullet()
{
}

void Bullet::Awake()
{
	animation->SetAnimation("Bullet");
}

void Bullet::Update()
{
	position += direction*speed;

	if (clock() - spawnTime > aliveTime)
	{
		isActive = false;
	}
}

void Bullet::OnCollisionEnter(GameObject * gameObject)
{
	if (gameObject->name == "Enemy")
	{
		gameObject->isActive = false;
		this->isActive = false;
		Camera::AddShake(10.5f);
	}

}

void Bullet::SetOption(D3DXVECTOR2 direction, float speed)
{
	degree = D3DXToDegree(atan2(direction.y, direction.x));
	this->direction = direction;
	this->speed = speed;
}
