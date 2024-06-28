#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/BoxEnemy.h"
#include"../Objects/Enemy/WingEnemy.h"
#include"../Objects/Enemy/GoldEnemy.h"
#include"../Objects/Enemy/Harpy.h"
#include"../Objects/Player/Bomb.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include <time.h>

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
	CreateObject<Player>(Vector2D(320.0f,60.0f));
	//画像の読み込み
	back_image = LoadGraph("Resource/Images/BackGround.png");

	time_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	animation[0] = LoadGraph("Resource/Images/Score/0.png");
	animation[1] = LoadGraph("Resource/Images/Score/1.png");
	animation[2] = LoadGraph("Resource/Images/Score/2.png");
	animation[3] = LoadGraph("Resource/Images/Score/3.png");
	animation[4] = LoadGraph("Resource/Images/Score/4.png");
	animation[5] = LoadGraph("Resource/Images/Score/5.png");
	animation[6] = LoadGraph("Resource/Images/Score/6.png");
	animation[7] = LoadGraph("Resource/Images/Score/7.png");
	animation[8] = LoadGraph("Resource/Images/Score/8.png");
	animation[9] = LoadGraph("Resource/Images/Score/9.png");

	finish_image[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	finish_image[1] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	finish_image[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	finish_image[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	finish_image[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

	score_image=   LoadGraph("Resource/Images/Score/font-21.png");

	main_sound = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");

	stop_sound[0] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_timeup.wav");
	stop_sound[1] = LoadSoundMem("Resource/Sounds/Evaluation/SE_perfect.wav");
	stop_sound[2] = LoadSoundMem("Resource/Sounds/Evaluation/SE_ok.wav");
	stop_sound[3] = LoadSoundMem("Resource/Sounds/Evaluation/SE_good.wav");
	stop_sound[4] = LoadSoundMem("Resource/Sounds/Evaluation/SE_bad.wav");

	//初期化処理の設定
	game_count = TIMELIMIT; 

	/*score_image = LoadGraph("Resource/Images/Score/font-21.png");
	hs_image= LoadGraph("Resource/Images/Score/hs.png");
	count_image[0]= LoadGraph("Resource/Images/Score/0.png");*/
	//サイズ変更

}

//更新処理
void Scene::Update()
{	

	srand((unsigned int)time(NULL));

	//カウントする
	count++;                                                                                                                                                                                                                          

	//Enemyを表示する
	for (int i = 0; i < 1000; i++)
	{

		if (i % 45 == 0)
		{
			enemy_creat++;
		}
	}
	//
		if (enemy_creat%100==0 && count > 300)
		{
			int s;
			s = rand() % 4;


			switch (s)
			{
			case 0:
				CreateObject<BoxEnemy>(Vector2D(20, 400));
		
				break;

			case 1:
				CreateObject<GoldEnemy>(Vector2D(20, 400));
		
				break;

			case 2:
				CreateObject<Harpy>(Vector2D(20, 200));
				
				break;

			case 3:
				CreateObject<WingEnemy>(Vector2D(20 , 200));
				
				break;

			default:
				break;
			}
			count--;
		}
	
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
	
	//spaceキーを押したら、敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D());
	}

	//時間カウント
	if (game_count == 0)
	{
		//スコア表示
		TimeUp();
	}
	else
	{
		game_count--;
	}
	
}

//描画処理
void Scene::Draw() const
{
	//背景描画
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	DrawExtendGraph(30,440,70,480, time_image, FALSE);

	DrawExtendGraph(70, 440, 100, 480, animation[game_count /150/ 10], FALSE); //10
	DrawExtendGraph(100, 440, 130, 480, animation[game_count /150 % 10], FALSE); //1

	DrawExtendGraph(300, 440, 380, 480, score_image, FALSE);

	//音源
	PlaySoundMem(main_sound, DX_PLAYTYPE_LOOP, FALSE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//DeleteObject(GameObject*);
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
//タイムアップ画面
void Scene::TimeUp()
{
	int count = 0;
	count++;
	//メイン音源を止める
	StopSoundMem(main_sound, FALSE);
	//フィニッシュ音源
	PlaySoundMem(stop_sound[0], DX_PLAYTYPE_NORMAL, FALSE);
	//フィニッシュ画面
	DrawExtendGraph(100, 240, 300, 240, finish_image[0], FALSE);

	//成績発表
	if (count==0)
	{
		DeleteGraph(finish_image[0]);
		if (score >3000)
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[4], FALSE); //パーフェクト
			PlaySoundMem(stop_sound[1], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else if (score >1499)
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[3], FALSE); //OK
			PlaySoundMem(stop_sound[2], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else if (score <1500)
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[2], FALSE); //GOOD
			PlaySoundMem(stop_sound[3], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else //1000以下
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[1], FALSE); //BAD
			PlaySoundMem(stop_sound[4], DX_PLAYTYPE_NORMAL, FALSE);
		}
	}
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