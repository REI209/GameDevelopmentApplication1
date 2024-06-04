#include"Enemy.h"
#include"DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() :animation_count(0), direction(0.0f)
{
	teki_1[0] = NULL;
	teki_1[1] = NULL;
	teki_2[0] = NULL;
	teki_2[1] = NULL;
	teki_2[2] = NULL;
	teki_2[3] = NULL;
	teki_2[4] = NULL;
	teki_3[0] = NULL;
	teki_3[1] = NULL;
	teki_4[0] = NULL;
	teki_4[1] = NULL;
	effect[0] = NULL;
	effect[1] = NULL;
	effect[2] = NULL;
	effect[3] = NULL;
}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓ǂݍ���
	//�n�R�e�L
	teki_1[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	teki_1[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	//���e�L
	teki_2[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	teki_2[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	teki_2[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	teki_2[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	teki_2[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
	//�n�[�s�[
	teki_3[0] = LoadGraph("Resource/Images/Harpy/1.png");
	teki_3[1] = LoadGraph("Resource/Images/Harpy/2.png");
	//�n�l�e�L
	teki_4[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	teki_4[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	//�e�L�e
	effect[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	effect[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	effect[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	effect[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	//�G���[�`�F�b�N
	if (teki_1[0] == -1 || teki_1[1] == -1)
	{
		throw("�n�R�e�L�̉摜������܂���\n");
	}
	/*if (teki_2[0] == -1 || teki_2[1] == -1 || teki_2[2] == -1 || teki_2[3] || teki_2[4])
	{
		throw("���e�L�̉摜������܂���\n");
	}
	if (teki_3[0] == -1 || teki_3[1] == -1)
	{
		throw("�n�[�s�[�̉摜������܂���\n");
	}
	if (teki_4[0] == -1 || teki_4[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
	}*/
	//�����̐ݒ�
	radian = 0.0;

	//�����蔻��̑傫���ݒ�
	box_size = 64.0;

	//�����������̐ݒ�
	image = teki_1[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);
}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();

	////�e�L�����_������
	//if (enemy_creat > 0 && animation_count > 300)
	//{
	//	int x;
	//	animation_count = 0;
	//	x = rand();

	//	switch (x)
	//	{
	//	case 0:
	//		//teki_1
	//		break;
	//	case 1:
	//		//teki_2
	//		break;
	//	case 2:
	//		//teki_3
	//		break;
	//	case 3:
	//		//teki_4
	//		break;
	//	}
	//}
}

//�`�揈��
void Enemy::Draw() const
{
	//�摜���]�t���O
	int filp_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		filp_flag = FALSE;
	}
	else
	{
		filp_flag = TRUE;
	}

	//�������ƂɃn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(teki_1[0]);
	DeleteGraph(teki_1[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	direction = 0.0f;
	DeleteGraph(teki_1[0]);
	DeleteGraph(teki_1[1]);
	//delete box_size;
}

//�ړ�����
void Enemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	if (((location.x + direction.x) < box_size.x) ||
		(600.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == teki_1[0])
		{
			image = teki_1[1];
		}
		else
		{
			image = teki_1[0];
		}

		/*if (image == teki_2[0])
		{
			image = teki_2[1];
		}
		else if (image == teki_2[1])
		{
			image = teki_2[2];
		}
		else if (image == teki_2[2])
		{
			image = teki_2[3];
		}
		else if (image == teki_2[3])
		{
			image = teki_2[4];
		}
		else
		{
			image = teki_2[0];
		}

		if (image == teki_3[0])
		{
			image = teki_3[1];
		}
		else
		{
			image = teki_3[0];
		}*/
	}
}