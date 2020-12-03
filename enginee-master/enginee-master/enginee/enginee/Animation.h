#pragma once

#include <d3dx9.h>
#include <ctime>
#include <string>

class GameObject;

class Animation
{
public:
	
	std::string textureName;

	GameObject *parent;

	D3DXVECTOR2 imageSize;
	D3DXVECTOR2 frameSize;
	D3DXVECTOR2 nowFrame;

	clock_t lastChangeTime;
	clock_t timePerFrame;

	void Update();
	void SetAnimation(std::string textureName);
	RECT GetRect();
	Animation();
	~Animation();
};

