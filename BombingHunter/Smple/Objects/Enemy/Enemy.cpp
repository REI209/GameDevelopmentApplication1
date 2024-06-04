#include"Enemy.h"
#include"DxLib.h"

//コンストラクタ
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

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//画像の読み込み
	//ハコテキ
	teki_1[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	teki_1[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	//金テキ
	teki_2[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	teki_2[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	teki_2[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	teki_2[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	teki_2[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
	//ハーピー
	teki_3[0] = LoadGraph("Resource/Images/Harpy/1.png");
	teki_3[1] = LoadGraph("Resource/Images/Harpy/2.png");
	//ハネテキ
	teki_4[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	teki_4[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	//テキ弾
	effect[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	effect[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	effect[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	effect[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	//エラーチェック
	if (teki_1[0] == -1 || teki_1[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}
	/*if (teki_2[0] == -1 || teki_2[1] == -1 || teki_2[2] == -1 || teki_2[3] || teki_2[4])
	{
		throw("金テキの画像がありません\n");
	}
	if (teki_3[0] == -1 || teki_3[1] == -1)
	{
		throw("ハーピーの画像がありません\n");
	}
	if (teki_4[0] == -1 || teki_4[1] == -1)
	{
		throw("ハネテキの画像がありません\n");
	}*/
	//向きの設定
	radian = 0.0;

	//当たり判定の大きさ設定
	box_size = 64.0;

	//初期化処理の設定
	image = teki_1[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();

	////テキランダム生成
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

//描画処理
void Enemy::Draw() const
{
	//画像反転フラグ
	int filp_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		filp_flag = FALSE;
	}
	else
	{
		filp_flag = TRUE;
	}

	//情報をもとにハコテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(teki_1[0]);
	DeleteGraph(teki_1[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	direction = 0.0f;
	DeleteGraph(teki_1[0]);
	DeleteGraph(teki_1[1]);
	//delete box_size;
}

//移動処理
void Enemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
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

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Enemy::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
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