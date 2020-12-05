#include "Scene.h"
#include <vector>
#include "GameObject.h"
#include "BoxCollider.h"
#include "Enemy.h"
#include "Player.h"
#include "BackGround.h"
#include "InputManager.h"
Scene::Scene() :
	nextSceneName("")
{
}

Scene::~Scene()
{
}

std::list<GameObject*>& Scene::GetObjectList()
{
	return objectList;
}

void Scene::AddGameObject(GameObject* obj)
{
	objectList.push_back(obj);
	obj->Awake();
}

void Scene::CheckNextScene()
{
	if (nextSceneName != "")
	{
		ChangeScene(nextSceneName);
		nextSceneName = "";
	}
}

void Scene::Update()
{
	auto iter = objectList.begin();
	while (iter != objectList.end())
	{
		auto obj = *iter;
		if (obj->isActive)
		{
			obj->Update();
			obj->UpdateAnimation();
			iter++;
		}
		else
		{
			obj->OnDestroy();
			delete obj;
			iter = objectList.erase(iter);
		}
	}

	/*for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		auto obj = *iter;

		if (!obj->isActive)
		{
			obj->OnDestroy();
			objectList.erase(iter--);
			delete obj;
		}
		else
		{
			obj->Update();
			obj->UpdateAnimation();
		}
	}
	*/
}

void Scene::LateUpdate()
{
	for (auto obj : objectList)
	{
		obj->LateUpdate();
	}
}

void Scene::CollisionCheck()
{
	auto size = objectList.size();

	if (size < 1)
	{
		return;
	}
	vector<GameObject*> vec(size);
	int idx = 0;
	for (auto obj : objectList)
	{
		vec[idx++] = obj;
	}

	for (int i = 0; i < size - 1; i++)
	{
		auto obj1 = vec[i];

		if (!obj1->isActive)
			continue;

		for (int j = 0; j < size; j++)
		{
			auto obj2 = vec[j];

			if (obj1 == obj2)
				continue;

			//충돌체크

			//AABB <= 이거쓸꺼임
			//OBB
			//원충돌
			if (AABB(obj1, obj2))
			{//충돌됨
				obj1->OnCollisionEnter(obj2);
				obj2->OnCollisionEnter(obj1);
			}
		}
	}
}

void Scene::ChangeScene(std::string sceneName)
{
	for (auto obj : objectList)
	{
		obj->isActive = false;
	}

	Update();

	if (sceneName == "Main")
	{
		mciSendString(L"close BGM", 0, 0, 0);
		mciSendString(L"open ./Resource/Sound/Bgm.wav type mpegvideo alias BGM", 0, 0, 0);
		mciSendString(L"play BGM repeat", 0, 0, 0);

		//if (InputManager::mousePosistion < )
		ChangeScene("Stage1");
	}

	if (sceneName == "Stage1")
	{
		Instantiate<Player>({ 0.0f, 0.0f });
		Instantiate<Enemy>({ 500.0f, 0.0f });
		Instantiate<Enemy>({ -500.0f, 0.0f });
		Instantiate<Enemy>({ 0.0f, 500.0f });
		Instantiate<Enemy>({ 0.0f, -500.0f });
		Instantiate<BackGround>({ 0.0f, 0.0f });
	}
}

bool Scene::AABB(GameObject* obj1, GameObject* obj2)
{
	RECT result;

	auto rect1 = obj1->collider->GetRect();
	auto rect2 = obj2->collider->GetRect();

	return IntersectRect(&result, &rect1, &rect2);
}