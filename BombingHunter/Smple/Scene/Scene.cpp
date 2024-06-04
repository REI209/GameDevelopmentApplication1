#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Player/Bomb.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

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
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
	//�摜�̓ǂݍ���
	back_image = LoadGraph("Resource/Images/BackGround.png");

	/*score_image = LoadGraph("Resource/Images/Score/font-21.png");
	hs_image= LoadGraph("Resource/Images/Score/hs.png");
	count_image[0]= LoadGraph("Resource/Images/Score/0.png");*/
}

//�X�V����
void Scene::Update()
{
	//�J�E���g
	count++;

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

	////Z�L�[����������A�G�𐶐�����
	//if (InputControl::GetKeyDown(KEY_INPUT_Z))
	//{
	//	CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
	//}
	
	//space�L�[����������A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(100.0f, 100.0f));
	}

	//if (enemy_creat > 0 && count > 300)
	//{
	//	int x;
	//	count = 0;
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
	/*}*/
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�`��
	DrawGraph(0, 0, back_image, FALSE);
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