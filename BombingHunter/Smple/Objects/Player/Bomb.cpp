#include"Bomb.h"
#include"DxLib.h"

//�R���X�g���N�^
Bomb::Bomb() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("�{���̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 1.5;

	//�����蔻��̑傫���ݒ�
	box_size = 64.0;

	//�����������̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 1.0f);
}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Bomb::Draw() const
{
	//�������ƂɃn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	direction = 0.0f;

	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//�ړ�����
void Bomb::Movement()
{
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void Bomb::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������,�܂��͓G�ɓ���������
	if (animation_count >= 300)
	{
		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			radian = 0.0;
			direction = 0.0f;
			image = animation[1];
		}
	/*	else if(image==animation[1])
		{
			radian = 0.0;
			image = animation[2];
		}
	    else
	    {
		    radian = 0.0;
		    image = animation[2];
	    }*/
	}
}