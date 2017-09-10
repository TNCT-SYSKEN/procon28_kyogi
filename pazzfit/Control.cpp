#include "Control.h"

Control::Control() {
	//ここで画像処理の実行
}

void Control::exe() {
	set_piece();
}

void Control::set_piece() {
	//テキストを読み込み切り分けてそれぞれpush_backする

}

void Control::output_piece() {
		bool screen = false;
		Graphics::SetBackground(Palette::White);
		for (int i = 0; i < piece.size(); i++) {
				for (int j = 0; j < piece[i].ans_point.size(); j++) {
						if (j != piece[i].ans_point.size()) {
								Line(piece[i].ans_point[j].first * 5, piece[i].ans_point[j].second * 5, piece[i].ans_point[j + 1].first * 5, piece[i].ans_point[j + 1].second * 5).draw(Color(i + 1, i + 2, i + 3));
						}
						else {
								Line(piece[i].ans_point[j].first * 5, piece[i].ans_point[j].second * 5, piece[i].ans_point[0].first * 5, piece[i].ans_point[0].second * 5).draw(Color(i + 1, i + 2, i + 3));
						}
				}
		}
		screen = true;
		if (screen)
		{
				ScreenCapture::Save();
				screen = false;
		}
}