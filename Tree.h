#ifndef BPLUS_TREE_H  
#define BPLUS_TREE_H  

#include "BPlusNode.h"  
#include <vector>  
using namespace std;

enum COMPARE_OPERATOR { LT, LE, EQ, BE, BT, BETWEEN }; // �Ƚϲ�������<��<=��=��>=��>��<>  
const int INVALID_INDEX = -1;

struct SelectResult
{
	int keyIndex;
	CLeafNode* targetNode;
};

class CBPlusTree {
public:
	CBPlusTree();
	~CBPlusTree();
	bool insert(KeyType key, const DataType& data);
	bool remove(KeyType key);
	bool update(KeyType oldKey, KeyType newKey);
	bool modify(KeyType oldKey, const DataType& newdata);
	// ��ֵ��ѯ��compareOperator������<��<=��=��>=��>
	vector<DataType> select(KeyType compareKey, int compareOpeartor);
	// ��Χ��ѯ��BETWEEN  
	//vector<DataType> select(KeyType smallKey, KeyType largeKey);
	vector<vector<int>> ALL(); //�Զ�ά�������ʽ�����������������<key,value>��
	bool search(KeyType key); // �����Ƿ����  
	int find(KeyType key);		//�ҵ�key��value�ͷ��أ������ھͷ���-1
	void clear();             // ���  
	void print()const;        // ��ӡ���ؼ���  
	void printData()const;    // ��ӡ����  

private:
	void o_insert(CNode* parentNode, KeyType key, const DataType& data);
	void o_remove(CNode* parentNode, KeyType key);
	void printInConcavo(CNode *pNode, int count)const;
	bool o_search(CNode *pNode, KeyType key)const;
	void changeKey(CNode *pNode, KeyType oldKey, KeyType newKey);
	void search(KeyType key, SelectResult& result);
	void o_search(CNode* pNode, KeyType key, SelectResult& result);
	void remove(KeyType key, DataType& dataValue);
	void o_remove(CNode* parentNode, KeyType key, DataType& dataValue);
private:
	CNode* m_Root;
	CLeafNode* m_DataHead;
	KeyType m_MaxKey;  // B+���е�����  
};

#endif  
#pragma once
