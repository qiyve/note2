#include<stdio.h>
#include<Windows.h>

#define SUCCESS           1 // ִ�гɹ�						
#define ERROR			 -1 // ִ��ʧ��			         			

template<class T>
class TreeNode {
public:
	T element;					//��ǰ�ڵ�洢������			
	TreeNode<T>* pLeft;			//ָ�����ӽڵ��ָ��			
	TreeNode<T>* pRight;		//ָ�����ӽڵ��ָ��			
	TreeNode<T>* pParent;		//ָ�򸸽���ָ��			


	TreeNode(T& ele) {
		//��ʼ��Node�ڵ�							
		memset(&element, 0, sizeof(TreeNode));
		//ΪԪ�ظ�ֵ							
		memcpy(&element, &ele, sizeof(T));
		pLeft = pRight = pParent = NULL;
	}
	//����== �Ƚ�������Ƿ����								
	bool operator==(TreeNode<T>* node) {
		return node->element == element ? true : false;
	}
};

template<class T>
class BSortTree {
public:
	BSortTree();						//���캯��		
	~BSortTree();						//��������		
public:									//�ж����Ƿ�Ϊ��		
	bool IsEmpty();						//�����ڵ�		
	DWORD Insert(T element);							//ɾ���ڵ�		
	void Delete(T element);								
	TreeNode<T>* Search(T element);						//���ҽڵ�		
	void InOrderTraverse(TreeNode<T>* pNode);						//�������		
	void PreOrderTraverse(TreeNode<T>* pNode);						//ǰ�����		
	void PostOrderTraverse(TreeNode<T>* pNode);						//�������		
private:
	TreeNode<T>* GetMaxNode(TreeNode<T>* pNode);						//��ȡ��pNodeΪ�������ڵ�		
	TreeNode<T>* GetMinNode(TreeNode<T>* pNode);						//��ȡ��pNodeΪ������С�ڵ�		
	TreeNode<T>* SearchNode(TreeNode<T>* pNode, T element);				//��ȡ��pNodeΪ������С�ڵ�		
	DWORD InsertNode(T element, TreeNode<T>* pNode);					//�����ڵ�		
	TreeNode<T>* DeleteNode(T element, TreeNode<T>* pNode);				//ɾ���ڵ�		
	void Clear(TreeNode<T>* pNode);					//������нڵ�		
private:
	TreeNode<T>* m_pRoot;							//�����ָ��		
	int size;										//����Ԫ���ܸ���		
};


void test()
{
}

int main()
{


	return 0;
}

template<class T>
BSortTree<T>::BSortTree()
{
	m_pRoot = NULL;
	size = 0;
}

template<class T>
BSortTree<T>::~BSortTree() {

	Clear(m_pRoot);
}


template<class T>
DWORD BSortTree<T>::Insert(T element)
{
	//������ڵ�Ϊ��								
	if (!m_pRoot)
	{
		m_pRoot = new TreeNode<T>(element);
		size++;
		return SUCCESS;
	}
	//������ڵ㲻Ϊ��								
	return InsertNode(element, m_pRoot);
}

template<class T>
DWORD BSortTree<T>::InsertNode(T element, TreeNode<T>* pNode)
{
	//��Ԫ�ط�װ���ڵ���								
	TreeNode<T>* pNewNode = new TreeNode<T>(element);
	//���element == ��ǰ�ڵ� ֱ�ӷ���								
	if (element == pNode->element)
	{
		return SUCCESS;
	}
	//���pNode��������ΪNULL ����element < ��ǰ�ڵ�								
	if (pNode->pLeft == NULL && element < pNode->element)
	{
		pNode->pLeft = pNewNode;
		pNewNode->pParent = pNode;
		size++;
		return SUCCESS;
	}
	//���pNode��������ΪNULL ����element > ��ǰ�ڵ�								
	if (pNode->pRight == NULL && element > pNode->element) {
		pNode->pRight = pNewNode;
		pNewNode->pParent = pNode;
		size++;
		return SUCCESS;
	}
	//���element<��ǰ�ڵ� �ҵ�ǰ�ڵ����������Ϊ��								
	if (element < pNode->element)
	{
		InsertNode(element, pNode->pLeft);
	}
	else
	{
		InsertNode(element, pNode->pRight);
	}
	return SUCCESS;
}

template<class T>
void BSortTree<T>::Clear(TreeNode<T>* pNode)
{
	if (pNode != NULL)
	{
		Clear(pNode->pLeft);
		Clear(pNode->pRight);
		delete pNode;
		pNode = NULL;
	}
}

template<class T>
bool BSortTree<T>::IsEmpty()
{
	return size == 0 ? true : false;
}

template<class T>
TreeNode<T>* BSortTree<T>::Search(T element)
{
	return SearchNode(m_pRoot, element);
}

template<class T>
TreeNode<T>* BSortTree<T>::SearchNode(TreeNode<T>* pNode, T element)
{
	if (pNode == NULL)					//����ڵ�ΪNULL			
	{
		return NULL;
	}
	else if (element == pNode->element)					//������			
	{
		return pNode;
	}					//����Ƚڵ��Ԫ��С ������			
	else if (element < pNode->element)
	{
		return SearchNode(pNode->pLeft, element);
	}
	else				//����Ƚڵ��Ԫ�ش� ������			
	{
		return SearchNode(pNode->pRight, element);
	}
}

template<class T>
void BSortTree<T>::Delete(T element)
{
	if (m_pRoot == NULL)
	{
		return ERROR;
	}
	DeleteNode(element, m_pRoot);
}

template<class T>
TreeNode<T>* BSortTree<T>::DeleteNode(T element, TreeNode<T>* pNode)
{
	// ����
	if (m_pRoot == NULL)
	{
		return ERROR;
	}

	else if (element == pNode->element)
	{
		//1�� ֻ��������  û��������
		if (pNode->pLeft != NULL && pNode->pRight == NULL)
		{
			TreeNode<T>* pPt = pNode->pParent;//��ȡ ��ǰ�ڵ� �� ���ڵ�
			pPt->pLeft = pNode->pLeft;        // �ø��ڵ�������� ֱ�� ָ��ǰ�ڵ��������
			delete pNode;
		}
		//2�� ������Ϊ��  ֻ��������
		else if (pNode->pLeft == NULL && pNode->pRight != NULL)
		{
			TreeNode<T>* pPt = pNode->pParent; //��ȡ ��ǰ�ڵ� �� ���ڵ�
			pPt->pRight = pNode->pRight;	  // �ø��ڵ�������� ֱ�� ָ��ǰ�ڵ��������
			delete pNode;
		}
		
		//3������������Ϊ��
		else if (pNode->pLeft == NULL && pNode->pRight == NULL)
		{
			TreeNode<T>* p;
			p = pNode->pParent;
			if (p->pLeft != NULL && p->pRight == NULL) //����ʵ��������ǿ���ǰ�ڵ��ڸ��ڵ����߻����ұ�
			{
				delete p->pLeft;
				p->pLeft == NULL;
			}
			if (p->pLeft == NULL && p->pRight != NULL)
			{
				delete p->pRight;
				p->pRight = NULL;
			}

			delete p->pRight;
			p->pRight = NULL;  //�����о��Ǵ����ӽڵ�һ�����Ҳ�Ϊ�գ�ɾ���ĸ���һ����
		}

		//������������Ϊ��
		else if (pNode->pLeft != NULL && pNode->pRight != NULL)
		{
			TreeNode<T>* pCurrent = pNode->pRight;

			//GetMinNode��һ���ݹ麯��������NODE���������С�ڵ�
			TreeNode<T>* pMin = GetMinNode(pNode->pRight);

			//����С�Ľڵ�Ԫ��̧��pNode�ڵ�������
			pNode->element = (int)pMin;

			//��ʱ�˿̣�Pnode�Ѿ��滻Ϊ��С�ڵ��Ԫ���ˣ�
			//��ôֻ��Ҫɾ��pCurrent��pNode->pRight���µ�������С�ڵ�Ϳ����ˣ������õĵݹ顣
			DeleteNode(pNode->element, pCurrent);
		}
	}
	else if (element > pNode->element)
	{
		//Element ����pNode�� ֵ����ô����Pnode������ʼ��
		DeleteNode(element, pNode->pRight);
	}
	else
	{
		DeleteNode(element, pNode->pLeft);
	}

	return NULL;
}

template<class T>
TreeNode<T>* BSortTree<T>::GetMinNode(TreeNode<T>* pNode)
{
	TreeNode<T>* pMin = NULL;
	if (pNode != NULL)
	{
		/*˵һ�£�����Ϊʲô����T���ͣ���ΪT�����������ʹ�С����������ֻ��ҪNODEͷ4���ֽڵ�����,
		������һ�㲻ͨ�ã��ڵ��ͷ�ĸ��ֽ��������ͱ������ˡ�*/
		int data = pNode->element;
		if (data >= pNode->element)
		{
			pMin = (TreeNode<T>*)pNode->element;//����һ���Ƚ�С�Ľڵ������
		}

		GetMinNode(pNode->pLeft);
		return pMin;
	}
}

//�������	
template<class T>
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return ERROR;
	}
	InOrderTraverse(pNode->pLeft);
	printf("%d\n", pNode->element);
	InOrderTraverse(pNode->pRight);
}

//�������	
template<class T>
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return ERROR;
	}
	printf("%d\n", pNode->element);
	PreOrderTraverse(pNode->pLeft);
	PreOrderTraverse(pNode->pRight);

}

//�������	
template<class T>
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)				
{
	if (pNode == NULL)
	{
		return ERROR;
	}
	PostOrderTraverse(pNode->pLeft);
	PostOrderTraverse(pNode->pRight);
	printf("%d\n", pNode->element);
}
