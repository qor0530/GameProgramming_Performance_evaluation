#pragma once

#include <d3dx9.h>

static class Camera // static 인 클래스는 안에 도 static 이어야한다
{
public:
	Camera();
	~Camera();

	static void Update();

	static int ScreenWidth; // 여기
	static int ScreenHeight; // 여기

	static D3DXVECTOR2 position;
	static D3DXVECTOR2 scale;
	static D3DXMATRIX matrix;
	static float degree;

	static void AddShake(float shake);

	static float shake;
};

