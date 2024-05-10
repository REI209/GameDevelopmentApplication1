#include"Vector2D.h"
#include<math.h>

//コンストラクタ
Vector2D::Vector2D() :x(0.0f), y(0.0f)
{
}

Vector2D::Vector2D(float scalar) :x(scalar), y(scalar)
{
}

Vector2D::Vector2D(float mx, float my) :x(mx), y(my)
{
}

//デストラクタ
Vector2D::~Vector2D()
{
}

//代入処理を演算子でオーバーロードしています
Vector2D& Vector2D::operator=(const Vector2D& location)
{
	//自身のメンバ変数に引数の値を代入
	this->x = location.x;
	this->y = location.y;

	//自身を課wす
	return *this;
}

//加算処理
const Vector2D Vector2D::operator+(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x + location.x;
	result.y = this->y + location.y;

	return result;
}

//自己代入(加算)
Vector2D& Vector2D::operator+=(const Vector2D& location)
{
	//加算代入する
	this->x += location.x;
	this->y += location.y;

	//自身を返す
	return *this;
}

//減算処理
const Vector2D Vector2D::operator-(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x - location.x;
	result.y = this->y - location.y;

	return result;
}

//減算代入
Vector2D& Vector2D::operator-=(const Vector2D& location)
{
	//減算代入する
	this->x -= location.x;
	this->y -= location.y;

	//自身を返す
	return *this;
}

//乗算処理
const Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * scalar;
	result.y = this->y * scalar;

	return result;
}

const Vector2D Vector2D::operator*(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * location.x;
	result.y = this->y * location.y;

	return result;
}

//乗算代入
Vector2D& Vector2D::operator *= (const float& scalar)
{
	//乗算代入する
	this->x *= scalar;
	this->y *= scalar;

	//自身を返す
	return *this;
}

//乗算代入
Vector2D& Vector2D::operator *= (const Vector2D& location)
{
	//乗算代入する
	this->x *= location.x;
	this->y *= location.y;

	//自身を返す
	return *this;
}

const Vector2D Vector2D::operator/(const float& scalar) const
{
	//0除算しているか確認
	if (fabsf(scalar) < 1e-6f)
	{
		return Vector2D(0.0f);
	}
	return Vector2D(this->x / scalar, this->y / scalar);
}

const Vector2D Vector2D::operator/(const Vector2D& location) const
{
	//0除算しているか確認
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		return Vector2D(0.0f);
	}
	return Vector2D(this->x / location.x, this->y / location.y);
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
	//0除算しているか確認
	if (fabsf(scalar) < 1e-6f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= scalar;
		this->y /= scalar;
	}
	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& location)
{
	//0除算しているか確認
	if ((fabsf(location.x) < 1e-6f) || (fabsf(location.y) < 1e-6f))
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= location.x;
		this->y /= location.y;
	}
	return *this;
}

//整数値にキャストする
void Vector2D::ToInt(int* x, int* y) const
{
	*x = static_cast<int>(this->x);
	*y = static_cast<int>(this->y);
}