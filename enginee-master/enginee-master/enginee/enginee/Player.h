#pragma once
#include "GameObject.h"
#include <ctime>
class Player :
	public GameObject
{
public:
	Player();
	~Player();

	clock_t deadTime;
	bool isFlip;
	void Awake() override;
	void Update() override;
	void LateUpdate() override;
	void OnRender() override;
	void OnCollisionEnter(GameObject* gameObject) override;
	void OnDestroy() override;
private:
	void PlayerMove();
	void CameraMove();
	void MouseInput();
};
