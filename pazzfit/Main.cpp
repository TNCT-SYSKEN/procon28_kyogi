#include "common.h"
#include "Control.h"

void Main(){
	Control control;
	int a = 0;

	const Font font(30);
	Graphics::SetBackground(Palette::White);

	while (System::Update()){
		if (a == 0) {
			font(L"何も使用しない = 1").draw(0,0,Palette::Black);
			font(L"形状情報を使用する = 2").draw(0, 50, Palette::Black);
			font(L"配置情報を使用する = 3").draw(0, 100, Palette::Black);
			if (Input::Key1.clicked) {
				a = 1;
			}
			if (Input::Key2.clicked) {
				a = 2;
			}
			if (Input::Key3.clicked) {
				a = 3;
			}
		}
		if (a == 1) {
			control.exe();
		}
	}
}
