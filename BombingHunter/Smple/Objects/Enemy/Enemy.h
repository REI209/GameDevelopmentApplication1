#pragma once

#include"../GameObject.h"

class Enemy :public GameObject
{
private:
	int enemy_creat;
	int teki_1[2];     //�A�j���[�V�����摜
	int teki_2[5];
	int teki_3[2];
	int teki_4[2];
	int effect[4];        //�e�L�e�G�t�F�N�g
	int animation_count;  //�A�j���[�V��������
	Vector2D  direction;  //�i�s����

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override; //����������
	virtual void Update() override;     //�X�V����
	virtual void Draw() const override; //�`�揈��
	virtual void Finalize() override;   //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();
};


