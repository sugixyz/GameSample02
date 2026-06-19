#include "Enemy.h"
#include"Engine/Model.h"
#include"Ground.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),hModel_(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	int x = rand() % 51 - 25;
	int z = rand() % 51 - 25;
	transform_.position_.x = x;
	transform_.position_.z = z;

	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 2.0f);
	AddCollider(collider);
}

void Enemy::Update()
{
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

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		pTarget->KillMe();
		KillMe();
	}
}
