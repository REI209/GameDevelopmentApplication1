#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"


#define D_ENEMY_SPEED	(50.0f)
#define MODE_TIME  (100) //�ǐՃ��[�h�Ƃ̐؂�ւ�

Enemy::Enemy() :
	move_animation(),
	dying_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::MOVE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	food_count(0),
	animation_time(0.0f),
	animation_count(0),
	old_panel(ePanelID::NONE),
	is_destroy(false),
	is_izike(false),
	is_nawabari(false)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 12, 12, 1, 32, 32);
	dying_animation = rm->GetImages("Resource/Images/eyes.png", 11, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::food);
	collision.hit_object_type.push_back(eObjectType::power_food);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;
}

void Enemy::Update(float delta_second)
{
	// �v���C���[��Ԃɂ���āA�����ς���
	switch (enemy_state)
	{
	case eEnemyState::IDLE:
		// �摜�̐ݒ�
		image = move_animation[9];
		break;
	case eEnemyState::MOVE:
		// �ړ�����
		Movement(delta_second);
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::NAWABARI:
		//�꒣����
		NawabariMode();
	case eEnemyState::IZIKE:
		//���������
		IzikeMode();
	case eEnemyState::DIE:
		// ���S���̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// ����������
			if (animation_count >= dying_animation.size())
			{
				enemy_state = eEnemyState::IDLE;
				animation_count = 0;
				is_destroy = true;
			}
		}
		image = dying_animation[animation_count];
		break;
	default:
		break;
	}
}

void Enemy::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Enemy::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Enemy::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	// ���������I�u�W�F�N�g���v���C���[��������
	if (enemy_state==eEnemyState::IZIKE || hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::DIE;
	}
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��擾����
/// </summary>
/// <returns>�G�l�~�[�̏��</returns>
eEnemyState Enemy::GetEnemyState() const
{
	return enemy_state;
}

//���S��Ԃɂ���
bool Enemy::GetDestroy() const
{
	return is_destroy;
}

//�꒣���Ԃɂ���
bool Enemy::GetNawabari() const
{
	return is_nawabari;
}

//��������Ԃɂ���
bool Enemy::GetIzike() const
{
	return is_izike;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::Movement(float delta_second)
{
	// �ړ��ʂ���ړ��������X�V
	if (Vector2D::Distance(old_location, location) == 0.0f)
	{
		// �ړ����Ȃ���� direction_state ��ύX����
		velocity = 0.0f;
		now_direction_state = next_direction_state;
		next_direction_state = eDirectionState::NONE;
	}
	else
	{
		// �ړ������Ɉړ����Ă��Ȃ���� direction_state ��ύX����
		switch (now_direction_state)
		{
		case eDirectionState::UP:
		case eDirectionState::DOWN:
		{
			float diff = location.y - old_location.y;
			if (((now_direction_state == eDirectionState::UP) && (diff < 0.0f)) ||
				((now_direction_state == eDirectionState::DOWN) && (0.0f < diff)))
			{
				// �ړ������Ɉړ����Ă�̂� break
				break;
			}

			velocity.y = 0.0f;
			now_direction_state = next_direction_state;
			next_direction_state = eDirectionState::NONE;
		}
		break;

		case eDirectionState::LEFT:
		case eDirectionState::RIGHT:
		{

			float diff = location.x - old_location.x;
			if (((now_direction_state == eDirectionState::LEFT) && (diff < 0.0f)) ||
				((now_direction_state == eDirectionState::RIGHT) && (0.0f < diff)))
			{
				// �ړ������Ɉړ����Ă�̂� break
				break;
			}

			velocity.x = 0.0f;
			now_direction_state = next_direction_state;
			next_direction_state = eDirectionState::NONE;
		}
		break;

		default:// �������Ȃ�
			break;
		}
	}

	//// ���͏�Ԃ̎擾
	//InputManager* input = InputManager::GetInstance();

	// ���݃p�l���̏�Ԃ��m�F
	ePanelID panel = StageData::GetPanelData(location);

	//// ���͂���ړ�������ݒ�
	//if (input->GetKeyDown(KEY_INPUT_UP) || input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::UP:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::DOWN:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::UP;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::UP;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_DOWN) || input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::DOWN:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::UP:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::DOWN;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::DOWN;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::LEFT:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::RIGHT:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::LEFT;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::LEFT;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::RIGHT:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::LEFT:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::RIGHT;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::RIGHT;
	//	}
	//}

	// �i�s�����̈ړ��ʂ�ǉ�
	switch (now_direction_state)
	{
	case Enemy::UP:
		velocity.y = -1.0f;
		break;
	case Enemy::DOWN:
		velocity.y = 1.0f;
		break;
	case Enemy::LEFT:
		velocity.x = -1.0f;
		break;
	case Enemy::RIGHT:
		velocity.x = 1.0f;
		break;
	default:
		velocity = 0.0f;
		now_direction_state = next_direction_state;
		next_direction_state = Enemy::NONE;
		break;
	}

	// ��s���͂̈ړ��ʂ�ǉ�
	if ((panel != ePanelID::NONE)
		&& (old_panel != panel))
	{
		switch (next_direction_state)
		{
		case Enemy::UP:
			velocity.y = -1.0f;
			break;
		case Enemy::RIGHT:
			velocity.x = 1.0f;
			break;
		case Enemy::DOWN:
			velocity.y = 1.0f;
			break;
		case Enemy::LEFT:
			velocity.x = -1.0f;
			break;
		default:
			break;
		}
	}

	// �O����W�̍X�V
	old_location = location;

	// �O��p�l���̍X�V
	old_panel = panel;

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_ENEMY_SPEED * delta_second;

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
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

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
		}

	}
}

void Enemy::NawabariMode()
{

}

void Enemy::IzikeMode()
{

}