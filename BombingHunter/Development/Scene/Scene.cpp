#include"DxLib.h"
#include"Scene.h"

#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Utility/InputControl.h"

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() :objects(),image(0),location()
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
	image = LoadGraph("Resource/BackGround.png");
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
	//�G�l�~�[����
	CreateObject<Enemy>(Vector2D(320.0f, 240.0f));
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
}

//�`�揈��
void Scene::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0,0, image, TRUE);
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
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