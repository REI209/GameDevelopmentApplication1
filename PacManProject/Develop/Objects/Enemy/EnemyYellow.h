#pragma once
#include"../GameObject.h"
#include"../../Utility/StageData.h"
#include"EnemyBase.h"

/// <summary>
/// �G�l�~�[�x�[�X�N���X
/// </summary>
class EnemyYellow : public GameObject
{
private:
	//�i�s�������
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

private:
	std::vector<int> move_animation;   //�ړ��̃A�j���[�V�����摜
	std::vector<int> eyes_animation;   //�ڋʂ̃A�j���[�V�����摜
	Vector2D old_location;             //�O��̈ʒu
	Vector2D velocity;                 //�ړ���
	eEnemyState enemy_state;           //�G�l�~�[���
	eDirectionState now_direction_state;	// ���ݐi�s�������
	eDirectionState next_direction_state;	// ����i�s�������
	float animation_time;              //�A�j���[�V��������
	int animation_count;               //�A�j���[�V�����Y����
	int eyes_animation_count;          //�ڋʃA�j���[�V�����Y����
	ePanelID old_panel;						// �O��p�l�����
	bool is_destroy;                   //���񂾏�ԂɂȂ������H
	int eye_image;


	//�ړ��A�j���[�V�����̏���
	const int animation_num[2] = { 0, 1, };


public:
	EnemyYellow();
	virtual ~EnemyYellow();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// �G�l�~�[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�G�l�~�[�̏��</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// �G�l�~�[�����񂾂��ǂ����m�F����
	/// </summary>
	/// <returns>�G�l�~�[�̏��</returns>
	bool GetDestroy() const;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);

	void EyeAnimeMode();

	void ModeChange();

};

