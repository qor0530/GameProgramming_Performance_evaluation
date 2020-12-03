#pragma once

#include <map>
#include <list>
#include <string> 
#include <typeinfo.h>
#include <mmsystem.h>
#include <d3dx9.h>
class BoxCollider;
class Component;
class Animation;
using namespace std;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	std::string name;

	Animation * animation;
	BoxCollider * collider;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	float degree;

	int sortingLayer;

	bool isActive;

	virtual void Awake();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnDestroy();
	virtual void OnRender();
	virtual void OnCollisionEnter(GameObject * GameObject);

	GameObject *Find(string name);
	void UpdateAnimation();
	//template<class T>
	//T * AddComponent();

	//template<class T>
	//T * GetComponent();

private:
	//map<string, Component *> componentMap;
	//list<Component *> componentList;


};
//
//template<class T>
//inline T * GameObject::AddComponent()
//{
//	auto comp = new T();
//
//	auto component = dynamic_cast<Component *>(comp);
//	if (component == nullptr)
//	{
//		return nullptr;
//	}
//
//	auto componentName = typeid(comp).name();
//
//	componentMap.insert(make_pair(componentName, comp));
//	componentList.insert(comp);
//
//	return comp;
//}
//
//template<class T>
//inline T * GameObject::GetComponent()
//{
//	auto componentName = typeid(T*).name();
//
//	auto pair = componentMap.find(componentName);
//
//	if (pair == componentMap.end())
//	{
//		return nullptr;
//	}
//
//	pair->first; //Å°
//	pair->second; //°ª
//
//	return pair->second;
//}
