#include "PlayScene.h"
#include"Ground.h"
#include"Tank.h"
#include"Enemy.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),createCounter(0.0f)
{
}

void PlayScene::Initialize()
{
	//親をプレイシーンにして地面を生成
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
	createCounter++;

	if (createCounter >= 240)
	{
		Instantiate<Enemy>(this);
		createCounter = 0;
	}

	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* sceneManager = (SceneManager*)(this->GetParent());
		sceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
