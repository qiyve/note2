#include<stdio.h>
#include<Windows.h>


//�洢������Ϣ
class Monster
{
public:
	int ID;
	int Level;
	char Name[20];
public:
	Monster() {}
	Monster(int ID, int Level, const char* Name)
	{
		this->ID = ID;
		this->Level = Level;
		memcpy(&this->Name, Name, strlen(Name) + 1);
	}
};

//�洢���Ľڵ�
template<class T>
class TreeNode {
public:
	T element;					//��ǰ�ڵ�洢������  		
	TreeNode<T>* pLeft;			//ָ�����ӽڵ��ָ��			
	TreeNode<T>* pRight;		//ָ�����ӽڵ��ָ��			

	TreeNode(T& ele) {
		//��ʼ��Node�ڵ�							
		memset(&element, 0, sizeof(TreeNode));
		//ΪԪ�ظ�ֵ							
		memcpy(&element, &ele, sizeof(T));
		pLeft = pRight = NULL;
	}
};

template<class T>
class BSortTree {
public:
	BSortTree();					//���캯��			
	~BSortTree();					//��������			
public:
	void InOrderTraverse(TreeNode<T>* pNode);			//�������			
	void PreOrderTraverse(TreeNode<T>* pNode);			//ǰ�����			
	void PostOrderTraverse(TreeNode<T>* pNode);			//�������			
	TreeNode<T>* GetRoot();								//���ظ��ڵ�			
	int GetDepth(TreeNode<T>* pNode);					//����ĳ���ڵ�ĸ߶�/���			
private:
	void Init();   //��ʼ��������Ϣ
	void Clear(TreeNode<T>* pNode);  //�����ͷŶ���
private:
	TreeNode<T>* m_pRoot;		//�����ָ��			
	int size;					//����Ԫ���ܸ���			
};


int main()
{
	TreeNode<Monster>* m_pRoot = NULL;
	TreeNode<Monster>* m_pRoot2 = NULL;
	BSortTree<Monster> Bin;

	m_pRoot = Bin.GetRoot();
	Bin.GetDepth(m_pRoot);

	printf("----------------���� ----------------\n");
	Bin.PreOrderTraverse(m_pRoot);
	printf("---------------- ���� ----------------\n");
	Bin.InOrderTraverse(m_pRoot);
	printf("----------------����----------------\n");
	Bin.PostOrderTraverse(m_pRoot);

	return 0;
}



template<class T>
BSortTree<T>::BSortTree()
{
	Init();
}

template<class T>
BSortTree<T>::~BSortTree() {

	//�ͷ����Խڵ�ռ�								
	Clear(m_pRoot);
}
template<class T>
void BSortTree<T>::Clear(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return;
	}
	//��ɾ��������
	Destory(pNode->pLeft);
	//��ɾ��������
	Destory(pNode->pRight);
	delete pNode;
	pNode = NULL:
}

template<class T>
void BSortTree<T>::Init()
{
	//����������Ϣ
	Monster m1(1, 1, "���");
	Monster m2(2, 2, "Ұ��");
	Monster m3(3, 3, "Ұ��");
	Monster m4(4, 4, "ʿ��");
	Monster m5(5, 5, "����");
	Monster m6(6, 6, "������");
	Monster m7(7, 7, "�������");

	//���� ���ڵ�
	TreeNode<Monster>* n1 = new TreeNode<Monster>(m1);
	TreeNode<Monster>* n2 = new TreeNode<Monster>(m2);
	TreeNode<Monster>* n3 = new TreeNode<Monster>(m3);
	TreeNode<Monster>* n4 = new TreeNode<Monster>(m4);
	TreeNode<Monster>* n5 = new TreeNode<Monster>(m5);
	TreeNode<Monster>* n6 = new TreeNode<Monster>(m6);
	TreeNode<Monster>* n7 = new TreeNode<Monster>(m7);

	//��������ֵ
	m_pRoot = n5;
	n5->pLeft = n4;
	n5->pRight = n6;
	n4->pLeft = n1;
	n1->pRight = n2;
	n6->pLeft = n3;
	n3->pRight = n7;
	size = 7;
}

//���ظ��ڵ�
template<class T>
TreeNode<T>* BSortTree<T>::GetRoot()
{
	return m_pRoot;
}

//����ĳ���ڵ�ĸ߶�/���			
template<class T>
int BSortTree<T>::GetDepth(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return 0;
	}
	else
	{
		//�������
		int m = GetDepth(pNode->pLeft);
		int n = GetDepth(pNode->pRight);
		return (m > n) ? (m + 1) : (n + 1);
	}
}

//����������й���,�г��ֵ�����
template<class T>
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)
{

									
	if (pNode == NULL)
	{
		return;
	}

	// ���� �ڸ� ����
	InOrderTraverse(pNode->pLeft);
	printf("������%s \n", pNode->element.Name);
	InOrderTraverse(pNode->pRight);
}

//����������й���,�г��ֵ�����		
template<class T>
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return;
	}
	// �ȸ� ���� ����
	printf("������%s \n", pNode->element.Name);
	PreOrderTraverse(pNode->pLeft);
	PreOrderTraverse(pNode->pRight);
}

//����������й���,�г��ֵ�����								
template<class T>
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)
{

	if (pNode == NULL)
	{
		return;
	}

	// ���� ���� �ڸ�
	PostOrderTraverse(pNode->pLeft);
	PostOrderTraverse(pNode->pRight);
	printf("������%s \n", pNode->element.Name);
}

