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
	//�^�C�}�[�摜
	time_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	//0����9
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

	//�X�R�A�摜
	score_image=   LoadGraph("Resource/Images/Score/font-21.png");
	//�n�C�X�R�A�摜
	hs_image= LoadGraph("Resource/Images/Score/hs.png");

	//�t�B�j�b�V���C���[�W
	finish_image[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	finish_image[1] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	finish_image[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	finish_image[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	finish_image[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");
	//���C������
	main_sound = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	//�I���ɉ���
	stop_sound[0] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_timeup.wav");
	stop_sound[1] = LoadSoundMem("Resource/Sounds/Evaluation/SE_perfect.wav");
	stop_sound[2] = LoadSoundMem("Resource/Sounds/Evaluation/SE_ok.wav");
	stop_sound[3] = LoadSoundMem("Resource/Sounds/Evaluation/SE_good.wav");
	stop_sound[4] = LoadSoundMem("Resource/Sounds/Evaluation/SE_bad.wav");
	//�����������̐ݒ�
	game_count = TIMELIMIT;
	score = 0;
}

//�X�V����
void Scene::Update()
{	
	//���������_���ɂ���
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
	//�G�̃����_������
		if (enemy_creat%250==0 && count > 300)
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
			//�J�E���g���}�C�i�X����
			count--;
		}
	

	    //�X�R�A�̌v�Z
		if (score <= score + n_score)
		{
			score = score + n_score;
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
		CreateObject<Bomb>(objects[0]->GetLocation());
	}

	//���ԃJ�E���g
	if (game_count == 0)
	{
		//�X�R�A�\��
		TimeUp();
	}
	else
	{
		//���ԃ}�C�i�X
		game_count--;
	}
	
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�`��
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	DrawExtendGraph(30,440,70,480, time_image, FALSE);
	//�^�C���摜
	DrawExtendGraph(70, 440, 100, 480, animation[game_count /150/ 10], FALSE); //10
	DrawExtendGraph(100, 440, 130, 480, animation[game_count /150 % 10], FALSE); //1
	//�X�R�A�摜
	DrawExtendGraph(140, 440, 220, 480, score_image, FALSE);
	DrawExtendGraph(220, 440, 250, 480, animation[score / 150 / 1000], FALSE); //1000
	DrawExtendGraph(250, 440, 280, 480, animation[score / 150 /100], FALSE); //100
	DrawExtendGraph(280, 440, 310, 480, animation[score / 150 / 10], FALSE); //10
	DrawExtendGraph(310, 440, 340, 480, animation[score / 150 % 10], FALSE); //1
	//�n�C�X�R�A�摜
	DrawExtendGraph(380, 440, 490, 480, hs_image, FALSE);
	DrawExtendGraph(490, 440, 520, 480, animation[hs / 150 / 1000], FALSE); //1000
	DrawExtendGraph(520, 440, 550, 480, animation[hs / 150 / 100], FALSE); //100
	DrawExtendGraph(550, 440, 580, 480, animation[hs / 150 / 10], FALSE); //10
	DrawExtendGraph(580, 440, 610, 480, animation[hs / 150 % 10], FALSE); //1
	//����
	PlaySoundMem(main_sound, DX_PLAYTYPE_LOOP, FALSE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//�g�p�����摜���J������
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

void Scene::HigthScore()
{
	//�����X�R�A���n�C�X�R�A��荂�����
	if (score >= hs)
	{
		//�n�C�X�R�A�ɑ������
		hs = score;
	}
}

void Scene::TimeUp()
{
	//�n�C�X�R�A����	
	HigthScore();

	//�J�E���g����
	int count = 0;
	count++;
	//���C���������~�߂�
	StopSoundMem(main_sound, FALSE);
	//�t�B�j�b�V������
	PlaySoundMem(stop_sound[0], DX_PLAYTYPE_NORMAL, FALSE);
	//�t�B�j�b�V�����
	DrawExtendGraph(100, 240, 300, 240, finish_image[0], FALSE);

	//���є��\
	if (count == 0)
	{
		//�t�B�j�b�V����ʂ��폜
		DeleteGraph(finish_image[0]);
		//�X�R�A��3000�ȏ�Ȃ�
		if (score > 3000)
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[4], FALSE); //�p�[�t�F�N�g
			PlaySoundMem(stop_sound[1], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else if (score > 1499) //�X�R�A��1500�ȏ�Ȃ�
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[3], FALSE); //OK
			PlaySoundMem(stop_sound[2], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else if (score < 1500) //�X�R�A��1500�����Ȃ�
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[2], FALSE); //GOOD
			PlaySoundMem(stop_sound[3], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else //1000�ȉ�
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[1], FALSE); //BAD
			PlaySoundMem(stop_sound[4], DX_PLAYTYPE_NORMAL, FALSE);
		}
	}

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
		if (a->GetType() == b->GetType())
		{
			return;
		}
		else
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
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