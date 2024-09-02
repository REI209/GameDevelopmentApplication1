#include"EnemyBase.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"

#define D_ENEMY_SPEED  (50.0f)

EnemyBase::EnemyBase() :
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

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Initialize()
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
	velocity = Vector2D(2.0f, 0.0f);

	//レイヤーの設定
	z_layer = 10;

	//可動性の設定
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
{
	//

	
	//目のアニメ
	EyeAnimeMode();

	//状態の切り替え
	switch (enemy_state)
	{
	case eEnemyState::TUISEKI:
		//画像の設定
		image = move_animation[0];
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);

		EyeAnimeMode();
		break;
	case eEnemyState::IJIKE:
		//画像の設定
		image = move_animation[16];
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);
		break;
	//case eEnemyState::NAWABARI:
	//	//移動処理
	//	Movement(delta_second);
	//	//アニメーション制御
	//	AnimationControl(delta_second);
	case eEnemyState::EYE:
		//死んだときに戻る処理
		break;
	default:
		break;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	//目のアニメ描画
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
}

void EnemyBase::Finalize()
{
	//動的配列の解放
	move_animation.clear();
	eyes_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	//当たったオブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		//当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		//最近傍点を求める7
		Vector2D near_point = NearPointCheck(hc, this->location);

		//Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		//めり込んだ部分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//diffの分だけ戻る
		location += dv.Normalize() * diff;

		velocity *= -1;
	}

	//当たったオブジェクトがプレイヤーだったら
	if (hit_object->GetCollision().object_type == eObjectType::player&&eEnemyState::IJIKE)
	{
		//死亡処理
	}

}
/// <summary>
/// エネミーの状態を取得する
/// </summary>
/// <returns>エネミーの状態</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

bool EnemyBase::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
///移動処理 
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
void EnemyBase::Movement(float delta_second)
{

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_ENEMY_SPEED * delta_second;

}

void EnemyBase::AnimationControl(float delta_second)
{
	//移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		//フレームカウントを加算
	//	animation_count++;

	//	if (animation_count >= 10)
	//	{
	//		animation_count = 0;

	//		if (image == move_animation[0])
	//		{
	//			image = move_animation[1];
	//		}
	//		else
	//		{
	//			image = move_animation[0];
	//		}
	//	}
	}
}

void EnemyBase::EyeAnimeMode()
{

	switch (next_direction_state)
	{
	case EnemyBase::UP:
		eye_image = eyes_animation[0];
		break;
	case EnemyBase::DOWN:
		eye_image = eyes_animation[2];
		break;
	case EnemyBase::LEFT:
		eye_image = eyes_animation[3];
		break;
	case EnemyBase::RIGHT:
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

void EnemyBase::ModeChange()
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