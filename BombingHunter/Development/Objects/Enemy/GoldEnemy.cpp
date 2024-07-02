#include "GoldEnemy.h"
#include"DxLib.h"

//コンストラクタ
GoldEnemy::GoldEnemy() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

//デストラクタ
GoldEnemy::~GoldEnemy()
{

}

//初期化処理
void GoldEnemy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1 || animation[4] == -1)
	{
		throw("金テキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//当たり判定の大きさ設定
	box_size = 32.0;

	//初期化処理の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0.7, 0.0f);

	//オブジェクトタイプ
	type = ENEMY;
}

//更新処理
void GoldEnemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void GoldEnemy::Draw() const
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
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, filp_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void GoldEnemy::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
}

//当たり判定通知処理
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	direction = 0.0f;
	//画像削除
	Finalize();
}

//移動処理
void GoldEnemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
	if (((location.x + direction.x) < box_size.x) ||
		(640.0f - box_size.x) < (location.x + direction.x))
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
void GoldEnemy::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}