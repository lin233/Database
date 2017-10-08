
#include"CorrectTest.h"
//���ܲ���

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

//�ռ����ܲ���
//��������������µ� 20W - 7W + 20W ������ 
void SpaceTest() {
	TestOpen();
	CBPlusTree TestTree;
	int Exist = 0;

	//����20W������
	while (Exist < 200000) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//��λ����Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		if (buffer_store(key, value))
		{
			Exist++;
			TestTree.insert(key, value);//��¼ԭʼ��������
		}
	}

	vector<vector<int>>TestVec;
	TestVec = TestTree.ALL();
	
	//ɾ��7W
	for (int i = 0; i < 70000; i++) {
		int key = TestVec[i][0];
		o_remove(key);
	}

	//�ٲ���20W
	Exist = 0;
	while (Exist < 200000) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//��λ����Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		if (buffer_store(key, value))
		{
			Exist++;
			TestTree.insert(key, value);//��¼ԭʼ��������
		}
	}

	TestClose();
	cout << "DONE" << endl;
};


//ģ���û�����ʱ�����ܲ���:�л���
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
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//��λ����Key
			int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			buffer_store(key, value);
			int behavior = rand() % 2;
			//����鿴
			if (behavior == 1) {
				o_search(key);
			}
			
			int behavior2 = rand() % 3;
			//����޸�
			if (behavior2 == 0) {
				int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
					rand() % 10 * 10000 + rand() % 10 * 1000 +
					rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
				o_modify(key, new_value);
			}
			//���ɾ��
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


//ģ���û�����ʱ�����ܲ���:�޻���
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
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//��λ����Key
			int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
				rand() % 10 * 10000 + rand() % 10 * 1000 +
				rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
			o_store(key, value);
			int behavior = rand() % 2;
			//����鿴
			if (behavior == 1) {
				o_search(key);
			}

			int behavior2 = rand() % 3;
			//����޸�
			if (behavior2 == 0) {
				int new_value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
					rand() % 10 * 10000 + rand() % 10 * 1000 +
					rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
				o_modify(key, new_value);
			}
			//���ɾ��
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


//ʱ�����ܲ��ԣ��洢���л��棩
void TimeTest2_1(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();

	int Exist = 0;
	while (Exist < NUM) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//��λ����Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		buffer_store(key, value);
		Exist++;
	}
	close();
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "ʱ�����ܲ��ԣ��洢���л��棩: "<< NUM <<" Time:" << time << endl;
	
	return;
}

//ʱ�����ܲ��ԣ��洢���޻��棩
void TimeTest2_2(int NUM) {
	open();
	clock_t time1, time2;
	time1 = clock();

	int Exist = 0;
	while (Exist < NUM) {
		int key = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;//��λ����Key
		int value = 10000000 + rand() % 10 * 1000000 + rand() % 10 * 100000 +
			rand() % 10 * 10000 + rand() % 10 * 1000 +
			rand() % 10 * 100 + rand() % 10 * 10 + rand() % 10;
		o_store(key, value);
		Exist++;
	}
	close();
	time2 = clock();
	double time = ((double)time2 - time1) / ((double)CLOCKS_PER_SEC);
	cout << "ʱ�����ܲ��ԣ��洢���޻��棩: " << NUM << " Time:" << time << endl; 
	return;
}


//ʱ�����ܲ��ԣ���ѯ
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
	cout << "ʱ�����ܲ��ԣ���ѯ: " << NUM << " Time:" << time << endl;
	close();
	return;
}


//ʱ�����ܲ��ԣ�ɾ��
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
	cout << "ʱ�����ܲ��ԣ�ɾ��: " << NUM << " Time:" << time << endl;
	close();
	return;
}


//ʱ�����ܲ��ԣ��޸�
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
	cout << "ʱ�����ܲ��ԣ��޸�: " << NUM << " Time:" << time << endl; 
	close();
	return;
}



