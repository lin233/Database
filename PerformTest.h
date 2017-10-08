
#include"CorrectTest.h"
//性能测试

/*
TestOpen();
clock_t time1, time2;
time1 = clock();


time2 = clock();
double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
cout << "Time:" << time << endl;
TestClose();
return true;
*/

//空间性能测试
//创建重利用情况下的 20W - 7W + 20W 的数据 
void SpaceTest() {
	TestOpen();
	CBPlusTree TestTree;
	int Exist = 0;

	//插入20W条数据
	while (Exist < 200000) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		if (buffer_store(key, value))
		{
			Exist++;
			TestTree.insert(key, value);//记录原始插入数据
		}
	}

	vector<vector<int>>TestVec;
	TestVec = TestTree.ALL();
	
	//删除7W
	for (int i = 0; i < 70000; i++) {
		int key = TestVec[i][0];
		o_remove(key);
	}

	//再插入20W
	Exist = 0;
	while (Exist < 200000) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		if (buffer_store(key, value))
		{
			Exist++;
			TestTree.insert(key, value);//记录原始插入数据
		}
	}

	TestClose();
	cout << "DONE" << endl;
};


//模仿用户操作时间性能测试:有缓存
void TimeTest1_1(int NUM) {
	TestOpen();
	clock_t time1, time2;
	time1 = clock();
	int Exist = 0;
	
	for (int i = 0; i < NUM; i++) {
		int key;
		for (int j = 0; j < 10; j++) {
			key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
			int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			buffer_store(key, value);
			int behavior = rand() % 2;
			//随机查看
			if (behavior == 1) {
				o_search(key);
			}
			
			int behavior2 = rand() % 3;
			//随机修改
			if (behavior2 == 0) {
				int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
					rand() % 10 * 10000 + rand() % 10 * 1000 +
					rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
				o_modify(key, new_value);
			}
			//随机删除
			else if (behavior2 == 1) {
				o_remove(key);
			}
			else {};
		}

	}
	TestClose();
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "Time:" << time << endl;

	
	return;

}


//模仿用户操作时间性能测试:无缓存
void TimeTest1_2(int NUM) {
	TestOpen();
	clock_t time1, time2;
	time1 = clock();
	int Exist = 0;

	for (int i = 0; i < NUM; i++) {
		int key;
		for (int j = 0; j < 10; j++) {
			key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
			int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			o_store(key, value);
			int behavior = rand() % 2;
			//随机查看
			if (behavior == 1) {
				o_search(key);
			}

			int behavior2 = rand() % 3;
			//随机修改
			if (behavior2 == 0) {
				int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
					rand() % 10 * 10000 + rand() % 10 * 1000 +
					rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
				o_modify(key, new_value);
			}
			//随机删除
			else if (behavior2 == 1) {
				o_remove(key);
			}
			else {};
		}

	}
	TestClose();
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "Time:" << time << endl;

	
	return;


}


//时间性能测试：存储（有缓存）
void TimeTest2_1(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();

	int Exist = 0;
	while (Exist < NUM) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		buffer_store(key, value);
		Exist++;
	}
	close();
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "时间性能测试：存储（有缓存）: "<< NUM <<" Time:" << time << endl;
	
	return;
}

//时间性能测试：存储（无缓存）
void TimeTest2_2(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();

	int Exist = 0;
	while (Exist < NUM) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		o_store(key, value);
		Exist++;
	}
	close();
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "时间性能测试：存储（无缓存）: " << NUM << " Time:" << time << endl; 
	return;
}


//时间性能测试：查询
void TimeTest3(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();

	vector<vector<int>>TestVec = tree.ALL();

	int Exist = 0;
	while (Exist < NUM) {
		int r = rand() * 100 % (TestVec.size() - 1) + 1;
		o_search(TestVec[r][0]);
		Exist++;
	}
	
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "时间性能测试：查询: " << NUM << " Time:" << time << endl;
	close();
	return;
}


//时间性能测试：删除
void TimeTest4(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();

	vector<vector<int>>TestVec = tree.ALL();

	int Exist = 0;
	while (Exist < NUM) {
		int r = rand() * 100 % (TestVec.size() - 1) + 1;
		o_remove(TestVec[r][0]);
		Exist++;
	}
	
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "时间性能测试：删除: " << NUM << " Time:" << time << endl;
	close();
	return;
}


//时间性能测试：修改
void TimeTest5(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();
	
	vector<vector<int>>TestVec = tree.ALL();

	int Exist = 0;
	while (Exist < NUM) {
	
			int r = rand() * 100 % (TestVec.size() - 1) + 1;
			int key = TestVec[r][0];
			Exist++;

		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		o_modify(key,value);
		Exist++;
	}
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "时间性能测试：修改: " << NUM << " Time:" << time << endl; 
	close();
	return;
}



