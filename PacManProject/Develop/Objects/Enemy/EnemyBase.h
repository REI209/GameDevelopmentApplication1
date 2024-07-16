#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// エネミー状態
enum eEnemyState
{
	IDLE,		// 待機状態
	MOVE,		// 移動状態
	NAWABARI,   //縄張り状態
	IZIKE,      //いじけ状態
	DIE,		// 死亡状態
};

/// <summary>
/// エネミークラス
/// </summary>
class Enemy : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> dying_animation;		// 死亡のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				//エネミー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	int food_count;							// 餌を食べた数
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	ePanelID old_panel;						// 前回パネル情報
	bool is_destroy;						// 死んだ状態になったか？
	bool is_izike;                          //いじけ状態になったか？
	bool is_nawabari;                       //縄張り状態になったか

	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:

	/// <summary>
	/// エネミーの状態を取得する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
    /// エネミーの死亡状態を取得する
    /// </summary>
    /// <returns>エネミーの死亡状態</returns>
	bool GetDestroy() const;

	/// <summary>
    /// エネミーの縄張り状態を取得する
    /// </summary>
    /// <returns>エネミーの縄張り状態</returns>
	bool GetNawabari() const;

	/// <summary>
    /// エネミーのいじけ状態を取得する
    /// </summary>
    /// <returns>エネミーのいじけ状態</returns>
	bool GetIzike() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

	//縄張りモードにする
	void NawabariMode();
	//いじけモードにする
	void IzikeMode();
};
