#include "Bullet.h"
#include"Engine/Model.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"),hModel_(-1),move(XMFLOAT3(0,0,0))
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.25f);
	AddCollider(collider);
}

void Bullet::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vMove = XMLoadFloat3(&move);
	XMVECTOR fall = { 0,-0.005,0 };
	XMStoreFloat3(&move, XMLoadFloat3(&move) + fall);
	vPos += vMove;
	XMStoreFloat3(&transform_.position_, vPos);

	if (transform_.position_.y <= -4.0f)
	{
		KillMe();
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
