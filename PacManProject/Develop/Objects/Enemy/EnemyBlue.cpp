#include "EnemyBlue.h"
#include"../../Utility/ResourceManager.h"
#include"DxLib.h"

#define D_ENEMY_SPEED  (50.0f)

EnemyBlue::EnemyBlue() :
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

EnemyBlue::~EnemyBlue()
{

}

void EnemyBlue::Initialize()
{
	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	velocity = Vector2D(0.0f, 2.0f);

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//���C���[�̐ݒ�
	z_layer = 10;

	//�����̐ݒ�
	mobility = eMobilityType::Movable;
}

void EnemyBlue::Update(float delta_second)
{
	//�ڂ̃A�j��
	EyeAnimeMode();

	if (ePlayerState::POWER)
	{
		eEnemyState::IJIKE;
	}

	//��Ԃ̐؂�ւ�
	switch (enemy_state)
	{
	case eEnemyState::TUISEKI:
		//�摜�̐ݒ�
		image = move_animation[4];
		//�ړ�����
		Movement(delta_second);
		//�A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::IJIKE:
		//�摜�̐ݒ�
		image = move_animation[16];
		//�ړ�����
		Movement(delta_second);
		//�A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::NAWABARI:
		//�ړ�����
		Movement(delta_second);
		//�A�j���[�V��������
		AnimationControl(delta_second);
	case eEnemyState::EYE:
		//�摜�̐ݒ�
		image = eyes_animation[0];
		break;
	default:
		break;
	}
}

void EnemyBlue::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	//�ڂ̃A�j���`��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
}

void EnemyBlue::Finalize()
{
	//���I�z��̉��
	move_animation.clear();
	eyes_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void EnemyBlue::OnHitCollision(GameObjectBase* hit_object)
{
	//���������I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		//�����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		//�ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		//Enemy����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		//�߂荞�񂾕���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//diff�̕������߂�
		location += dv.Normalize() * diff;

		velocity *= -1;
	}

	//���������I�u�W�F�N�g���v���C���[��������
	if (hit_object->GetCollision().object_type == eObjectType::player && eEnemyState::IJIKE)
	{
		//���S����
	}

}
/// <summary>
/// �G�l�~�[�̏�Ԃ��擾����
/// </summary>
/// <returns>�G�l�~�[�̏��</returns>
eEnemyState EnemyBlue::GetEnemyState() const
{
	return enemy_state;
}

bool EnemyBlue::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
///�ړ����� 
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBlue::Movement(float delta_second)
{
	location += velocity * D_ENEMY_SPEED * delta_second;
}

void EnemyBlue::AnimationControl(float delta_second)
{
	//�ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		//�摜�̐ݒ�
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 2)
		{
			image = move_animation[(dir_num * 2) + animation_num[animation_count]];
			eye_image = move_animation[(dir_num * 2) + animation_num[animation_count]];
		}
	}
}

void EnemyBlue::EyeAnimeMode()
{
	switch (now_direction_state)
	{
	case EnemyBlue::UP:
		eye_image = eyes_animation[0];
		break;
	case EnemyBlue::DOWN:
		eye_image = eyes_animation[2];
		break;
	case EnemyBlue::LEFT:
		eye_image = eyes_animation[3];
		break;
	case EnemyBlue::RIGHT:
		eye_image = eyes_animation[1];
		break;
	default:
		break;
	}

	if (eEnemyState::IJIKE)
	{
		//���������[�h�̂Ƃ��ڂ�����
	}
}

void EnemyBlue::ModeChange()
{
	if (eEnemyState::TUISEKI)
	{
		//�ǂ������鏈��

	}
	else if (eEnemyState::IJIKE)
	{
		//�v���C���[���瓦����

	}
}
