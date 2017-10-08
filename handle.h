#include"BPlusNode.h"
#include"Tree.h"
#include<iostream>
#include<random>
#include<fstream>
#include <ctime>
#include <assert.h>
#include<vector>
#include<string>
#include<sstream>


CBPlusTree tree;
vector<vector<int>>buffer;
fstream idx;
fstream datafile;
vector<int>DeleteLocation;
fstream DeleteIdx;
const int capacity = 10;

bool o_store(int key, int value);

//������ݿ���ڣ��ʹ򿪣������ھʹ�������ȡ�����ļ�����B+�����Լ���ȡ�������õĵ�ַ����vector��
void open() {
	//�������ļ�
	datafile.open("data.txt");
	if (!datafile.is_open()) {
		ofstream x;
		x.open("data.txt");
		x.close();
		datafile.open("data.txt");
	}
	//�������ļ�������B+��
	idx.open("idx.txt");
	if (!idx.is_open()) {
		ofstream x;
		x.open("idx.txt");
		x.close();
		idx.open("idx.txt");
	}
	else {
		while (!idx.eof()) {
			int key, value;
			idx >> key;
			idx >> value;
			if(key>0)tree.insert(key, value);
			else break;
		}
		idx.close();
		idx.open("idx.txt");
	}
	//�������õ�ַ�ļ�
	DeleteIdx.open("DeleteIdx.txt");
	if (!DeleteIdx.is_open()) {
		ofstream x;
		x.open("DeleteIdx.txt");
		x.close();
		DeleteIdx.open("DeleteIdx.txt");
	}
	else {
			while (!DeleteIdx.eof()) {
				int dex;
				DeleteIdx >> dex;
				if (dex >= 0) {
					DeleteLocation.push_back(dex);
				}
				else break;
		}
	}
	buffer.clear();

}

//���Ժ����õĴ�����ʽ���õĶ����½������ݿ⣬����ȶԲ�����
void TestOpen() {
	ofstream x("Testdata.txt", ios::trunc);
	x.close();
	datafile.open("Testdata.txt");

	ofstream y("Testidx.txt", ios::trunc);
	y.close();
	idx.open("Testidx.txt");

	ofstream z("TestDeleteidx.txt", ios::trunc);
	z.close();
	DeleteIdx.open("TestDeleteidx.txt");

	tree.clear();

}

//ˢ�������ļ��������õ�ַ�ļ�,ˢ�������ļ���д���档
void TestClose() {
	//ˢ�������õĵ�ַ�ļ�
	ofstream DeleteIdx("TestDeleteidx.txt", ios::trunc);
	for (int i = 0; i < DeleteLocation.size(); i++) {
		DeleteIdx << DeleteLocation[i] << endl;
	}
	DeleteIdx.close();

	//ˢ�������ļ�
	ofstream idx("Testidx.txt", ios::trunc);
	vector<vector<int>>LocationIdx = tree.ALL();
	for (int i = 0; i < LocationIdx.size(); i++) {
		idx << LocationIdx[i][0] << " " << LocationIdx[i][1] << endl;
	}
	idx.close();

	//ˢ�������ļ����ѻ����е�����ȫ������
	for (int i = 0; i < buffer.size(); i++) {
		o_store(buffer[i][0], buffer[i][1]);
	}
	buffer.clear();
	datafile.close();

	tree.clear();

}


//ˢ�������ļ��������õ�ַ�ļ�,ˢ�������ļ���д���档
void close() {
	//ˢ�������õĵ�ַ�ļ�
	ofstream DeleteIdx("DeleteIdx.txt", ios::trunc);
	for (int i = 0; i < DeleteLocation.size(); i++) {
		DeleteIdx << DeleteLocation[i] << endl;
	}
	DeleteIdx.close();

	//ˢ�������ļ�
	ofstream idx("idx.txt", ios::trunc);
	vector<vector<int>>LocationIdx = tree.ALL();
	for (int i = 0; i < LocationIdx.size(); i++) {
		idx << LocationIdx[i][0] << " " << LocationIdx[i][1] << endl;
	}
	idx.close();

	//ˢ�������ļ����ѻ����е�����ȫ������
	for (int i = 0; i < buffer.size(); i++) {
		o_store(buffer[i][0], buffer[i][1]);
	}
	buffer.clear();
	datafile.close();

}

//�ж��Ƿ����key�ǰ�λ����int������Ҳ�ǰ�λ����int.����һǧ����С��һ�ڵ�����
bool valid(int key, int value) {
	if ((key <= 10000000) || (key > 99999999))return false;
	if ((value <= 10000000) || (value > 99999999))return false;
	return true;
}

//�ж��Ƿ��ڻ�����
int InCache(int key) {
	for (int i = 0; i < buffer.size(); i++) {
		if (key == buffer[i][0])return i;
	}
	return -1;
}

//���ң����ҳɹ�����value��ʧ�ܷ���-1.
int o_search(int key) {
	int InC = InCache(key);
	if (InC != -1) {
		return buffer[InC][1];
	}
	if (tree.search(key)) {
		int location = tree.find(key);
		datafile.seekp(location, ios::beg);
		int key, value;
		datafile >> key;
		datafile >> value;
		return value;
	};
	return -1;//��Ϊvalue�Ǵ���һǧ��ģ����Կ�����-1��ʧ�ܵı�־
}

//���Ҳ���
bool searchExam(int key, int CorrectValue) {
	return (o_search(key) == CorrectValue);
}

//�û��ò��ҽӿ�
void search(int key) {
	int value = o_search(key);
	if (value != -1) { cout << key << " " << value << endl; return; }
	else { cout << "����ʧ�ܣ������ݲ�����" << endl; return; };
}

//���뻺�棬�������һ��ֵ��ˢ�£��������档
bool buffer_store(int key, int value) {
	if ((InCache(key)!=-1) || tree.search(key))return false;

	vector<int> v;
	v.push_back(key); v.push_back(value);
	buffer.push_back(v);

	if (buffer.size() < capacity) {
	}
	else {
		for (int i = 0; i < buffer.size(); i++) {
			o_store(buffer[i][0], buffer[i][1]);
		}
		buffer.clear();
	}
	return true;
}

//���������ļ����д洢
bool o_store(int key, int value) {
	if (!valid(key, value)) {  return false; }
	idx.seekg(0, ios::end);
	if (!tree.search(key)) {
		int index;
		if (DeleteLocation.size() != 0) {
			index = DeleteLocation[DeleteLocation.size() - 1];
			DeleteLocation.pop_back();
		}
		else {
			datafile.seekg(0, ios::end);       //����ַΪ�ļ���������ƫ�Ƶ�ַΪ0������ָ�붨λ���ļ�������
			streampos sp = datafile.tellg();			//spΪ��λָ�룬��Ϊ�����ļ�������������Ҳ�����ļ��Ĵ�С,�õ������λ�á�
			index = sp;
		}
		datafile.seekg(index, ios::beg);
		datafile << key << " " << value << endl;
		tree.insert(key, index);	//���뵽������
		idx << key << " " << index; //д�뵽�����ļ���
		return true;
	}
	return false;
}

//�û��ô洢�ӿ�
void store(int key, int value) {
	if (!valid(key, value)) { cout << "�����ݲ�����Ҫ��" << endl; return; }
	if (buffer_store(key, value)) { cout << "�洢�ɹ�"<<endl; return; }
	else {
		cout << "����ʧ�ܣ��������Ѿ�����" << endl;
		return;
	}
}

//�޸�
bool o_modify(int key, int new_value) {
	if (!valid(key, new_value)) { cout << "������Ҫ��"; return false; }
	int InC = InCache(key);
	if (InC != -1) {
		buffer[InC][1] = new_value;
		return true;
	}
	if (!tree.search(key))return false;
	else {
		int location = tree.find(key);
		datafile.seekp(location, ios::beg);
		datafile << key << " " << new_value << endl;
		return true;
	}
}

//�û����޸Ľӿ�
void modify(int key, int new_value) {
	if (o_modify(key, new_value)) { cout << "���ĳɹ�" << endl; }
	else {
		cout << "����ʧ�ܣ������ݲ�����" << endl;
	}
}

//ɾ��
bool o_remove(int key) {
	int InC = InCache(key);
	if (InC != -1) {
		vector<vector<int>>transfer;
		for (int i = 0; i < InC; i++) {
			transfer.push_back(buffer[i]);
		}
		for (int j = InC + 1; j < buffer.size(); j++) {
			transfer.push_back(buffer[j]);
		}
		buffer = transfer;
		return true;
	}
	if (!tree.search(key))return false;
	else {
		int location = tree.find(key);
		datafile.seekp(location, ios::beg);
		datafile << 10000000 << " " << 10000000 << endl;//���ǵ�ԭ��������
		tree.remove(key);//��������ɾ��
		DeleteLocation.push_back(location);//�ѿ���ʹ�õĵ�ַ������
		return true;
	}
}

//�û���ɾ���ӿ�
void remove(int key) {
	if (o_remove(key)) { cout << "ɾ���ɹ�" << endl; return; }
	else {
		cout << "ɾ��ʧ�ܣ������ݲ�����" << endl;
	}
}



