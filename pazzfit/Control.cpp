#include "Control.h"

Control::Control() {
	//Ç±Ç±Ç≈âÊëúèàóùÇÃé¿çs
}

void Control::exe() {
	set_piece();
	
	use_position();
}

void Control::set_piece() {
}

void Control::output_piece() {
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
				ScreenCapture::Save();
}

void Control::use_position() {
		make_point_position();
		output_piece();
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

