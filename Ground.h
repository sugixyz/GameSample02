#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Ground : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);
	//デストラクタ
	~Ground();
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
private:
	//地面モデルのハンドル
	int hModel_;
};