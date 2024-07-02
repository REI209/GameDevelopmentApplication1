#pragma once
#define TIMELIMIT  (9150)  //時間制限
#define SCORE (0)

#include<vector>
#include<string>
#include<map>
#include"../Objects/GameObject.h"

class Scene
{
private:
	int back_image;  //背景イメージ
	int animation[10];   //数字画像
	int finish_image[5]; //止まった後の画像
	int stop_sound[5];   //止まった後の音源
	int main_sound;  //メイン音源

	int game_count;      //タイマー
    int time_image;  //タイマーイメージ
	int count;       //カウント

	int enemy_creat; //敵生成

	int score; //スコア
	int n_score; //新しいスコア
	int hs; //ハイスコア
	int score_image; //スコアイメージ
	int hs_image; //ハイスコアイメージ

private:
	std::vector<GameObject*>objects; //オブジェクトリスト
	std::map<std::string,std::vector<int>>sounds;  //サウンドリスト

public:
	Scene();
	~Scene();

	void Initialize();  //初期化処理
	void Update();  //更新処理
	void Draw() const; //描画処理
	void Finalize(); //終了時処理

	//ハイスコアの処理
	void HigthScore();
	//タイムアップの処理
	void TimeUp();

private:

	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};