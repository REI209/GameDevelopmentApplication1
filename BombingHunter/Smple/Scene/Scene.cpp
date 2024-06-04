#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Player/Bomb.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(), back_image(NULL),count(0),enemy_creat(0)
{
	/*count_image[0] = NULL;
	count_image[1] = NULL;
	count_image[2] = NULL;
	count_image[3] = NULL;
	count_image[4] = NULL;*/
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
	//画像の読み込み
	back_image = LoadGraph("Resource/Images/BackGround.png");

	/*score_image = LoadGraph("Resource/Images/Score/font-21.png");
	hs_image= LoadGraph("Resource/Images/Score/hs.png");
	count_image[0]= LoadGraph("Resource/Images/Score/0.png");*/
}

//更新処理
void Scene::Update()
{
	//カウント
	count++;

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック
			HitCheckObject(objects[i], objects[j]);
		}
	}

	////Zキーを押したら、敵を生成する
	//if (InputControl::GetKeyDown(KEY_INPUT_Z))
	//{
	//	CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
	//}
	
	//spaceキーを押したら、敵を生成する
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

//描画処理
void Scene::Draw() const
{
	//背景描画
	DrawGraph(0, 0, back_image, FALSE);
	////スコアの描画
	//DrawGraph(0, 0, back_image, FALSE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//使用した画像を開放する
	//DeleteGraph(count_image[0]);
	//DeleteGraph(count_image[1]);
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//２つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、HIT判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#else

//当たり判定チェック
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHIT判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER