
#include"PerformTest.h"
using namespace std;

void USER() {
	open();
	cout << "�洢����1" << endl;
	cout << "�޸�����2" << endl;
	cout << "ɾ������3" << endl;
	cout << "��������4" << endl;
	cout << "��������5" << endl;
	cout << "�˳�����6" << endl;
	int i = 0;
	while (true) {
		i++;
		if (i % 5 == 0) {
			cout << "�洢����1" << endl;
			cout << "�޸�����2" << endl;
			cout << "ɾ������3" << endl;
			cout << "��������4" << endl;
			cout << "��������5" << endl;
			cout << "�˳�����6" << endl;
		}
		int x;
		cin >> x;
		if (x == 1) {
			cout << "key:";
			int key;
			cin >> key;
			cout << "value:";
			int value;
			cin >> value;
			store(key, value);
		}
		else if (x == 2) {
			int key;
			cout << "key:";
			cin >> key;
			int value;
			cout << "value:";
			cin >> value;
			modify(key, value);
		}
		else if (x == 3) {
			int key;
			cout << "key:";
			cin >> key;
			remove(key);
		}
		else if (x == 4) {
			int key;
			cout << "key:";
			cin >> key;
			search(key);
		}
		else if (x == 5) {
			close();
			cout << "����ɹ�" << endl;
			open();
		}
		else if (x == 6) {
			close();
			break;
		}
		else {
			cout << "����������";
		}
	}
}

int main() {
	USER();
}