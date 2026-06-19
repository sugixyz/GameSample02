#pragma once
#include"Engine/GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(GameObject* parent);
	~Bullet();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	/// <summary>
	/// 弾の移動ベクトルを設定
	/// </summary>
	/// <param name="moveVec">移動ベクトル</param>
	void SetMoveVector(const XMFLOAT3& moveVec) { move = moveVec; }
private:
	//弾モデルのハンドル
	int hModel_;
	//弾の移動ベクトル
	XMFLOAT3 move;
};