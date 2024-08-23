#include"EnemyBase.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"

#define D_ENEMY_SPEED  (100.0f)

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

	//レイヤーの設定
	z_layer = 10;

	//可動性の設定
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
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
		image = move_animation[0];
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

		//最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		//Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		//めり込んだ部分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//diffの分だけ戻る
		location += dv.Normalize() * diff;
	}

	//当たったオブジェクトがプレイヤーだったら
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::IJIKE;
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
	//移動量から移動方向を更新
	if (Vector2D::Distance(old_location, location) == 0.0f)
	{
		//移動が無ければ、direction_stateを変更する
		velocity = 0.0f;
		now_direction_state = next_direction_state;
		next_direction_state = eDirectionState::LEFT;
	}
	else
	{
		//移動方向に移動していなければdirection_stateを変更する
		switch (now_direction_state)
		{
		case eDirectionState::UP:
		case eDirectionState::DOWN:
		{
			float diff = location.y - old_location.y;
			if (((now_direction_state == eDirectionState::UP) && (diff < 0.0f)) ||
				((now_direction_state == eDirectionState::DOWN) && (0.0f < diff)))
			{
				// 移動方向に移動してるので break
				break;
			}

			velocity.y = 0.0f;
			now_direction_state = next_direction_state;
			next_direction_state = eDirectionState::LEFT;
		}
		break;

		case eDirectionState::LEFT:
		case eDirectionState::RIGHT:
		{

			float diff = location.x - old_location.x;
			if (((now_direction_state == eDirectionState::LEFT) && (diff < 0.0f)) ||
				((now_direction_state == eDirectionState::RIGHT) && (0.0f < diff)))
			{
				// 移動方向に移動してるので break
				break;
			}

			velocity.x = 0.0f;
			now_direction_state = next_direction_state;
			next_direction_state = eDirectionState::LEFT;
		}
		break;

		default:// 何もしない
			break;
		}
	}

	//現在パネルの状態を確認
	ePanelID panel = StageData::GetPanelData(location);

	//進行方向の移動量を追加
	switch (now_direction_state)
	{
	case EnemyBase::UP:
		velocity.y = -1.0f;
		break;
	case EnemyBase::DOWN:
		velocity.y = 1.0f;
		break;
	case EnemyBase::LEFT:
		velocity.x = -1.0f;
		break;
	case EnemyBase::RIGHT:
		velocity.x = 1.0f;
		break;
	default:
		velocity = 0.0f;
		now_direction_state = next_direction_state;
		next_direction_state = EnemyBase::LEFT;
		break;
	}

	//選考入力の移動量を追加
	if ((panel != ePanelID::NONE)
		&& (old_panel != panel))
	{
		switch (next_direction_state)
		{
		case EnemyBase::UP:
			velocity.y = -1.0f;
			break;
		case EnemyBase::RIGHT:
			velocity.x = 1.0f;
			break;
		case EnemyBase::DOWN:
			velocity.y = 1.0f;
			break;
		case EnemyBase::LEFT:
			velocity.x = -1.0f;
			break;
		default:
			break;
		}
	}

	//前回座標の更新
	old_location = location;

	//前回パネルの更新
	old_panel = panel;

	//移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_ENEMY_SPEED * delta_second;

	// 画面外に行ったら、反対側にワープさせる
	if (location.x < 0.0f)
	{
		old_location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		old_location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}
}

void EnemyBase::AnimationControl(float delta_second)
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

void EnemyBase::EyeAnimeMode()
{
	switch (now_direction_state)
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