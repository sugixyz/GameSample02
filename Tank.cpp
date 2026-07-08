#include "Tank.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Debug.h"
#include"Ground.h"
#include"Engine/Camera.h"
#include"TankHead.h"

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
	//カメラの高さのバイアス
	const float FPS_HEIGHT_BIAS = 0.2f;

	const float TPS_HEIGHT_BIAS = 5.0f;
	const float TPS_FRONT_BIAS = 8.0f;

	const float RadToDeg = 180 / 3.14159265358;
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
	Instantiate<TankHead>(this);
}

void Tank::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //ロード：読み込み
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX mRotZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
	XMVECTOR vMove = XMVector3TransformCoord(vFront, mRotZ * mRotX * mRotY);

	if (Input::IsKeyDown(DIK_C))
	{
		//カメラの切り替え
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		//自分の位置に
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + TPS_HEIGHT_BIAS;
		camPos.z = camPos.z - TPS_FRONT_BIAS;
		Camera::SetPosition(camPos);
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);
		Camera::SetTarget(camTarget);
	}
		break;
	case TPS_CAMROT:
	{
		//自分の位置に
		XMFLOAT3 camPos;
		XMVECTOR vCam = { 0.0f,TPS_HEIGHT_BIAS,-TPS_FRONT_BIAS,0.0f };
		vCam = XMVector3TransformCoord(vCam, mRotY);
		XMStoreFloat3(&camPos, vPos + vCam);
		Camera::SetPosition(camPos);
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);
		Camera::SetTarget(camTarget);
	}
		break;
	case FPS_CAM:
		//自分の位置に
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + FPS_HEIGHT_BIAS;
		Camera::SetPosition(camPos);
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget,vPos + vMove);
		Camera::SetTarget(camTarget);
		break;
	}


	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2;
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2;
	}

	Debug::Log("CAMTYPE = ");
	Debug::Log(camType_, true); //後のtrueは改行の有無

	if (Input::IsKey(DIK_W))
	{

		vPos = vPos + MOVE_SPEED * vMove;
		XMStoreFloat3(&transform_.position_, vPos); //ストア：書き込み（格納）
	}
	if (Input::IsKey(DIK_S))
	{

		vPos = vPos - MOVE_SPEED * vMove;
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
		XMFLOAT3 normal = data.normal;
		transform_.rotate_.z = atan2f(normal.y, normal.x);
		transform_.rotate_.x = atan2f(-normal.y, normal.z);
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

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}

void Tank::SetTPSCam()
{
}

void Tank::SetTPSCamRot()
{
}

void Tank::SetFPSCam()
{
}