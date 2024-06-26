#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX]; //現在の入力値
	static char old_key[D_KEYCODE_MAX]; //前回入力値

public:
	static void Update();

	static bool GetKey(int Key_code);
	static bool GetKeyDown(int Key_code);
	static bool GetKeyUp(int Key_code);

private:
	static bool CheckKeyCodeRange(int Key_code);
};