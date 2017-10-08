#include "Tree.h"  
#include <iostream>  
#include <algorithm>  
using namespace std;

CBPlusTree::CBPlusTree() {
	m_Root = NULL;
	m_DataHead = NULL;
}

CBPlusTree::~CBPlusTree() {
	clear();
}

bool CBPlusTree::insert(KeyType key, const DataType& data) {
	// �Ƿ��Ѿ�����  
	if (search(key))
	{
		return false;
	}
	// �ҵ����Բ����Ҷ�ӽ�㣬���򴴽��µ�Ҷ�ӽ��  
	if (m_Root == NULL)
	{
		m_Root = new CLeafNode();
		m_DataHead = (CLeafNode*)m_Root;
		m_MaxKey = key;
	}
	if (m_Root->getKeyNum() >= MAXNUM_KEY) // ���������������  
	{
		CInternalNode* newNode = new CInternalNode();  //�����µĸ��ڵ�  
		newNode->setChild(0, m_Root);
		m_Root->split(newNode, 0);    // Ҷ�ӽ�����  
		m_Root = newNode;  //���¸��ڵ�ָ��  
	}
	if (key>m_MaxKey)  // ��������ֵ  
	{
		m_MaxKey = key;
	}
	o_insert(m_Root, key, data);
	return true;
}

void CBPlusTree::o_insert(CNode* parentNode, KeyType key, const DataType& data)
{
	if (parentNode->getType() == LEAF)  // Ҷ�ӽ�㣬ֱ�Ӳ���  
	{
		((CLeafNode*)parentNode)->insert(key, data);
	}
	else
	{
		// �ҵ��ӽ��  
		int keyIndex = parentNode->getKeyIndex(key);
		int childIndex = parentNode->getChildIndex(key, keyIndex); // ���ӽ��ָ������  
		CNode* childNode = ((CInternalNode*)parentNode)->getChild(childIndex);
		if (childNode->getKeyNum() >= MAXNUM_LEAF)  // �ӽ������������з���  
		{
			childNode->split(parentNode, childIndex);
			if (parentNode->getKeyValue(childIndex) <= key)   // ȷ��Ŀ���ӽ��  
			{
				childNode = ((CInternalNode*)parentNode)->getChild(childIndex + 1);
			}
		}
		o_insert(childNode, key, data);
	}
}

void CBPlusTree::clear()
{
	if (m_Root != NULL)
	{
		m_Root->clear();
		delete m_Root;
		m_Root = NULL;
		m_DataHead = NULL;
	}
}

bool CBPlusTree::search(KeyType key)
{
	return o_search(m_Root, key);
}

bool CBPlusTree::o_search(CNode *pNode, KeyType key)const
{
	if (pNode == NULL)  //���ڵ�ָ���Ƿ�Ϊ�գ���ýڵ��Ƿ�ΪҶ�ӽڵ�  
	{
		return false;
	}
	else
	{
		int keyIndex = pNode->getKeyIndex(key);
		if (keyIndex < 0)return false;
		int childIndex = pNode->getChildIndex(key, keyIndex); // ���ӽ��ָ������  
		if (keyIndex<pNode->getKeyNum() && key == pNode->getKeyValue(keyIndex))
		{
			return true;
		}
		else
		{
			if (pNode->getType() == LEAF)   //���ýڵ��Ƿ�ΪҶ�ӽڵ�  
			{
				return false;
			}
			else
			{
				return o_search(((CInternalNode*)pNode)->getChild(childIndex), key);
			}
		}
	}
}

int  CBPlusTree::find(KeyType key) {
	bool x = search(key);
	//int y = select(key, EQ)[0];
	if (x) {
		return select(key, EQ)[0];
	}
	return -1;
}

void CBPlusTree::print()const
{
	printInConcavo(m_Root, 10);
}	 

void CBPlusTree::printInConcavo(CNode *pNode, int count) const {
	if (pNode != NULL)
	{
		int i, j;
		for (i = 0; i<pNode->getKeyNum(); ++i)
		{
			if (pNode->getType() != LEAF)
			{
				printInConcavo(((CInternalNode*)pNode)->getChild(i), count - 2);
			}
			for (j = count; j >= 0; --j)
			{
				cout << "-";
			}
			cout << pNode->getKeyValue(i) << endl;
		}
		if (pNode->getType() != LEAF)
		{
			printInConcavo(((CInternalNode*)pNode)->getChild(i), count - 2);
		}
	}
}

void CBPlusTree::printData()const
{
	CLeafNode* itr = m_DataHead;
	while (itr != NULL)
	{
		for (int i = 0; i<itr->getKeyNum(); ++i)
		{
			cout << itr->getData(i) << " ";
		}
		cout << endl;
		itr = itr->getRightSibling();
	}
}

bool CBPlusTree::remove(KeyType key)
{
	if (!search(key))  //������  
	{
		return false;
	}
	if (m_Root->getKeyNum() == 1)//�����������  
	{
		if (m_Root->getType() == LEAF)
		{
			clear();
			return true;
		}
		else
		{
			CNode *pChild1 = ((CInternalNode*)m_Root)->getChild(0);
			CNode *pChild2 = ((CInternalNode*)m_Root)->getChild(1);
			if (pChild1->getKeyNum() == MINNUM_KEY && pChild2->getKeyNum() == MINNUM_KEY)
			{
				pChild1->mergeChild(m_Root, pChild2, 0);
				delete m_Root;
				m_Root = pChild1;
			}
		}
	}
	o_remove(m_Root, key);
	return true;
}

vector<vector<int>> CBPlusTree::ALL() {
	CLeafNode* itr = m_DataHead;
	vector<vector<int>> VecTree;
	while (itr != NULL)
	{
		for (int i = 0; i<itr->getKeyNum(); ++i)
		{
			vector<int> v;
			v.push_back(itr->getKeyValue(i));
			v.push_back(itr->getData(i));
			//cout<<itr->getKeyValue(i)<<" "<< itr->getData(i);
			//cout << endl;
			VecTree.push_back(v);
		}
		itr = itr->getRightSibling();
	}
	return VecTree;
}

// parentNode�а����ļ�ֵ��>MINNUM_KEY  
void CBPlusTree::o_remove(CNode* parentNode, KeyType key)
{
	int keyIndex = parentNode->getKeyIndex(key);
	int childIndex = parentNode->getChildIndex(key, keyIndex); // ���ӽ��ָ������  
	if (parentNode->getType() == LEAF)// �ҵ�Ŀ��Ҷ�ӽڵ�  
	{
		if (key == m_MaxKey&&keyIndex>0)
		{
			m_MaxKey = parentNode->getKeyValue(keyIndex - 1);
		}
		parentNode->removeKey(keyIndex, childIndex);  // ֱ��ɾ��  
													  // �����ֵ���ڲ�����д��ڣ�ҲҪ��Ӧ���滻�ڲ����  
		if (childIndex == 0 && m_Root->getType() != LEAF && parentNode != m_DataHead)
		{
			changeKey(m_Root, key, parentNode->getKeyValue(0));
		}
	}
	else // �ڽ��  
	{
		CNode *pChildNode = ((CInternalNode*)parentNode)->getChild(childIndex); //����key���������ڵ�  
		if (pChildNode->getKeyNum() == MINNUM_KEY)                       // �����ؼ��ִﵽ����ֵ��������ز���  
		{
			CNode *pLeft = childIndex>0 ? ((CInternalNode*)parentNode)->getChild(childIndex - 1) : NULL;                       //���ֵܽڵ�  
			CNode *pRight = childIndex<parentNode->getKeyNum() ? ((CInternalNode*)parentNode)->getChild(childIndex + 1) : NULL;//���ֵܽڵ�  
																															   // �ȿ��Ǵ��ֵܽ���н�  
			if (pLeft && pLeft->getKeyNum()>MINNUM_KEY)// ���ֵܽ��ɽ�  
			{
				pChildNode->borrowFrom(pLeft, parentNode, childIndex - 1, LEFT);
			}
			else if (pRight && pRight->getKeyNum()>MINNUM_KEY)//���ֵܽ��ɽ�  
			{
				pChildNode->borrowFrom(pRight, parentNode, childIndex, RIGHT);
			}
			//�����ֵܽڵ㶼���ɽ裬���Ǻϲ�  
			else if (pLeft)                    //�����ֵܺϲ�  
			{
				pLeft->mergeChild(parentNode, pChildNode, childIndex - 1);
				pChildNode = pLeft;
			}
			else if (pRight)                   //�����ֵܺϲ�  
			{
				pChildNode->mergeChild(parentNode, pRight, childIndex);
			}
		}
		o_remove(pChildNode, key);
	}
}

void CBPlusTree::changeKey(CNode *pNode, KeyType oldKey, KeyType newKey)
{
	if (pNode != NULL && pNode->getType() != LEAF)
	{
		int keyIndex = pNode->getKeyIndex(oldKey);
		if (keyIndex<pNode->getKeyNum() && oldKey == pNode->getKeyValue(keyIndex))  // �ҵ�  
		{
			pNode->setKeyValue(keyIndex, newKey);
		}
		else   // ������  
		{
			changeKey(((CInternalNode*)pNode)->getChild(keyIndex), oldKey, newKey);
		}
	}
}

bool CBPlusTree::update(KeyType oldKey, KeyType newKey)
{
	if (search(newKey)) // �����º�ļ��Ƿ��Ѿ�����  
	{
		return false;
	}
	else
	{
		int dataValue;
		remove(oldKey, dataValue);
		if (dataValue == INVALID_INDEX)
		{
			return false;
		}
		else
		{
			return insert(newKey, dataValue);
		}
	}
}

void CBPlusTree::remove(KeyType key, DataType& dataValue)
{
	if (!search(key))  //������  
	{
		dataValue = INVALID_INDEX;
		return;
	}
	if (m_Root->getKeyNum() == 1)//�����������  
	{
		if (m_Root->getType() == LEAF)
		{
			dataValue = ((CLeafNode*)m_Root)->getData(0);
			clear();
			return;
		}
		else
		{
			CNode *pChild1 = ((CInternalNode*)m_Root)->getChild(0);
			CNode *pChild2 = ((CInternalNode*)m_Root)->getChild(1);
			if (pChild1->getKeyNum() == MINNUM_KEY && pChild2->getKeyNum() == MINNUM_KEY)
			{
				pChild1->mergeChild(m_Root, pChild2, 0);
				delete m_Root;
				m_Root = pChild1;
			}
		}
	}
	o_remove(m_Root, key, dataValue);
}

void CBPlusTree::o_remove(CNode* parentNode, KeyType key, DataType& dataValue)
{
	int keyIndex = parentNode->getKeyIndex(key);
	int childIndex = parentNode->getChildIndex(key, keyIndex); // ���ӽ��ָ������  
	if (parentNode->getType() == LEAF)// �ҵ�Ŀ��Ҷ�ӽڵ�  
	{
		if (key == m_MaxKey&&keyIndex>0)
		{
			m_MaxKey = parentNode->getKeyValue(keyIndex - 1);
		}
		dataValue = ((CLeafNode*)parentNode)->getData(keyIndex);
		parentNode->removeKey(keyIndex, childIndex);  // ֱ��ɾ��  
													  // �����ֵ���ڲ�����д��ڣ�ҲҪ��Ӧ���滻�ڲ����  
		if (childIndex == 0 && m_Root->getType() != LEAF && parentNode != m_DataHead)
		{
			changeKey(m_Root, key, parentNode->getKeyValue(0));
		}
	}
	else // �ڽ��  
	{
		CNode *pChildNode = ((CInternalNode*)parentNode)->getChild(childIndex); //����key���������ڵ�  
		if (pChildNode->getKeyNum() == MINNUM_KEY)                       // �����ؼ��ִﵽ����ֵ��������ز���  
		{
			CNode *pLeft = childIndex>0 ? ((CInternalNode*)parentNode)->getChild(childIndex - 1) : NULL;                       //���ֵܽڵ�  
			CNode *pRight = childIndex<parentNode->getKeyNum() ? ((CInternalNode*)parentNode)->getChild(childIndex + 1) : NULL;//���ֵܽڵ�  
																															   // �ȿ��Ǵ��ֵܽ���н�  
			if (pLeft && pLeft->getKeyNum()>MINNUM_KEY)// ���ֵܽ��ɽ�  
			{
				pChildNode->borrowFrom(pLeft, parentNode, childIndex - 1, LEFT);
			}
			else if (pRight && pRight->getKeyNum()>MINNUM_KEY)//���ֵܽ��ɽ�  
			{
				pChildNode->borrowFrom(pRight, parentNode, childIndex, RIGHT);
			}
			//�����ֵܽڵ㶼���ɽ裬���Ǻϲ�  
			else if (pLeft)                    //�����ֵܺϲ�  
			{
				pLeft->mergeChild(parentNode, pChildNode, childIndex - 1);
				pChildNode = pLeft;
			}
			else if (pRight)                   //�����ֵܺϲ�  
			{
				pChildNode->mergeChild(parentNode, pRight, childIndex);
			}
		}
		o_remove(pChildNode, key, dataValue);
	}
}


vector<DataType> CBPlusTree::select(KeyType compareKey, int compareOpeartor)
{
	vector<DataType> results;
	if (m_Root != NULL)
	{
		if (compareKey>m_MaxKey)   // �Ƚϼ�ֵ����B+�������ļ�ֵ  
		{
			if (compareOpeartor == LE || compareOpeartor == LT)
			{
				for (CLeafNode* itr = m_DataHead; itr != NULL; itr = itr->getRightSibling())
				{
					for (int i = 0; i < itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
				}
			}
		}
		else if (compareKey<m_DataHead->getKeyValue(0))  // �Ƚϼ�ֵС��B+������С�ļ�ֵ  
		{
			if (compareOpeartor == BE || compareOpeartor == BT)
			{
				for (CLeafNode* itr = m_DataHead; itr != NULL; itr = itr->getRightSibling())
				{
					for (int i = 0; i<itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
				}
			}
		}
		else  // �Ƚϼ�ֵ��B+����  
		{
			SelectResult result;
			search(compareKey, result);
			switch (compareOpeartor)
			{
			case LT:
			case LE:
			{
				CLeafNode* itr = m_DataHead;
				int i;
				while (itr != result.targetNode)
				{
					for (i = 0; i<itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
					itr = itr->getRightSibling();
				}
				for (i = 0; i<result.keyIndex; ++i)
				{
					results.push_back(itr->getData(i));
				}
				if (itr->getKeyValue(i)<compareKey ||
					(compareOpeartor == LE && compareKey == itr->getKeyValue(i)))
				{
					results.push_back(itr->getData(i));
				}
			}
			break;
			case EQ:
			{
				if (result.targetNode->getKeyValue(result.keyIndex) == compareKey)
				{
					results.push_back(result.targetNode->getData(result.keyIndex));
				}
			}
			break;
			case BE:
			case BT:
			{
				CLeafNode* itr = result.targetNode;
				if (compareKey<itr->getKeyValue(result.keyIndex) ||
					(compareOpeartor == BE && compareKey == itr->getKeyValue(result.keyIndex))
					)
				{
					results.push_back(itr->getData(result.keyIndex));
				}
				int i;
				for (i = result.keyIndex + 1; i<itr->getKeyNum(); ++i)
				{
					results.push_back(itr->getData(i));
				}
				itr = itr->getRightSibling();
				while (itr != NULL)
				{
					for (i = 0; i<itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
					itr = itr->getRightSibling();
				}
			}
			break;
			default:  // ��Χ��ѯ  
				break;
			}
		}
	}
	sort<vector<DataType>::iterator>(results.begin(), results.end());
	return results;
}

/*
vector<DataType> CBPlusTree::select(KeyType smallKey, KeyType largeKey)
{
	vector<DataType> results;
	if (smallKey <= largeKey)
	{
		SelectResult start, end;
		search(smallKey, start);
		search(largeKey, end);
		CLeafNode* itr = start.targetNode;
		int i = start.keyIndex;
		if (itr->getKeyValue(i)<smallKey)
		{
			++i;
		}
		if (end.targetNode->getKeyValue(end.keyIndex)>largeKey)
		{
			--end.keyIndex;
		}
		while (itr != end.targetNode)
		{
			for (; i<itr->getKeyNum(); ++i)
			{
				results.push_back(itr->getData(i));
			}
			itr = itr->getRightSibling();
			i = 0;
		}
		for (; i <= end.keyIndex; ++i)
		{
			results.push_back(itr->getData(i));
		}
	}
	sort<vector<DataType>::iterator>(results.begin(), results.end());
	return results;
}*/

void CBPlusTree::search(KeyType key, SelectResult& result)
{
	o_search(m_Root, key, result);
}

void CBPlusTree::o_search(CNode* pNode, KeyType key, SelectResult& result)
{
	int keyIndex = pNode->getKeyIndex(key);
	int childIndex = pNode->getChildIndex(key, keyIndex); // ���ӽ��ָ������  
	if (pNode->getType() == LEAF)
	{
		result.keyIndex = keyIndex;
		result.targetNode = (CLeafNode*)pNode;
		return;
	}
	else
	{
		return o_search(((CInternalNode*)pNode)->getChild(childIndex), key, result);
	}
}

bool CBPlusTree::modify(KeyType oldKey, const DataType& newdata) {
	bool IsExist = remove(oldKey);
	if (IsExist) {
		insert(oldKey, newdata);
	}
	return IsExist;
}
