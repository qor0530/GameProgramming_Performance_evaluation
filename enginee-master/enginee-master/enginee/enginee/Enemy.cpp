#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Animation.h"
Enemy::Enemy() :
	target(nullptr)
{
}

Enemy::~Enemy()
{
}

void Enemy::Awake()
{
	name = "Enemy";
	sortingLayer = 1;
	animation->SetAnimation("Enemy1");

	target = static_cast<Player*>(GameObject::Find("Player"));
}

void Enemy::OnDestroy()
{
	PlaySound(L"./Resource/Sound/Die.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void Enemy::Update()
{
	target = static_cast<Player*>(GameObject::Find("Player"));

	if (target == nullptr)
	{
		return;
	}
	auto diff = target->position - position;
	D3DXVECTOR2 result = { 0.0f, 0.0f };
	D3DXVec2Normalize(&result, &diff);
	position += result * 5.0f;
}