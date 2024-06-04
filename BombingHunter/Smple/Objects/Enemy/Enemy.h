#pragma once

#include"../GameObject.h"

class Enemy :public GameObject
{
private:
	int enemy_creat;
	int teki_1[2];     //アニメーション画像
	int teki_2[5];
	int teki_3[2];
	int teki_4[2];
	int effect[4];        //テキ弾エフェクト
	int animation_count;  //アニメーション時間
	Vector2D  direction;  //進行方向

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override; //初期化処理
	virtual void Update() override;     //更新処理
	virtual void Draw() const override; //描画処理
	virtual void Finalize() override;   //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimationControl();
};


