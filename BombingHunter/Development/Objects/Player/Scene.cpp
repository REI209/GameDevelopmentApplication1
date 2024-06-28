#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/BoxEnemy.h"
#include"../Objects/Enemy/WingEnemy.h"
#include"../Objects/Enemy/GoldEnemy.h"
#include"../Objects/Enemy/Harpy.h"
#include"../Objects/Player/Bomb.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include <time.h>

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(), back_image(NULL),count(0),enemy_creat(0)
{
	/*count_image[0] = NULL;
	count_image[1] = NULL;
	count_image[2] = NULL;
	count_image[3] = NULL;
	count_image[4] = NULL;*/
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f,60.0f));
	//�摜�̓ǂݍ���
	back_image = LoadGraph("Resource/Images/BackGround.png");
	time_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	animation[0] = LoadGraph("Resource/Images/Score/0.png");
	animation[1] = LoadGraph("Resource/Images/Score/1.png");
	animation[2] = LoadGraph("Resource/Images/Score/2.png");
	animation[3] = LoadGraph("Resource/Images/Score/3.png");
	animation[4] = LoadGraph("Resource/Images/Score/4.png");
	animation[5] = LoadGraph("Resource/Images/Score/5.png");
	animation[6] = LoadGraph("Resource/Images/Score/6.png");
	animation[7] = LoadGraph("Resource/Images/Score/7.png");
	animation[8] = LoadGraph("Resource/Images/Score/8.png");
	animation[9] = LoadGraph("Resource/Images/Score/9.png");
	score_image=   LoadGraph("Resource/Images/Score/font-21.png");

	//�����������̐ݒ�
	game_count = TIMELIMIT;

	/*score_image = LoadGraph("Resource/Images/Score/font-21.png");
	hs_image= LoadGraph("Resource/Images/Score/hs.png");
	count_image[0]= LoadGraph("Resource/Images/Score/0.png");*/
	//�T�C�Y�ύX

}

//�X�V����
void Scene::Update()
{	

	srand((unsigned int)time(NULL));

	//�J�E���g����
	count++;                                                                                                                                                                                                                          

	//Enemy��\������
	for (int i = 0; i < 1000; i++)
	{

		if (i % 45 == 0)
		{
			enemy_creat++;
		}
	}
	//
		if (enemy_creat%100==0 && count > 300)
		{
			int s;
			s = rand() % 4;


			switch (s)
			{
			case 0:
				CreateObject<BoxEnemy>(Vector2D(100, 400));

				break;

			case 1:
				CreateObject<GoldEnemy>(Vector2D(100, 400));

				break;

			case 2:
				CreateObject<Harpy>(Vector2D(100, 300));

				break;

			case 3:
				CreateObject<WingEnemy>(Vector2D(100 , 200));

				break;

			default:
				break;
			}
			count--;
		}
	
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N
			HitCheckObject(objects[i], objects[j]);
		}
	}
	
	//space�L�[����������A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D());
	}

	//���ԃJ�E���g
	if (game_count == 0)
	{
		//�X�R�A�\��
	}
	else
	{
		game_count--;
	}
	
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�`��
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	DrawExtendGraph(30,440,70,480, time_image, FALSE);
	DrawExtendGraph(70, 440, 100, 480, animation[game_count /150/ 10], FALSE); //10
	DrawExtendGraph(100, 440, 130, 480, animation[game_count /150 % 10], FALSE); //1
	DrawExtendGraph(300, 440, 380, 480, score_image, FALSE);
	////�X�R�A�̕`��
	//DrawGraph(0, 0, back_image, FALSE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//DeleteObject(GameObject*);
	//�g�p�����摜���J������
	//DeleteGraph(count_image[0]);
	//DeleteGraph(count_image[1]);
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHIT����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#else

//�����蔻��`�F�b�N
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���HIT�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER