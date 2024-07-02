#pragma once

#include "../GameObject.h"

class EnemyBase : public GameObject
{
protected:

public:
	EnemyBase();
	virtual ~EnemyBase();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};