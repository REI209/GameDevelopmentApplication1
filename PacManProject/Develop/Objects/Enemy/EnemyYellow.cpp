#include "EnemyYellow.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"

#define D_ENEMY_SPEED  (50.0f)

EnemyYellow::EnemyYellow() :
	move_animation(),
	eyes_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::TUISEKI),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	animation_time(0),
	animation_count(0),
	eyes_animation_count(0),
	old_panel(ePanelID::NONE),
	is_destroy(false),
	eye_image()
{

}

EnemyYellow::~EnemyYellow()
{

}

void EnemyYellow::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//初期進行方向
	velocity = Vector2D(0.0f, -2.0f);

	//レイヤーの設定
	z_layer = 10;

	//可動性の設定
	mobility = eMobilityType::Movable;
}

void EnemyYellow::Update(float delta_second)
{
	//目のアニメ
	EyeAnimeMode();

	if (ePlayerState::POWER)
	{
		eEnemyState::IJIKE;
	}

	//状態の切り替え
	switch (enemy_state)
	{
	case eEnemyState::TUISEKI:
		//画像の設定
		image = move_animation[6];
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::IJIKE:
		//画像の設定
		image = move_animation[16];
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::NAWABARI:
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);
	case eEnemyState::EYE:
		//画像の設定
		image = eyes_animation[0];
		break;
	default:
		break;
	}
}

void EnemyYellow::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	//目のアニメ描画
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
}

void EnemyYellow::Finalize()
{
	//動的配列の解放
	move_animation.clear();
	eyes_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void EnemyYellow::OnHitCollision(GameObjectBase* hit_object)
{
	//当たったオブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		//当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		//最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		//Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		//めり込んだ部分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//diffの分だけ戻る
		location += dv.Normalize() * diff;

		//壁に当たると跳ね返るようにする
		velocity *= -1;
	}

	//当たったオブジェクトがプレイヤーだったら
	if (hit_object->GetCollision().object_type == eObjectType::player && eEnemyState::IJIKE)
	{
		//死亡処理
	}

}
/// <summary>
/// エネミーの状態を取得する
/// </summary>
/// <returns>エネミーの状態</returns>
eEnemyState EnemyYellow::GetEnemyState() const
{
	return enemy_state;
}

bool EnemyYellow::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
///移動処理 
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void EnemyYellow::Movement(float delta_second)
{
	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_ENEMY_SPEED * delta_second;

	//if (velocity.y == 1.0f)
	//{
	//	now_direction_state == EnemyYellow::UP;
	//}
	//else if (velocity.y == -1.0f)
	//{
	//	now_direction_state == EnemyYellow::DOWN;
	//}
	//else if (velocity.x == -1.0f)
	//{
	//	now_direction_state == EnemyYellow::LEFT;
	//}
	//else if (velocity.x == 1.0f)
	//{
	//	now_direction_state == EnemyYellow::RIGHT;
	//}
}

void EnemyYellow::AnimationControl(float delta_second)
{
	//移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		//画像の設定
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 2)
		{
			image = move_animation[(dir_num * 2) + animation_num[animation_count]];
			eye_image = move_animation[(dir_num * 2) + animation_num[animation_count]];
		}
	}
}

void EnemyYellow::EyeAnimeMode()
{
	switch (now_direction_state)
	{
	case EnemyYellow::UP:
		eye_image = eyes_animation[0];
		break;
	case EnemyYellow::DOWN:
		eye_image = eyes_animation[2];
		break;
	case EnemyYellow::LEFT:
		eye_image = eyes_animation[3];
		break;
	case EnemyYellow::RIGHT:
		eye_image = eyes_animation[1];
		break;
	default:
		break;
	}

	if (eEnemyState::IJIKE)
	{
		//いじけモードのとき目を消す
	}
}

void EnemyYellow::ModeChange()
{
	if (eEnemyState::TUISEKI)
	{
		//追いかける処理

	}
	else if (eEnemyState::IJIKE)
	{
		//プレイヤーから逃げる

	}
}
