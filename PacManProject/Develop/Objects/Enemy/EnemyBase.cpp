#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_ENEMY_SPEED (50.0f)

EnemyBase::EnemyBase()
	//:move_animation(),
	//eye_animation(),
	//velocity(0.0f),
	//enemy_state(eEnemyState::MOVE),
	//now_direction_state(eDirectionState::LEFT),
	//next_direction_state(eDirectionState::LEFT),
	//animation_time(0.0f),
	//animation_count(0),
	//old_panel(ePanelID::NONE),
	//is_izike(false),
	//is_nawabari(true),
	//is_destroy(false)
{
}

EnemyBase::~EnemyBase()
{
}
//
////初期化処理
//void EnemyBase::Initialize()
//{
//	// アニメーション画像の読み込み
//	ResourceManager* rm = ResourceManager::GetInstance();
//	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
//	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
//
//	// 当たり判定の設定
//	collision.is_blocking = true;
//	collision.object_type = eObjectType::enemy;	
//	collision.hit_object_type.push_back(eObjectType::enemy);
//	collision.hit_object_type.push_back(eObjectType::wall);
//	collision.hit_object_type.push_back(eObjectType::special);
//	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
//
//	// レイヤーの設定
//	z_layer = 5;
//
//	//// 可動性の設定
//	mobility = eMobilityType::Movable;
//}
//
////更新処理
//void EnemyBase::Update(float delta_second)
//{
//	// プレイヤー状態によって、動作を変える
//	switch (enemy_state)
//	{
//	case eEnemyState::IDLE:
//		// 画像の設定
//		image = move_animation[10];
//		break;
//
//	case eEnemyState::MOVE:
//		// 移動処理z
//		Movement(delta_second);
//		//目のアニメ
//		EyeAnimation(delta_second);
//		break;
//
//	case eEnemyState::NAWABARI:
//		//縄張りモードに切り替える
//		is_nawabari = true;
//		NawabariModeAnime(delta_second);
//		break;
//
//	case eEnemyState::IZIKE:
//		//いじけモードに切り替える
//		is_izike = true;
//		IzikeModeAnime(delta_second);
//		break;
//
//	case eEnemyState::DIE:
//		// 死亡中のアニメーション
//
//		break;
//
//	default:
//		break;
//	}
//}
//
////描画処理
//void EnemyBase::Draw(const Vector2D& screen_offset) const
//{
//	__super::Draw(screen_offset);
//}
//
////終了時処理
//void EnemyBase::Finalize()
//{
//	// 動的配列の解放
//	move_animation.clear();
//	eye_animation.clear();
//}
//
////当たり判定通知処理
//void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
//{
//	// 当たった、オブジェクトが壁だったら
//	if (hit_object->GetCollision().object_type == eObjectType::wall)
//	{
//		// 当たり判定情報を取得して、カプセルがある位置を求める
//		CapsuleCollision hc = hit_object->GetCollision();
//		hc.point[0] += hit_object->GetLocation();
//		hc.point[1] += hit_object->GetLocation();
//
//		// 最近傍点を求める
//		Vector2D near_point = NearPointCheck(hc, this->location);
//
//		// Playerからnear_pointへの方向ベクトルを取得
//		Vector2D dv2 = near_point - this->location;
//		Vector2D dv = this->location - near_point;
//
//		// めり込んだ差分
//		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();
//
//		// diffの分だけ戻る
//		location += dv.Normalize() * diff;
//	}
//	// いじけモードのとき、当たったオブジェクトがプレイヤーだったら死亡状態に切り替える
//	if (eEnemyState::IZIKE&&hit_object->GetCollision().object_type == eObjectType::player)
//	{
//		enemy_state = eEnemyState::DIE;
//	}
//}
//
//
///// エネミーの状態を取得する
//eEnemyState EnemyBase::GetEnemyState() const
//{
//	return enemy_state;
//}
//
////いじけ状態取得
//bool EnemyBase::GetIzike()
//{
//	return is_izike;
//}
//
////縄張り状態取得
//bool EnemyBase::GetNawabari()
//{
//	return is_nawabari;
//}
//
////死亡状態取得
//bool EnemyBase::GetDestroy() const
//{
//	return is_destroy;
//}
//
////移動処理
//void EnemyBase::Movement(float delta_second)
//{
//	// 移動量 * 速さ * 時間 で移動先を決定する
//	location += velocity * D_ENEMY_SPEED * delta_second;
//	// 画面外に行ったら、反対側にワープさせる
//	if (location.x < 0.0f)
//	{
//		old_location.x = 672.0f;
//		location.x = 672.0f - collision.radius;
//		velocity.y = 0.0f;
//	}
//	if (672.0f < location.x)
//	{
//		old_location.x = 0.0f;
//		location.x = collision.radius;
//		velocity.y = 0.0f;
//	}
//}
//
//// 目アニメーション制御
//void EnemyBase::EyeAnimation(float delta_second)
//{
//	//縄張りモードのとき、進行方向に目アニメーション
//	if (enemy_state == NAWABARI) 
//	{
//		image = eye_animation[3];
//
//	/*	switch (now_direction_state)
//		{
//		case EnemyBase::UP:
//			image = eye_animation[0];
//			break;
//
//		case EnemyBase::RIGHT:
//			image = eye_animation[1];
//			break;
//
//		case EnemyBase::DOWN:
//			image = eye_animation[2];
//			break;
//
//		case EnemyBase::LEFT:
//			image = eye_animation[3];
//			break;
//
//		case EnemyBase::NONE:
//			break;
//			
//		default:
//			break;
//		}*/
//	}
//}
//
////縄張りモードのアニメ
//void EnemyBase::NawabariModeAnime(float delta_second)
//{
//	// 移動中のアニメーション
//animation_time += delta_second;
//if (animation_time >= (1.0f / 16.0f))
//{
//	animation_time = 0.0f;
//	animation_count++;
//	if (animation_count >= 4)
//	{
//		animation_count = 0;
//	}
//	// 画像の設定
//	int dir_num = (int)now_direction_state;
//	if (0 <= dir_num && dir_num < 4)
//	{
//		image = move_animation[(dir_num * 3) + animation_num[animation_count]];
//	}
//} 
//}
//
////いじけモードのアニメ
//void EnemyBase::IzikeModeAnime(float delta_second)
//{
//	//// 移動中のアニメーション
////animation_time += delta_second;
////if (animation_time >= (1.0f / 16.0f))
////{
////	animation_time = 0.0f;
////	animation_count++;
////	if (animation_count >= 4)
////	{
////		animation_count = 0;
////	}
////	// 画像の設定
////	int dir_num = (int)now_direction_state;
////	if (0 <= dir_num && dir_num < 4)
////	{
////		image = move_animation[(dir_num * 3) + animation_num[animation_count]];
////	}
////}
//}