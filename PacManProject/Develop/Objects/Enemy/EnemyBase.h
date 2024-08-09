#pragma once

#include "../GameObject.h"
#include"../../Utility/StageData.h"

////エネミー状態
//enum eEnemyState
//{
//	IDLE,      //待機状態
//	MOVE,      //移動状態
//	IZIKE,     //いじけモード
//	NAWABARI,  //縄張りモード
//	DIE,       //死亡状態
//};

//エネミークラス
class EnemyBase : public GameObject
{
//private:
//    // 進行方向状態
//	enum eDirectionState : unsigned char
//	{
//		UP,
//		RIGHT,
//		DOWN,
//		LEFT,
//		NONE,
//	};
//
//private:
//	std::vector<int> move_animation;   //移動のアニメーション
//	std::vector<int> eye_animation;    //死亡のアニメーション
//	Vector2D old_location;             //前回位置
//	Vector2D velocity;                 //移動量
//	//eEnemyState enemy_state;           //エネミー状態
//	eDirectionState now_direction_state;   //現在の状態
//	eDirectionState next_direction_state;  //前回の状態
//	float animation_time;              //アニメーションの時間
//	int animation_count;               //アニメーションカウント
//	ePanelID old_panel;                //前回のパネル
//	bool is_izike;                     //いじけ状態
//	bool is_nawabari;                  //縄張り状態
//	bool is_destroy;                   //死亡状態
//
//	//移動アニメーションの順番
//	const int animation_num[4] = { 0,1,2,1, };//変える

public:
	EnemyBase();
	virtual ~EnemyBase();

//	virtual void Initialize() override;  //初期化処理
//	virtual void Update(float delta_second) override; //更新処理
//	virtual void Draw(const Vector2D& screen_offset) const override; //描画処理
//	virtual void Finalize() override; //終了時処理
//
//	//当たり判定通知処理
//	virtual void OnHitCollision(GameObjectBase* hit_object) override;
//
//public:
//	//eEnemyState GetEnemyState() const; //エネミー状態取得
//	bool GetIzike(); //いじけ状態取得
//	bool GetNawabari(); //縄張り状態取得
//	bool GetDestroy() const; //死亡状態取得
//
//private:
//	void Movement(float delte_second); //移動処理
//	void EyeAnimation(float delte_second); //アニメーション時間
//	void NawabariModeAnime(float delte_second); //縄張りモードのアニメ
//	void IzikeModeAnime(float delte_second); //いじけモードのアニメ
};