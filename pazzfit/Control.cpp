#include "Control.h"

Control::Control() {
	//ここで画像処理の実行
}

void Control::exe() {
	set_shape_data();
	exec_argolithm();
}

void Control::set_piece() {

}

void Control::exec_argolithm() {
	Algorithm algo;
	algo.fit_piece(piece);
}

void Control::set_shape_data() {
	static bool flag = false;

	if (!flag) {
		make_point();
		make_line();
		make_angle();
		flag = true;
	}
}

void Control::make_point() {
	for (int j = 1;; j++) {
		vector<string> text;
		vector<string> cut_text;
		vector<pair<int, int> > pt;
		string hoge;
		ostringstream oss;
		oss << "shape_data\\qr_data00" << j << ".txt";
		//テキスト展開
		ifstream qr(oss.str());
		if (qr.fail()) {
			break;
		}
		//文字列に変換
		istreambuf_iterator<char> it(qr);
		istreambuf_iterator<char> last;
		string str(it, last);
		text.push_back(str);
		//}
		//文字列の切り分け
		for (int i = 0;; i++) {
			//NULLが来たら終わり
			if (text[0][i] == NULL) {
				cut_text.push_back(hoge);
				break;
			}
			//ダブルコロンで分ける
			if (text[0][i] == ':') {
				cut_text.push_back(hoge);
				hoge.erase(hoge.begin(), hoge.end());
				i++;
			}
			hoge.push_back(text[0][i]);
		}

		for (int k = 1; k < cut_text.size(); k++) {
			vector<string> fuga;
			string piyo;
			for (int i = 0;; i++) {
				if (cut_text[k][i] == NULL) {
					fuga.push_back(piyo);
					break;
				}
				if (cut_text[k][i] == ' ') {
					fuga.push_back(piyo);
					piyo.erase(piyo.begin(), piyo.end());
					i++;
				}
				piyo.push_back(cut_text[k][i]);
			}
			Piece foo;
			piece.push_back(foo);
			for (int i = 0; i < fuga.size(); i++) {
				//頂点数を代入
				if (i == 0) {
					piece[piece.size() - 1].no_piece = atoi(fuga[0].c_str());
				}
				//偶数(yにあたる部分)のときに座標代入
				else if (i % 2 == 0) {
					piece[piece.size() - 1].point.push_back(make_pair(atoi(fuga[i - 1].c_str()), atoi(fuga[i].c_str())));
				}
			}
		}
	}
	cout << piece[0].point[1].first << endl;
}

void Control::make_line() {
	for (int j = 0; j < piece.size(); j++) {
		for (int i = 0; i < piece[j].point.size(); i++) {
			if (i == piece[j].point.size() - 1) {
				double base, height;
				double line;
				base = piece[j].point[i].first - piece[j].point[0].first;
				height = piece[j].point[i].second - piece[j].point[0].second;
				line = sqrt(pow(base, 2) + pow(height, 2));
				piece[j].line.push_back(line);
			}
			else {
				double base, height;
				double line;
				base = piece[j].point[i].first - piece[j].point[i + 1].first;
				height = piece[j].point[i].second - piece[j].point[i + 1].second;
				line = sqrt(pow(base, 2) + pow(height, 2));
				piece[j].line.push_back(line);
			}
		}
	}
	cout << piece[0].point[0].first << endl;
}

void Control::make_angle() {
	int x_point[8] = { 0,1,1,1,0,-1,-1,-1 };
	int y_point[8] = { 1,1,0,-1,-1,-1,0,1 };
	for (int i = 0; i < piece.size(); i++) {
		for (int j = 0; j < piece[i].no_piece; j++) {
			Polygon shape; shape.scaled(10).draw();
			switch (piece[i].no_piece) {
			case 3:
			{
				shape = { { piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second } };
				break;
			}
			case 4:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second }
				};
				break;
			}
			case 5:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second }
				};
				break;
			}
			case 6:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second }
				};
				break;
			}
			case 7:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second }
				};
				break;
			}
			case 8:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second }
				};
				break;
			}
			case 9:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second }
				};
				break;
			}
			case 10:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
					{ piece[i].point[9].first,piece[i].point[9].second }
				};
				break;
			}
			case 11:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
					{ piece[i].point[9].first,piece[i].point[9].second },{ piece[i].point[10].first,piece[i].point[10].second }
				};
				break;
			}
			case 12:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
					{ piece[i].point[9].first,piece[i].point[9].second },{ piece[i].point[10].first,piece[i].point[10].second },{ piece[i].point[11].first,piece[i].point[11].second }
				};
				break;
			}
			case 13:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
					{ piece[i].point[9].first,piece[i].point[9].second },{ piece[i].point[10].first,piece[i].point[10].second },{ piece[i].point[11].first,piece[i].point[11].second },
					{ piece[i].point[12].first,piece[i].point[12].second }
				};
				break;
			}
			case 14:
			{shape = {
				{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
				{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
				{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
				{ piece[i].point[9].first,piece[i].point[9].second },{ piece[i].point[10].first,piece[i].point[10].second },{ piece[i].point[11].first,piece[i].point[11].second },
				{ piece[i].point[12].first,piece[i].point[12].second },{ piece[i].point[13].first,piece[i].point[13].second }
			};
			break;
			}
			case 15:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
					{ piece[i].point[9].first,piece[i].point[9].second },{ piece[i].point[10].first,piece[i].point[10].second },{ piece[i].point[11].first,piece[i].point[11].second },
					{ piece[i].point[12].first,piece[i].point[12].second },{ piece[i].point[13].first,piece[i].point[13].second },{ piece[i].point[14].first,piece[i].point[14].second }
				};
				break;
			}
			case 16:
			{
				shape = {
					{ piece[i].point[0].first,piece[i].point[0].second },{ piece[i].point[1].first,piece[i].point[1].second },{ piece[i].point[2].first,piece[i].point[2].second },
					{ piece[i].point[3].first,piece[i].point[3].second },{ piece[i].point[4].first,piece[i].point[4].second },{ piece[i].point[5].first,piece[i].point[5].second },
					{ piece[i].point[6].first,piece[i].point[6].second },{ piece[i].point[7].first,piece[i].point[7].second },{ piece[i].point[8].first,piece[i].point[8].second },
					{ piece[i].point[9].first,piece[i].point[9].second },{ piece[i].point[10].first,piece[i].point[10].second },{ piece[i].point[11].first,piece[i].point[11].second },
					{ piece[i].point[12].first,piece[i].point[12].second },{ piece[i].point[13].first,piece[i].point[13].second },{ piece[i].point[14].first,piece[i].point[14].second },
					{ piece[i].point[15].first,piece[i].point[15].second }
				};
				break;
			}
			}
			int angle = 0;
			for (int k = 0; k < 8; k++) {
				if (bool hoge = Point(piece[i].point[j].first + x_point[k], piece[i].point[j].second + y_point[k]).intersects(shape)) {
					angle++;
				}
			}
			//凹角である
			if (angle >= 5) {
				double a1, a2, b1, b2;
				double a, b, c, d;
				double kaku;
				a1 = piece[i].point[(j + 1) % piece[i].no_piece].first - piece[i].point[j].first;
				a2 = piece[i].point[(j + 1) % piece[i].no_piece].second - piece[i].point[j].second;
				b1 = piece[i].point[(j + piece[i].no_piece - 1) % piece[i].no_piece].first - piece[i].point[j].first;
				b2 = piece[i].point[(j + piece[i].no_piece - 1) % piece[i].no_piece].second - piece[i].point[j].second;
				a = a1 * b1;
				b = a2 * b2;
				c = sqrt(pow(a1, 2) + pow(a2, 2));
				d = sqrt(pow(b1, 2) + pow(b2, 2));
				kaku = (a + b) / (c * d);
				kaku = acos(kaku);
				kaku = kaku * 180 / Pi;
				kaku = 360 - kaku;
				piece[i].angle.push_back(kaku);
			}
			//凸角である
			else {
				double a1, a2, b1, b2;
				double a, b, c, d;
				double kaku;
				a1 = piece[i].point[(j + 1) % piece[i].no_piece].first - piece[i].point[j].first;
				a2 = piece[i].point[(j + 1) % piece[i].no_piece].second - piece[i].point[j].second;
				b1 = piece[i].point[(j + piece[i].no_piece - 1) % piece[i].no_piece].first - piece[i].point[j].first;
				b2 = piece[i].point[(j + piece[i].no_piece - 1) % piece[i].no_piece].second - piece[i].point[j].second;
				a = a1 * b1;
				b = a2 * b2;
				c = sqrt(pow(a1, 2) + pow(a2, 2));
				d = sqrt(pow(b1, 2) + pow(b2, 2));
				kaku = (a + b) / (c * d);
				kaku = acos(kaku);
				kaku = kaku * 180 / Pi;
				piece[i].angle.push_back(kaku);
			}
		}
	}
}

void Control::output_piece(vector<Piece> &rec_piece) {
		for (int i = 0; i < rec_piece.size(); i++) {
				for (int j = 0; j < rec_piece[i].ans_point.size(); j++) {
					if (rec_piece[i].ans_point.size() == 0) {
						break;
					}
						if (j != rec_piece[i].ans_point.size() - 1) {
								Line(rec_piece[i].ans_point[j].first * 5, rec_piece[i].ans_point[j].second * 5, rec_piece[i].ans_point[j + 1].first * 5, rec_piece[i].ans_point[j + 1].second * 5).draw(Color(i + 1, i + 2, i + 3));
						}
						else {
								Line(rec_piece[i].ans_point[j].first * 5, rec_piece[i].ans_point[j].second * 5, rec_piece[i].ans_point[0].first * 5, rec_piece[i].ans_point[0].second * 5).draw(Color(i + 1, i + 2, i + 3));
						}
				}
		}
		ScreenCapture::Save();
}

void Control::use_position() {
		make_point_position();
		output_piece(piece);
}

void Control::make_point_position() {
		for (int j = 1;; j++) {
				vector<string> text;
				vector<string> cut_text;
				vector<pair<int, int> > pt;
				string hoge;
				ostringstream oss;
				oss << "position_data\\posi_data00" << j << ".txt";
				ifstream qr(oss.str());
				if (qr.fail()) {
						break;
				}
				istreambuf_iterator<char> it(qr);
				istreambuf_iterator<char> last;
				string str(it, last);
				text.push_back(str);
				for (int i = 0;; i++) {
						if (text[0][i] == NULL) {
								cut_text.push_back(hoge);
								break;
						}
						if (text[0][i] == ':') {
								cut_text.push_back(hoge);
								hoge.erase(hoge.begin(), hoge.end());
								i++;
						}
						hoge.push_back(text[0][i]);
				}

				for (int k = 1; k < cut_text.size(); k++) {
						vector<string> fuga;
						string piyo;
						for (int i = 0;; i++) {
								if (cut_text[k][i] == NULL) {
										fuga.push_back(piyo);
										break;
								}
								if (cut_text[k][i] == ' ') {
										fuga.push_back(piyo);
										piyo.erase(piyo.begin(), piyo.end());
										i++;
								}
								piyo.push_back(cut_text[k][i]);
						}
						Piece foo;
						piece.push_back(foo);
						for (int i = 0; i < fuga.size(); i++) {
								if (i == 0) {
										piece[piece.size() - 1].no_piece = atoi(fuga[0].c_str());
								}
								else if (i % 2 == 0) {
										piece[piece.size() - 1].ans_point.push_back(make_pair(atoi(fuga[i - 1].c_str()), atoi(fuga[i].c_str())));
								}
						}
				}
		}
		cout << piece[0].point[1].first << endl;
}
