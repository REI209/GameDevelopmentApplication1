#pragma once

#include"../Utility/Vector2D.h"

enum {
	PLAYER,
	BOXENEMY,
	BOMB,
	HARPY,
	GOLDENEMY,
	WINGENEMY,
};

#define D_PIVOT_CENTER  //座標の原点を画像の中心にする

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D direction; //進行方向
	Vector2D location;  //位置情報
	Vector2D box_size;  //短形大きさ
	double radian;      //向き
	int image;          //描画する画像
	int type;           //オブジェクトのタイプ
	int sound;          //再生する音源
	int pointer;
public:
	bool flag;
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();  //初期化処理
	virtual void Update();      //更新処理
	virtual void Draw() const;  //描画処理
	virtual void Finalize();    //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさ取得
	Vector2D GetBoxSize() const;

	//タイプ取得
	int GetType();
};