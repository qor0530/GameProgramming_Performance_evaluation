#include "stdafx.h"
#include "Player.h"
#include "Animation.h"
#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Bullet.h"
#include "GraphicManager.h"
Player::Player() :
	deadTime(3000), isFlip(false)
{
}

Player::~Player()
{
}

void Player::Awake()
{
	name = "Player";
	animation->SetAnimation("TestAnimation");
	position = { 0.0f, 0.0f };
	sortingLayer = 1;
}

void Player::Update()
{
	PlayerMove();
	MouseInput();
}
void Player::LateUpdate()
{
	CameraMove();
}

void Player::OnRender()
{
	GraphicManager::RenderText("Player", position);
}

void Player::OnCollisionEnter(GameObject* gameObject)
{
	if (gameObject->name == "Enemy")
	{
		this->isActive = false;
		Camera::AddShake(10.5f);
		if (clock() > deadTime)
		{
			this->isActive = true;
		}
	}
}

void Player::OnDestroy()
{
	GameManager::nowScene->nextSceneName = "Stage1";
}

void Player::PlayerMove()
{
	if (InputManager::GetKey(InputManager::KeyCode::W))
	{
		position.y -= 5.0f;
	}
	if (InputManager::GetKey(InputManager::KeyCode::A))
	{
		position.x -= 5.0f;
	}
	if (InputManager::GetKey(InputManager::KeyCode::S))
	{
		position.y += 5.0f;
	}
	if (InputManager::GetKey(InputManager::KeyCode::D))
	{
		position.x += 5.0f;
	}

	//position = InputManager::mousePosistion;
}

void Player::CameraMove()
{
	auto diff = position - Camera::position;

	Camera::position += diff * 0.05f;
}

void Player::MouseInput()
{
	auto mousePosition = InputManager::mousePosistion;

	auto diff = mousePosition - position;

	auto radian = atan2(diff.y, diff.x);

	degree = D3DXToDegree(radian);

	auto flipedScale = -scale.y;
	if (mousePosition.x < 0 && isFlip == true)
	{
		scale.y = scale.y;
		isFlip = false;
	}
	else if (mousePosition.x > 0)
	{
		scale.y = flipedScale;
		isFlip = true;
	}
	D3DXVECTOR2 normal;

	D3DXVec2Normalize(&normal, &diff);

	if (InputManager::GetKeyDown(InputManager::KeyCode::L_mouse))
	{
		auto bullet = Instantiate<Bullet>(position);
		if (bullet != nullptr)
		{
			bullet->SetOption(normal, 10.0f);
		}
	}
}