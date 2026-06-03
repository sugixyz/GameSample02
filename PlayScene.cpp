#include "PlayScene.h"
#include"Ground.h"
#include"Tank.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	//親をプレイシーンにして地面を生成
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
