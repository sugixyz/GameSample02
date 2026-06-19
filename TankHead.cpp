#include "TankHead.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Bullet.h"

TankHead::TankHead(GameObject* parent)
	:GameObject(parent,"TankHead"),hModel_(-1)
{
}

TankHead::~TankHead()
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void TankHead::Update()
{
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2;
	}

	if (Input::IsKey(DIK_SPACE))
	{
		//タンクヘッドのTopというボーンの位置を取得	
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR top = XMLoadFloat3(&cannonTop);
		XMVECTOR root = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = top - root;
		vMove *= 0.2f;
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		Bullet* bullet = Instantiate<Bullet>(this->GetParent()->GetParent());
		bullet->SetPosition(cannonTop);
		bullet->SetMoveVector(move);
	}
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
