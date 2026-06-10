#include "Tank.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Debug.h"
#include"Ground.h"

namespace
{
	//タンクの前方向ベクトル
	XMVECTOR vFront = { 0,0,1,0 };
	const float MOVE_SPEED = 0.2;
}

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

	Debug::Log("Yangle = ");
	Debug::Log(transform_.rotate_.y, true); //後のtrueは改行の有無

	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_UP))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //ロード：読み込み
		XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMVECTOR vMove = XMVector3TransformCoord(vFront, mRotY);

		vPos = vPos + MOVE_SPEED * vMove;
		XMStoreFloat3(&transform_.position_, vPos); //ストア：書き込み（格納）
	}

	//レイキャストして、浮いてたら地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;  //レイを一定の高さから落とす
	data.dir = { 0,-1,0 }; //真下にレイを飛ばす
	Ground* g = (Ground*)FindObject("Ground");
	int hGourndModel = g->GetModelHandle();
	Model::RayCast(hGourndModel, &data);

	if (data.hit)
	{
		transform_.position_.y = -data.dist;
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

