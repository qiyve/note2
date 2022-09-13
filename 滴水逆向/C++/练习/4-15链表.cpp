#include<stdio.h>
#include<Windows.h>


#define SUCCESS           1 // ִ�гɹ�											
#define ERROR            -1 // ִ��ʧ��											
#define INDEX_IS_ERROR   -2 // �����������											
#define BUFFER_IS_EMPTY  -3 // �������ѿ�

template<class T_ELE> 
class NODE{
public:
	T_ELE Data;        
	NODE<T_ELE>* pNext;
};

template <class T_ELE>
class LinkedList :public NODE<T_ELE>
{
public:
	LinkedList();                           //Ĭ�Ϲ��캯��
	~LinkedList();
public:
	BOOL  IsEmpty();											//�ж������Ƿ�Ϊ�� �շ���1 �ǿշ���0				
	DWORD  Clear();												//�������				
	DWORD GetElement(IN DWORD dwIndex, OUT T_ELE& Element);		//����������ȡԪ��				
	DWORD GetElementIndex(IN T_ELE& Element);					//����Ԫ�ػ�ȡ�����е�����				
	DWORD Insert(IN T_ELE Element);								//����Ԫ��				
	DWORD Insert(IN DWORD dwIndex, IN T_ELE Element);			//������������Ԫ��				
	DWORD Delete(IN DWORD dwIndex);								//��������ɾ��Ԫ��				
	DWORD GetSize();											//��ȡ������Ԫ�ص�����
	VOID Show_Linke();												//��ӡ����		
private:
	NODE<T_ELE>* m_head;					//����ͷָ�룬ָ���һ���ڵ�				
	DWORD m_dwLength;						//Ԫ�ص�����				
};

//����
void test()
{
	LinkedList<int>Link;

	int index = 3;
	int value = 0;
	int element = 10;

	Link.Insert(0, 40);
	Link.Insert(1, 50);
	Link.Insert(2, 30);
	Link.Insert(3, 10);
	Link.Insert(4, 60);
	//Link.Insert(5, 70);


	//Link.Insert(20);
	//printf("Link.GetElementIndex(%d): %d\n", element, Link.GetElementIndex(element));

	Link.GetElement(index, value);
	printf("Link.GetElement(%d, %d)\n", index, value);

	Link.Delete(5);

	Link.Show_Linke();
}


int main()
{
	test();

	return 0;
}

//�޲ι��캯�� ��ʼ����Ա									
template<class T_ELE> 
LinkedList<T_ELE>::LinkedList()
	:m_head(NULL), m_dwLength(0)
{

}

//�������� ���Ԫ��									
template<class T_ELE>
LinkedList<T_ELE>::~LinkedList()
{
	Clear();
}

//�ж������Ƿ�Ϊ��									
template<class T_ELE>
BOOL LinkedList<T_ELE>::IsEmpty()
{
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}
	else
	{
		return SUCCESS;
	}
}

//�������									
template<class T_ELE> 
DWORD LinkedList<T_ELE>::Clear()
{
	// 1. �ж������Ƿ�Ϊ��	
	if (m_head == NULL || m_dwLength == 0)
	{
		return INDEX_IS_ERROR;
	}

	// 2. ѭ��ɾ�������еĽڵ�
	NODE<T_ELE>* pHead = m_head;
	for (DWORD i = 0; i < m_dwLength; i++)
	{
		//������ʱָ�����ͷŶ�����
		NODE<T_ELE>* pItertor = pHead;
		pHead = pHead->pNext;   // pHead ->pNext  ָ����һ���ڵ�
		delete pItertor;
	}
	// 3. ɾ�����һ���ڵ㲢����������Ϊ0
	m_head = NULL;
	m_dwLength = 0;

	return SUCCESS;
}


//����������ȡԪ��									
template<class T_ELE> 
DWORD LinkedList<T_ELE>::GetElement(IN DWORD dwIndex, OUT T_ELE& Element)
{
	NODE<T_ELE>* pTempNode = NULL;
	// 1. �ж������Ƿ���Ч	
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;
	}
	//2���ж������Ƿ�Ϊ��
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}

	// 3. ȡ������ָ��Ľڵ�
	pTempNode = m_head;
	for (DWORD i = 0; i < dwIndex; i++)
	{
		pTempNode = pTempNode->pNext;
	}

	// 3. ������ָ��ڵ��ֵ���Ƶ�OUT����	
	memcpy(&Element, &pTempNode->Data, sizeof(T_ELE));

	return SUCCESS;
}


//����Ԫ�����ݻ�ȡ����									
template<class T_ELE>
DWORD LinkedList<T_ELE>::GetElementIndex(IN T_ELE& Element)
{
	NODE<T_ELE>* pTempNode = NULL;
	//1���ж������Ƿ�Ϊ��
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}
	//2��ѭ�����������ҵ���ELement��ͬ��Ԫ��
	pTempNode = m_head;
	for (DWORD i = 0; i < m_dwLength; i++)
	{  
		//Ҳ����ͨ������ == �����бȽ� 
		if (!memcmp(&Element, &pTempNode->Data, sizeof(T_ELE)))
		{
			return i;
		}
		pTempNode = pTempNode->pNext;  
	}
	return ERROR;
}


//������β�������ڵ�									
template<class T_ELE> 
DWORD LinkedList<T_ELE>::Insert(IN T_ELE Element)
{
	//β�������ڵ�
	NODE<T_ELE>* pNewNode = new NODE<T_ELE>;
	memset(pNewNode, 0, sizeof(T_ELE));
	memcpy(&pNewNode->Data, &Element, sizeof(T_ELE));

	// 1. �ж������Ƿ�Ϊ��
	if (m_head == NULL || m_dwLength == 0)
	{
		m_head = pNewNode;
		m_dwLength++;
		return SUCCESS;
	}

	// 2. ����������Ѿ���Ԫ������ǰһ���ڵ�ָ����
	NODE<T_ELE>* pTempNode = m_head;
	for (DWORD i = 0; i < m_dwLength - 1; i++)  //m_dwLength - 1 ����һ���ڵ�
	{
		pTempNode = pTempNode->pNext;
	}
	pTempNode->pNext = pNewNode;
	m_dwLength++;

	return SUCCESS;
}

//���ڵ�������ָ��������λ��						0 1 2 3 4			
template<class T_ELE> DWORD
LinkedList<T_ELE>::Insert(IN DWORD dwIndex, IN T_ELE Element)
{
	NODE<T_ELE>* pPreviousNode = NULL;   //��һ�� �ڵ�
	NODE<T_ELE>* pCurrentNode = NULL;    //��ǰ  �ڵ�
	NODE<T_ELE>* pNextNode = NULL;		 //��һ���ڵ�

	//��� �ڵ�
	NODE<T_ELE>* pNewNode = new NODE<T_ELE>;
	memset(pNewNode, 0, sizeof(T_ELE));
	memcpy(&pNewNode->Data, &Element, sizeof(T_ELE));

	//  1. �ж�����ֵ�Ƿ���Ч		
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;
	}

	//  2. �ж������Ƿ�Ϊ�� ���� ����ֵΪ0 ֱ�����
	if (m_head == NULL || m_dwLength == 0)
	{
		if (dwIndex == 0)
		{		
			m_head = pNewNode;
			m_dwLength++;
			return SUCCESS;
		}
		return BUFFER_IS_EMPTY;
	}

	//  3. �������Ϊ0	
	if (dwIndex == 0)
	{
		// ����Ϊ 0 �� node->Next ָ��ͷָ��ָ��ĵ�ַ  ͷָ������ָ��Node��ֵ
		pNewNode->pNext = m_head;
		m_head = pNewNode;
		m_dwLength++;
		return SUCCESS;
	}

	//  4. �������Ϊ����β	
	if (dwIndex == m_dwLength)
	{
		pPreviousNode = m_head;
		for (DWORD i = 0; i < dwIndex - 1; i++) //ͨ��ѭ���ҵ�����β���Ľڵ�
		{
			pPreviousNode = pPreviousNode->pNext;
		}
		pPreviousNode->pNext = pNewNode;
		m_dwLength++;
		return SUCCESS;
	}

	//  5. �������Ϊ������
	pCurrentNode = m_head;
	for (DWORD i = 0; i < dwIndex - 1; i++) //dwIndex - 1 ��Ҫ��ӽڵ��λ��
	{
		pCurrentNode = pCurrentNode->pNext;
	}
	pNextNode = pCurrentNode->pNext;
	pCurrentNode->pNext = pNewNode;
	pNewNode->pNext = pNextNode;
	m_dwLength++;

	return SUCCESS;
}


//��������ɾ���ڵ�									
template<class T_ELE>
DWORD LinkedList<T_ELE>::Delete(IN DWORD dwIndex)
{
	NODE<T_ELE>* pPreviousNode = NULL;   //��һ�� �ڵ�
	NODE<T_ELE>* pCurrentNode = NULL;    //��ǰ  �ڵ�
	NODE<T_ELE>* pNextNode = NULL;		 //��һ���ڵ�

	//1���ж��Ƿ�����Ч����ֵ
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;
	}

	//2���ж������Ƿ�Ϊ��
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}

	//3�����������ֻ��ͷ�ڵ㣬��Ҫɾ��ͷ�ڵ�
	if (m_dwLength == 1 && dwIndex == 0)
	{
		delete m_head;
		m_head = NULL;
		m_dwLength--;
		return SUCCESS;
	}

	//4�����Ҫɾ����ͷ�ڵ�
	if (dwIndex == 0)
	{
		pNextNode = m_head->pNext;
		delete m_head;
		m_head = pNextNode;
		m_dwLength--;
		return SUCCESS;
	}
	//5���������������ڲ�
	pPreviousNode = m_head;
	for (DWORD i = 0; i < dwIndex - 1; i++)
	{
		pPreviousNode = pPreviousNode->pNext;   //��ȡ Ҫɾ���ڵ�� ��һ���ڵ�  A
	}
	pCurrentNode = pPreviousNode->pNext;    //��ȡҪɾ���ڵ�       B  
	pNextNode = pCurrentNode->pNext;        //��ȡҪɾ���ڵ����һ���ڵ�     C 
	pPreviousNode->pNext = pNextNode;       //����һ���ڵ�ָ�� ɾ���ڵ� ����һ���ڵ�   A -> C
	delete pCurrentNode;
	m_dwLength--;

	return SUCCESS;
}

//��ȡ�����нڵ������									
template<class T_ELE>
DWORD LinkedList<T_ELE>::GetSize()
{
	//�ж������Ƿ�Ϊ��   ��Ϊ���ؽڵ�����
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}

	else
	{
		return m_dwLength;
	}
}


template<class T_ELE> 
VOID LinkedList<T_ELE>::Show_Linke()
{
	if (m_head == NULL || m_dwLength == 0)
	{
		printf("����Ϊ��\n");
	}

	NODE<T_ELE>* pTempNode = m_head;
	for (DWORD i = 0; i < m_dwLength; i++)
	{
		printf("pNode->data: %d\n", pTempNode->Data);
		pTempNode = pTempNode->pNext;
	}
}
