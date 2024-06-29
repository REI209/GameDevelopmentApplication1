#include"GameObject.h"
#include"DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0),
	radian(0.0),
	image(0),
	sound(0)
{

}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{

}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{
	//当たり判定の可視化
#ifdef D_PIVOT_CENTER
	Vector2D t1 = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#else
	Vector2D t1 = location;
	Vector2D br = location + box_size;

	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif// D_PIVOT_CENTER

}

//終了時処理
void GameObject::Finalize()
{

}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	DeleteObject();
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return location;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

void GameObject::DeleteObject()
{
	//delete location;
	//delete box_size;

}

int GameObject::GetType()
{
	//自分のタイプを参照します
	return this->type;
}