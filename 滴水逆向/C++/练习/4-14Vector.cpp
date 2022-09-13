#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

#define SUCCESS           		   1 // �ɹ�					
#define ERROR            		  -1 // ʧ��					
#define MALLOC_ERROR			  -2 // �����ڴ�ʧ��					
#define INDEX_ERROR		 		  -3 // �����������	



template <class T_ELE>
class Vector
{
public:
	Vector();
	Vector(DWORD dwSize);
	~Vector();
public:
	DWORD	at(DWORD dwIndex, OUT T_ELE* pEle);			//���ݸ����������õ�Ԫ��	
	DWORD   push_back(T_ELE Element);					//��Ԫ�ش洢���������һ��λ��	
	VOID	pop_back();									//ɾ�����һ��Ԫ��	
	DWORD	insert(DWORD dwIndex, T_ELE Element);		//��ָ��λ������һ��Ԫ��	
	DWORD	capacity();									//�����ڲ����ݵ�����£����ܴ洢����Ԫ��	
	VOID	clear();									//�������Ԫ��	
	BOOL	empty();									//�ж�Vector�Ƿ�Ϊ�� ����trueʱΪ��	
	DWORD	erase(DWORD dwIndex);						//ɾ��ָ��Ԫ��	
	DWORD	size();										//����VectorԪ�������Ĵ�С	
private:
	BOOL	expand();
private:
	DWORD  m_dwIndex;					//��һ����������	
	DWORD  m_dwIncrement;				//ÿ�����ݵĴ�С	
	DWORD  m_dwLen;						//��ǰ�����ĳ���	
	DWORD  m_dwInitSize;		  	    //Ĭ�ϳ�ʼ����С	
	T_ELE* m_pVector;					//����ָ��	
};

//��ʼ��
template <class T_ELE>
Vector<T_ELE>::Vector()
	:m_dwInitSize(100), m_dwIncrement(5)
{
	//1.��������Ϊm_dwInitSize��T_ELE����							
	m_pVector = new T_ELE[m_dwInitSize];

	//2.���´����Ŀռ��ʼ��							
	memset(m_pVector, 0, sizeof(T_ELE) * m_dwInitSize);

	//3.��������ֵ						
	m_dwIndex = 0;
	m_dwLen = m_dwInitSize;  //����
}

//��ʼ��
template <class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize)
	:m_dwIncrement(5)
{
	//1.��������ΪdwSize��T_ELE����		
	m_pVector = new T_ELE[dwSize];

	//2.���´����Ŀռ��ʼ��		
	memset(m_pVector, 0, sizeof(T_ELE) * dwSize);
	//3.��������ֵ		
	m_dwIndex = 0;
	m_dwLen = dwSize;
}	

//����
template <class T_ELE>
Vector<T_ELE>::~Vector()
{
	//�ͷſռ� delete[]		
	delete[] m_pVector;
	m_pVector = NULL;

}

// ��������
template <class T_ELE>
BOOL Vector<T_ELE>::expand()
{
	DWORD dwLenTemp = 0;
	T_ELE* pVectorTemp = NULL;

	// 1. �������Ӻ�ĳ���							
	dwLenTemp = m_dwLen + m_dwIncrement;
	// 2. ����ռ�	
	pVectorTemp = new T_ELE[dwLenTemp];
	memset(pVectorTemp, 0, sizeof(T_ELE) * dwLenTemp);
	// 3. �����ݸ��Ƶ��µĿռ�							
	memcpy(pVectorTemp, m_pVector, sizeof(T_ELE) * m_dwLen);
	// 4. �ͷ�ԭ���ռ�							
	delete[] m_pVector;
	m_pVector = pVectorTemp;
	pVectorTemp = NULL;
	// 5. Ϊ�������Ը�ֵ							
	m_dwLen = dwLenTemp;

	return true;
}

// β��
template <class T_ELE>
DWORD  Vector<T_ELE>::push_back(T_ELE Element)
{
	//1.�ж��Ƿ���Ҫ���ݣ������Ҫ�͵������ݵĺ���							
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}

	//2.���µ�Ԫ�ظ��Ƶ����������һ��λ��							
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(T_ELE));

	//3.�޸�����ֵ							
	m_dwIndex++;

	return SUCCESS;
}

//ָ������
template <class T_ELE>
DWORD  Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)
{
	//1.�ж������Ƿ��ں�������							
	if (dwIndex<0 || dwIndex>m_dwIndex)
	{
		return INDEX_ERROR;
	}
	//2.�ж��Ƿ���Ҫ���ݣ������Ҫ�͵������ݵĺ���							
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	//3.��dwIndexֻ���Ԫ�غ���							
	for (DWORD i = m_dwIndex; i > dwIndex; i--)
	{
		memcpy(&m_pVector[i], &m_pVector[i-1], sizeof(T_ELE));
	}

	//4.��ElementԪ�ظ��Ƶ�dwIndexλ��		
	memcpy(&m_pVector[dwIndex], &Element, sizeof(T_ELE));
	//5.�޸�����ֵ	
	m_dwIndex++;

	return SUCCESS;
}


template <class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle)
{
	//�ж������Ƿ��ں�������							
	if (dwIndex<0 || dwIndex>= m_dwIndex)
	{
		return INDEX_ERROR;
	}

	//��dwIndex��ֵ���Ƶ�pEleָ�����ڴ�							
	memcpy(pEle, &m_pVector[dwIndex], sizeof(T_ELE));
	return SUCCESS;
}

//ɾ�����һ��Ԫ��		
template<class T_ELE>
VOID Vector<T_ELE>::pop_back()                  
{
	// m_dwIndex ��һ�����õ�����  --m_dwIndex ����һ������ Ҳ�������һ��Ԫ�� 
	memset(&m_pVector[m_dwIndex - 1], 0, sizeof(T_ELE));
	m_dwIndex--;
	
}


//�����ڲ����ݵ�����£����ܴ洢����Ԫ��	
template<class T_ELE>
DWORD Vector<T_ELE>::capacity()
{
	DWORD capacity = 0;   //�ܳ��� - ��һ������
	capacity = m_dwLen - m_dwIndex;

	return capacity;
}

//�ж�Vector�Ƿ�Ϊ�� ����trueʱΪ��	
template<class T_ELE>
BOOL Vector<T_ELE>::empty()
{
	if (m_dwIndex != 0 || m_pVector != NULL)
	{
		return SUCCESS;
	}

	return ERROR;
}

//�������Ԫ��
template<class T_ELE>
VOID Vector<T_ELE>::clear()
{
	//ȫ����ʼ��Ϊ 0 
	memset(m_pVector, 0, sizeof(T_ELE) * m_dwIndex);
	m_dwIndex = 0;
	m_dwLen = 0;

	delete[] m_pVector;
	m_pVector = NULL;
}

//ɾ��ָ��Ԫ��	
template<class T_ELE>
DWORD Vector<T_ELE>::erase(DWORD dwIndex)
{
	
	//�жϸ�ֵ�Ƿ� ����
	if (dwIndex<0 || dwIndex>m_dwIndex)
	{
		return INDEX_ERROR;
	}
	//��������  
	for (DWORD i = dwIndex; i < m_dwIndex; i++)
	{
		memcpy(&m_pVector[i], &m_pVector[i + 1], sizeof(T_ELE));
	}
	m_dwIndex--; //��������

	return SUCCESS;

}

//����VectorԪ�������Ĵ�С
template<class T_ELE>
DWORD Vector<T_ELE>::size()
{
	return m_dwIndex-1;
}

void TestVector()
{
	int sum = 0;
	Vector<int>* pVector = new Vector<int>(5);

	//����
	pVector->push_back(1);
	pVector->push_back(2);
	pVector->push_back(3);
	pVector->push_back(4);
	pVector->push_back(5);

	pVector->insert(3, 7);

	pVector->pop_back();
	pVector->erase(2);
}

int main()
{
	TestVector();

	return 0;
}


