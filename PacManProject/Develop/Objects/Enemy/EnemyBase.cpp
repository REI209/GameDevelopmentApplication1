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
////����������
//void EnemyBase::Initialize()
//{
//	// �A�j���[�V�����摜�̓ǂݍ���
//	ResourceManager* rm = ResourceManager::GetInstance();
//	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
//	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
//
//	// �����蔻��̐ݒ�
//	collision.is_blocking = true;
//	collision.object_type = eObjectType::enemy;	
//	collision.hit_object_type.push_back(eObjectType::enemy);
//	collision.hit_object_type.push_back(eObjectType::wall);
//	collision.hit_object_type.push_back(eObjectType::special);
//	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
//
//	// ���C���[�̐ݒ�
//	z_layer = 5;
//
//	//// �����̐ݒ�
//	mobility = eMobilityType::Movable;
//}
//
////�X�V����
//void EnemyBase::Update(float delta_second)
//{
//	// �v���C���[��Ԃɂ���āA�����ς���
//	switch (enemy_state)
//	{
//	case eEnemyState::IDLE:
//		// �摜�̐ݒ�
//		image = move_animation[10];
//		break;
//
//	case eEnemyState::MOVE:
//		// �ړ�����z
//		Movement(delta_second);
//		//�ڂ̃A�j��
//		EyeAnimation(delta_second);
//		break;
//
//	case eEnemyState::NAWABARI:
//		//�꒣�胂�[�h�ɐ؂�ւ���
//		is_nawabari = true;
//		NawabariModeAnime(delta_second);
//		break;
//
//	case eEnemyState::IZIKE:
//		//���������[�h�ɐ؂�ւ���
//		is_izike = true;
//		IzikeModeAnime(delta_second);
//		break;
//
//	case eEnemyState::DIE:
//		// ���S���̃A�j���[�V����
//
//		break;
//
//	default:
//		break;
//	}
//}
//
////�`�揈��
//void EnemyBase::Draw(const Vector2D& screen_offset) const
//{
//	__super::Draw(screen_offset);
//}
//
////�I��������
//void EnemyBase::Finalize()
//{
//	// ���I�z��̉��
//	move_animation.clear();
//	eye_animation.clear();
//}
//
////�����蔻��ʒm����
//void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
//{
//	// ���������A�I�u�W�F�N�g���ǂ�������
//	if (hit_object->GetCollision().object_type == eObjectType::wall)
//	{
//		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
//		CapsuleCollision hc = hit_object->GetCollision();
//		hc.point[0] += hit_object->GetLocation();
//		hc.point[1] += hit_object->GetLocation();
//
//		// �ŋߖT�_�����߂�
//		Vector2D near_point = NearPointCheck(hc, this->location);
//
//		// Player����near_point�ւ̕����x�N�g�����擾
//		Vector2D dv2 = near_point - this->location;
//		Vector2D dv = this->location - near_point;
//
//		// �߂荞�񂾍���
//		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();
//
//		// diff�̕������߂�
//		location += dv.Normalize() * diff;
//	}
//	// ���������[�h�̂Ƃ��A���������I�u�W�F�N�g���v���C���[�������玀�S��Ԃɐ؂�ւ���
//	if (eEnemyState::IZIKE&&hit_object->GetCollision().object_type == eObjectType::player)
//	{
//		enemy_state = eEnemyState::DIE;
//	}
//}
//
//
///// �G�l�~�[�̏�Ԃ��擾����
//eEnemyState EnemyBase::GetEnemyState() const
//{
//	return enemy_state;
//}
//
////��������Ԏ擾
//bool EnemyBase::GetIzike()
//{
//	return is_izike;
//}
//
////�꒣���Ԏ擾
//bool EnemyBase::GetNawabari()
//{
//	return is_nawabari;
//}
//
////���S��Ԏ擾
//bool EnemyBase::GetDestroy() const
//{
//	return is_destroy;
//}
//
////�ړ�����
//void EnemyBase::Movement(float delta_second)
//{
//	// �ړ��� * ���� * ���� �ňړ�������肷��
//	location += velocity * D_ENEMY_SPEED * delta_second;
//	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
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
//// �ڃA�j���[�V��������
//void EnemyBase::EyeAnimation(float delta_second)
//{
//	//�꒣�胂�[�h�̂Ƃ��A�i�s�����ɖڃA�j���[�V����
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
////�꒣�胂�[�h�̃A�j��
//void EnemyBase::NawabariModeAnime(float delta_second)
//{
//	// �ړ����̃A�j���[�V����
//animation_time += delta_second;
//if (animation_time >= (1.0f / 16.0f))
//{
//	animation_time = 0.0f;
//	animation_count++;
//	if (animation_count >= 4)
//	{
//		animation_count = 0;
//	}
//	// �摜�̐ݒ�
//	int dir_num = (int)now_direction_state;
//	if (0 <= dir_num && dir_num < 4)
//	{
//		image = move_animation[(dir_num * 3) + animation_num[animation_count]];
//	}
//} 
//}
//
////���������[�h�̃A�j��
//void EnemyBase::IzikeModeAnime(float delta_second)
//{
//	//// �ړ����̃A�j���[�V����
////animation_time += delta_second;
////if (animation_time >= (1.0f / 16.0f))
////{
////	animation_time = 0.0f;
////	animation_count++;
////	if (animation_count >= 4)
////	{
////		animation_count = 0;
////	}
////	// �摜�̐ݒ�
////	int dir_num = (int)now_direction_state;
////	if (0 <= dir_num && dir_num < 4)
////	{
////		image = move_animation[(dir_num * 3) + animation_num[animation_count]];
////	}
////}
//}