#include"handle.h"

//正确性测试

//⼤量数据测试
bool test1(int TIMES);

//非寻常测试
bool test2(int TIMES);

// 综合测试
bool test3(int nrec);

bool test1(int TIMES) {
	TestOpen();
	clock_t time1, time2;
	time1 = clock();
	int Exist = 0;
	CBPlusTree TestTree;

	cout << "TIMES:" << TIMES << endl;

	//数据生成
	while (Exist < TIMES) {
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


	//记录原始插入数据
	vector<vector<int>>TestVec = TestTree.ALL();

	//随机删除数据
	int a = (rand() % 10 * 1000000 + rand() % 10 * 100000 +
		rand() % 10 * 10000 + rand() % 10 * 1000 +
		rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10) % TIMES;

	for (int i = 0; i < a; i++) {
		int r = rand() * 100 % (TestVec.size() - 1) + 1;
		o_remove(TestVec[r][0]);
		TestTree.remove(TestVec[r][0]);
	}

	//读取全部数据，第一次比对
	for (int i = 0; i < TestVec.size(); i++) {
		int key = TestVec[i][0];
		int CorretValue = TestTree.find(key);
		if (!searchExam(key, CorretValue)) { cout << "第一次比对：失败" << endl; return false; }//测试不通过就返回
	}
	cout << "第一次比对：成功" << endl;

	//随机修改数据
	int b = (rand() % 10 * 1000000 + rand() % 10 * 100000 +
		rand() % 10 * 10000 + rand() % 10 * 1000 +
		rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10) % TIMES;
	for (int i = 0; i < b; i++) {
		int r = rand() * 100 % (TestVec.size() - 1);
		int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		o_modify(TestVec[r][0], new_value);		 //修改数据
		TestTree.modify(TestVec[r][0], new_value);//修改对比数据
	}


	//读取全部数据，第二次比对
	for (int i = 0; i < TestVec.size(); i++) {
		int key = TestVec[i][0];
		int CorretValue = TestTree.find(key);
		if (!searchExam(key, CorretValue)) { cout << "第二次比对：失败" << endl; return false; }//测试不通过就返回
	}
	cout << "第二次比对：成功" << endl;

	//随机插入
	while (Exist < TIMES) {
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

	//读取全部数据，第三次比对。
	TestVec = TestTree.ALL();

	for (int i = 0; i < TestVec.size(); i++) {
		int key = TestVec[i][0];
		int CorretValue = TestTree.find(key);
		if (!searchExam(key, CorretValue)) { cout << "第三次比对：失败" << endl; return false; }//测试不通过就返回
	}
	cout << "第三次比对：成功" << endl;


	time2 = clock();

	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);

	cout << "Time:" << time << endl;

	TestClose();
	return true;

}


bool test2(int TIMES) {
	TestOpen();
	clock_t time1, time2;
	time1 = clock();
	int Exist = 0;
	CBPlusTree TestTree;

	cout << "TIMES:" << TIMES << endl;

	//数据生成
	while (Exist < TIMES) {
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

	int x = rand() * 100 % TIMES;
	for (int i = 0; i < x; i++) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;

		if (!o_search(key)) {
			o_store(key, value);
			if (o_search(key) != value) {
				cout << "fail" << endl; return false;
			}

			o_remove(key);
			if (o_search(key) != -1) {
				cout << "fail" << endl; return false;
			}

			o_remove(key);
			if (o_search(key) != -1) {
				cout << "fail" << endl; return false;
			}

			int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			o_modify(key, new_value);

			if (o_search(key) != -1) {
				cout << "fail" << endl; return false;
			}

			int new_value2 = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			o_store(key, new_value2);
			if (o_search(key) != new_value2) {
				cout << "fail" << endl; return false;
			}

		}
	}

	cout << "Test2:成功" << endl;
	time2 = clock();

	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);

	cout << "Time:" << time << endl;

	TestClose();
	return true;
}


bool test3(int nrec) {
	TestOpen();
	clock_t time1, time2;
	time1 = clock();
	int Exist = 0;
	CBPlusTree TestTree;

	cout << "TIMES:" << nrec << endl;

	while (Exist < nrec) {
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

	//记录原始插入数据
	vector<vector<int>>TestVec = TestTree.ALL();

	//TestVec用做记录所有操作过的数据

	for (int i = 0; i < 10000; i++) {

		//随机读取一条记录
		int x = rand() * 100 % TestVec.size();
		int key = TestVec[x][0];
		int value = TestTree.find(key);
		if (!searchExam(key, value)) {
			cout << "fail" << endl; return false;
		}

		//每循环37次，随机删除一条记录
		if (i % 37 == 0) {
			//TestVec = TestTree.ALL();
			int x = rand() * 100 % TestVec.size();
			int key = TestVec[x][0];
			o_remove(key);
			TestTree.remove(key);
		}

		//每循环11次，随机添加一条记录并读取
		if (i % 11 == 0) {
			int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//八位数的Key
			int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			if (buffer_store(key, value))//添加成功
			{
				TestTree.insert(key, value);//记录原始插入数据
				vector<int>v;
				v.push_back(key); v.push_back(value);
				TestVec.push_back(v);//添加操作过的数据到vector
			}
			int CorrectValue = TestTree.find(key);
			if (!searchExam(key, CorrectValue)) {
				cout << "fail" << endl; return false;
			}
		}

		//每循环17次，随机替换一条记录为新记录
		if (i % 17 == 0) {
			//TestVec = TestTree.ALL();
			int x = rand() * 100 % TestVec.size();
			int key = TestVec[x][0];
			int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			o_modify(key, new_value);
			TestTree.modify(key, new_value);
		}

	}



	cout << "Test3:成功" << endl;
	time2 = clock();

	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);

	cout << "Time:" << time << "s" << endl;

	TestClose();
	return true;


}



