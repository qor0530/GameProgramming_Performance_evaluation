#pragma once

#include <vector>
#include <d3dx9.h>

class KeyState
{
public:
	int vkCode;
	bool isOn;		//키가 계속 눌리고 있을때
	bool isDown;	//키가 한번 눌렸는가
	bool isUp;		//키가 떼여 졌는가

	KeyState(int vkCode) :
		vkCode(vkCode),
		isOn(false),
		isDown(false),
		isUp(false)
	{

	}
	
};
static class InputManager
{
public:
	InputManager();
	~InputManager();

	static D3DXVECTOR2 mousePosistion;

	static void Init(HWND hWnd);
	static void Update();
	static HWND hWnd;
	enum class KeyCode { W, A, S, D, Space, L_mouse, R_mouse, MAX };

	static std::vector<KeyState *> KeyStateVector;

	static void AddKey(KeyCode keyCode, int vkCode);

	static bool GetKey(KeyCode keyCode);
	static bool GetKeyDown(KeyCode keyCode);
	static bool GetKeyUp(KeyCode keyCode);
};

