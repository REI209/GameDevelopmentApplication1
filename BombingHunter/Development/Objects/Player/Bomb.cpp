#include"Bomb.h"
#include"DxLib.h"

//コンストラクタ
Bomb::Bomb() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}

	//向きの設定
	radian = 4.5; 

	//当たり判定の大きさ設定
	box_size = 64.0;

	//初期化処理の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0.0f, 1.0f);

	//タイプの設定
	type = PLAYER;

}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void Bomb::Draw() const
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
void Bomb::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	direction = 0.0f;
	//終了時処理
	Finalize();

}

//移動処理
void Bomb::Movement()
{
	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Bomb::AnimationControl()
{
	//カウントする
	//アニメーションの切り替え
	for (int i = 0; i < 10; i++)
	{
		//yが400ならアニメーションを変える
		if (location.y == 400)
		{
			image = animation[1];
			direction = 0.0f;
			radian = 0.0;
		}
		else if (image==animation[1])
		{
			image = animation[2];
			Finalize();
		}
	}

}