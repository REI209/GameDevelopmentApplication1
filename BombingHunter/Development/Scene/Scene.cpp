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
	//タイマー画像
	time_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	//0から9
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

	//スコア画像
	score_image=   LoadGraph("Resource/Images/Score/font-21.png");
	//ハイスコア画像
	hs_image= LoadGraph("Resource/Images/Score/hs.png");

	//フィニッシュイメージ
	finish_image[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	finish_image[1] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	finish_image[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	finish_image[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	finish_image[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");
	//メイン音源
	main_sound = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	//終了に音源
	stop_sound[0] = LoadSoundMem("Resource/Sounds/Evaluation/BGM_timeup.wav");
	stop_sound[1] = LoadSoundMem("Resource/Sounds/Evaluation/SE_perfect.wav");
	stop_sound[2] = LoadSoundMem("Resource/Sounds/Evaluation/SE_ok.wav");
	stop_sound[3] = LoadSoundMem("Resource/Sounds/Evaluation/SE_good.wav");
	stop_sound[4] = LoadSoundMem("Resource/Sounds/Evaluation/SE_bad.wav");
	//初期化処理の設定
	game_count = TIMELIMIT;
	score = 0;
}

//更新処理
void Scene::Update()
{	
	//毎時ランダムにする
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
	//敵のランダム生成
		if (enemy_creat%250==0 && count > 300)
		{
			int s;
			s = rand() % 4;


			switch (s)
			{
			case 0:
				CreateObject<BoxEnemy>(Vector2D(100, 400));

				break;

			case 1:
				CreateObject<GoldEnemy>(Vector2D(100, 400));

				break;

			case 2:
				CreateObject<Harpy>(Vector2D(100, 300));

				break;

			case 3:
				CreateObject<WingEnemy>(Vector2D(100 , 200));

				break;

			default:
				break;
			}
			//カウントをマイナスする
			count--;
		}
	

	    //スコアの計算
		if (score <= score + n_score)
		{
			score = score + n_score;
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
		CreateObject<Bomb>(objects[0]->GetLocation());
	}

	//時間カウント
	if (game_count == 0)
	{
		//スコア表示
		TimeUp();
	}
	else
	{
		//時間マイナス
		game_count--;
	}
	
}

//描画処理
void Scene::Draw() const
{
	//背景描画
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	DrawExtendGraph(30,440,70,480, time_image, FALSE);
	//タイム画像
	DrawExtendGraph(70, 440, 100, 480, animation[game_count /150/ 10], FALSE); //10
	DrawExtendGraph(100, 440, 130, 480, animation[game_count /150 % 10], FALSE); //1
	//スコア画像
	DrawExtendGraph(140, 440, 220, 480, score_image, FALSE);
	DrawExtendGraph(220, 440, 250, 480, animation[score / 150 / 1000], FALSE); //1000
	DrawExtendGraph(250, 440, 280, 480, animation[score / 150 /100], FALSE); //100
	DrawExtendGraph(280, 440, 310, 480, animation[score / 150 / 10], FALSE); //10
	DrawExtendGraph(310, 440, 340, 480, animation[score / 150 % 10], FALSE); //1
	//ハイスコア画像
	DrawExtendGraph(380, 440, 490, 480, hs_image, FALSE);
	DrawExtendGraph(490, 440, 520, 480, animation[hs / 150 / 1000], FALSE); //1000
	DrawExtendGraph(520, 440, 550, 480, animation[hs / 150 / 100], FALSE); //100
	DrawExtendGraph(550, 440, 580, 480, animation[hs / 150 / 10], FALSE); //10
	DrawExtendGraph(580, 440, 610, 480, animation[hs / 150 % 10], FALSE); //1
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
	//使用した画像を開放する
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

void Scene::HigthScore()
{
	//もしスコアがハイスコアより高ければ
	if (score >= hs)
	{
		//ハイスコアに代入する
		hs = score;
	}
}

void Scene::TimeUp()
{
	//ハイスコア処理	
	HigthScore();

	//カウントする
	int count = 0;
	count++;
	//メイン音源を止める
	StopSoundMem(main_sound, FALSE);
	//フィニッシュ音源
	PlaySoundMem(stop_sound[0], DX_PLAYTYPE_NORMAL, FALSE);
	//フィニッシュ画面
	DrawExtendGraph(100, 240, 300, 240, finish_image[0], FALSE);

	//成績発表
	if (count == 0)
	{
		//フィニッシュ画面を削除
		DeleteGraph(finish_image[0]);
		//スコアが3000以上なら
		if (score > 3000)
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[4], FALSE); //パーフェクト
			PlaySoundMem(stop_sound[1], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else if (score > 1499) //スコアが1500以上なら
		{
			DrawExtendGraph(100, 240, 300, 240, finish_image[3], FALSE); //OK
			PlaySoundMem(stop_sound[2], DX_PLAYTYPE_NORMAL, FALSE);
		}
		else if (score < 1500) //スコアが1500未満なら
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
		if (a->GetType() == b->GetType())
		{
			return;
		}
		else
		{
			//当たったことをオブジェクトに通知する
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
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