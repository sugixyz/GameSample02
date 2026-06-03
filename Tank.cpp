#include "Tank.h"
#include"Engine/Model.h"
#include"Engine/Input.h"

Tank::Tank(GameObject* parent)
	:GameObject(parent,"Tank"),hModel_(-1)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
}

void Tank::Update()
{
	if (Input::IsKey(DIK_D) || Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2;
	}
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2;
	}
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_UP))
	{
		float radY = XMConvertToRadians(transform_.rotate_.y);
		XMFLOAT3 dir = XMFLOAT3(sinf(radY), 0.0f, cosf(radY));
		transform_.position_.x += dir.x;
		transform_.position_.z += dir.z;

		XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMMATRIX mtra
		
	}


}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

