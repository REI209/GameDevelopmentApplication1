#include"DxLib.h"
#include"Scene.h"

#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"

//コンストラクタ
Scene::Scene() :objects(),image(0),location()
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
	image = LoadGraph("Resource/BackGround.png");
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
	//エネミー生成
	CreateObject<Enemy>(Vector2D(320.0f, 240.0f));
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
}

//描画処理
void Scene::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0,0, image, TRUE);
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
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
