#pragma once
#define DEBUG

#include "../GameObject.h"
#include <vector>

class Bomb : public GameObject
{
private:
    std::vector<GameObject>objects;

    int animation[4];    //アニメーション画像
    int animation_count; //アニメーション時間

    Vector2D direction;   //進行方向



public:
    Bomb();
    ~Bomb();

    virtual void Initialize() override;      //初期化処理
    virtual void Update() override;          //更新処理
    virtual void Draw() const override;      //描画処理
    virtual void Finalize() override;        //終了処理

    //当たり判定通知処理
    virtual void OnHitCollision(GameObject* hit_object) override;
private:
    //移動処理
    void Movement();
    //アニメーション制御
    void AnimeControl();


    //オブジェクト生成処理
    template <class T>
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
            throw ("ゲームオブジェクトが生成できませんでした");
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