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
	enum CamType
	{
		FIXED_CAM, //固定カメラ
		TPS_CAM, //３人称視点カメラ
		TPS_CAMROT, //３人称視点カメラ（回転）
		FPS_CAM, //一人称視点カメラ
		CAM_TYPE_MAX
	};
}

Tank::Tank(GameObject* parent)
	:GameObject(parent,"Tank"),hModel_(-1),camType_(FIXED_CAM)
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
	if (Input::IsKeyDown(DIK_C))
	{
		//カメラの切り替え
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		break;
	case TPS_CAM:
		break;
	case TPS_CAMROT:
		break;
	case FPS_CAM:
		break;
	}


	if (Input::IsKey(DIK_D) || Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2;
	}
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2;
	}

	Debug::Log("CAMTYPE = ");
	Debug::Log(camType_, true); //後のtrueは改行の有無

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

