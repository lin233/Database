
#include"PerformTest.h"
using namespace std;

void USER() {
	open();
	cout << "存储输入1" << endl;
	cout << "修改输入2" << endl;
	cout << "删除输入3" << endl;
	cout << "查找输入4" << endl;
	cout << "保存输入5" << endl;
	cout << "退出输入6" << endl;
	int i = 0;
	while (true) {
		i++;
		if (i % 5 == 0) {
			cout << "存储输入1" << endl;
			cout << "修改输入2" << endl;
			cout << "删除输入3" << endl;
			cout << "查找输入4" << endl;
			cout << "保存输入5" << endl;
			cout << "退出输入6" << endl;
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
			cout << "保存成功" << endl;
			open();
		}
		else if (x == 6) {
			close();
			break;
		}
		else {
			cout << "请重新输入";
		}
	}
}

int main() {
	USER();
}