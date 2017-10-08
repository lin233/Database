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

//如果数据库存在，就打开，不存在就创建，读取索引文件建立B+树，以及读取可重利用的地址建立vector。
void open() {
	//打开数据文件
	datafile.open("data.txt");
	if (!datafile.is_open()) {
		ofstream x;
		x.open("data.txt");
		x.close();
		datafile.open("data.txt");
	}
	//打开索引文件，建立B+树
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
	//打开重利用地址文件
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

//测试函数用的创建方式，用的都是新建的数据库，方便比对操作。
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

//刷新索引文件和重利用地址文件,刷新数据文件，写缓存。
void TestClose() {
	//刷新重利用的地址文件
	ofstream DeleteIdx("TestDeleteidx.txt", ios::trunc);
	for (int i = 0; i < DeleteLocation.size(); i++) {
		DeleteIdx << DeleteLocation[i] << endl;
	}
	DeleteIdx.close();

	//刷新索引文件
	ofstream idx("Testidx.txt", ios::trunc);
	vector<vector<int>>LocationIdx = tree.ALL();
	for (int i = 0; i < LocationIdx.size(); i++) {
		idx << LocationIdx[i][0] << " " << LocationIdx[i][1] << endl;
	}
	idx.close();

	//刷新数据文件，把缓存中的数据全部存入
	for (int i = 0; i < buffer.size(); i++) {
		o_store(buffer[i][0], buffer[i][1]);
	}
	buffer.clear();
	datafile.close();

	tree.clear();

}


//刷新索引文件和重利用地址文件,刷新数据文件，写缓存。
void close() {
	//刷新重利用的地址文件
	ofstream DeleteIdx("DeleteIdx.txt", ios::trunc);
	for (int i = 0; i < DeleteLocation.size(); i++) {
		DeleteIdx << DeleteLocation[i] << endl;
	}
	DeleteIdx.close();

	//刷新索引文件
	ofstream idx("idx.txt", ios::trunc);
	vector<vector<int>>LocationIdx = tree.ALL();
	for (int i = 0; i < LocationIdx.size(); i++) {
		idx << LocationIdx[i][0] << " " << LocationIdx[i][1] << endl;
	}
	idx.close();

	//刷新数据文件，把缓存中的数据全部存入
	for (int i = 0; i < buffer.size(); i++) {
		o_store(buffer[i][0], buffer[i][1]);
	}
	buffer.clear();
	datafile.close();

}

//判断是否合理。key是八位数的int，内容也是八位数的int.大于一千万且小于一亿的数。
bool valid(int key, int value) {
	if ((key <= 10000000) || (key > 99999999))return false;
	if ((value <= 10000000) || (value > 99999999))return false;
	return true;
}

//判断是否在缓存中
int InCache(int key) {
	for (int i = 0; i < buffer.size(); i++) {
		if (key == buffer[i][0])return i;
	}
	return -1;
}

//查找，查找成功返回value，失败返回-1.
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
	return -1;//因为value是大于一千万的，所以可以用-1做失败的标志
}

//查找测试
bool searchExam(int key, int CorrectValue) {
	return (o_search(key) == CorrectValue);
}

//用户用查找接口
void search(int key) {
	int value = o_search(key);
	if (value != -1) { cout << key << " " << value << endl; return; }
	else { cout << "查找失败，该数据不存在" << endl; return; };
}

//存入缓存，如果超过一定值就刷新，并清理缓存。
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

//对于数据文件进行存储
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
			datafile.seekg(0, ios::end);       //基地址为文件结束处，偏移地址为0，于是指针定位在文件结束处
			streampos sp = datafile.tellg();			//sp为定位指针，因为它在文件结束处，所以也就是文件的大小,得到插入的位置。
			index = sp;
		}
		datafile.seekg(index, ios::beg);
		datafile << key << " " << value << endl;
		tree.insert(key, index);	//插入到树里面
		idx << key << " " << index; //写入到索引文件里
		return true;
	}
	return false;
}

//用户用存储接口
void store(int key, int value) {
	if (!valid(key, value)) { cout << "该数据不符合要求" << endl; return; }
	if (buffer_store(key, value)) { cout << "存储成功"<<endl; return; }
	else {
		cout << "插入失败，该数据已经存在" << endl;
		return;
	}
}

//修改
bool o_modify(int key, int new_value) {
	if (!valid(key, new_value)) { cout << "不符合要求"; return false; }
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

//用户用修改接口
void modify(int key, int new_value) {
	if (o_modify(key, new_value)) { cout << "更改成功" << endl; }
	else {
		cout << "更改失败，该数据不存在" << endl;
	}
}

//删除
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
		datafile << 10000000 << " " << 10000000 << endl;//覆盖掉原来的内容
		tree.remove(key);//从树里面删除
		DeleteLocation.push_back(location);//把可以使用的地址存起来
		return true;
	}
}

//用户用删除接口
void remove(int key) {
	if (o_remove(key)) { cout << "删除成功" << endl; return; }
	else {
		cout << "删除失败，该数据不存在" << endl;
	}
}



