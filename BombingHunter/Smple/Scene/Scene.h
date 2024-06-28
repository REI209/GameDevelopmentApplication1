#pragma once
#define TIMELIMIT  (450)//(9150)  //���Ԑ���

#include<vector>
#include<string>
#include<map>
#include"../Objects/GameObject.h"

class Scene:public GameObject
{
private:

	Vector2D direction;

	int animation[10];
	int game_count;

	int main_sound;
	int stop_sound[5];


	int time_image;  //�^�C�}�[�C���[�W
	int back_image;  //�w�i�C���[�W
	int finish_image[5]; //�t�B�j�b�V���C���[�W
	int count;       //�J�E���g
	int enemy_creat; //�G����
	int score; //�X�R�A
	//int hs; //�n�C�X�R�A
	int score_image; //�X�R�A�C���[�W
	//int hs_image; //�n�C�X�R�A

private:
	std::vector<GameObject*>objects; //�I�u�W�F�N�g���X�g
	std::map<std::string,std::vector<int>>sounds;  //�T�E���h���X�g

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	void TimeUp();

private:

	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};