#include "Control.h"

Control::Control() {
	//�����ŉ摜�����̎��s
}

void Control::exe() {
	//set_piece();
	//�`����i�[
	set_shape_data();
	exec_argolithm();
}

void Control::set_piece() {
	//�e�L�X�g��ǂݍ��ݐ؂蕪���Ă��ꂼ��push_back����

}

void Control::exec_argolithm() {
	//�����ɃA���S���Y���������Ă�
}

void Control::set_shape_data() {
	make_point();
	make_line();
}

void Control::make_point() {
	for (int j = 1;; j++) {
		vector<string> text;
		vector<string> cut_text;
		vector<pair<int, int> > pt;
		string hoge;
		ostringstream oss;
		oss << "shape_data\\qr_data00" << j << ".txt";
		//�e�L�X�g�W�J
		ifstream qr(oss.str());
		if (qr.fail()) {
			break;
		}
		//������ɕϊ�
		istreambuf_iterator<char> it(qr);
		istreambuf_iterator<char> last;
		string str(it, last);
		text.push_back(str);
		//}
		//������̐؂蕪��
		for (int i = 0;; i++) {
			//NULL��������I���
			if (text[0][i] == NULL) {
				cut_text.push_back(hoge);
				break;
			}
			//�_�u���R�����ŕ�����
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
				//���_������
				if (i == 0) {
					piece[piece.size() - 1].no_piece = atoi(fuga[0].c_str());
				}
				//����(y�ɂ����镔��)�̂Ƃ��ɍ��W���
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
