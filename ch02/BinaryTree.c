#include<stdio.h>
#include<time.h>
#include<stdlib.h>
struct TreeNode;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode BinaryTree;
typedef int ElementType;

struct TreeNode
{
	ElementType Element;
	BinaryTree Left;
	BinaryTree Right;
};

/*统计树中节点个数*/
int CountNodes(BinaryTree T)
{
	if (T == NULL)
		return 0;
	else
		return CountNodes(T->Left) + CountNodes(T->Right) + 1;
}
/*统计树中树叶个数*/
int CountLeaves(BinaryTree T)
{
	if (T == NULL)
		return 0;
	else if (T->Left == NULL && T->Right == NULL)
		return 1;
	else
		return CountLeaves(T->Left) + CountLeaves(T->Right);
}
/*统计树中满节点个数*/
int CountFull(BinaryTree T)
{
	if (T == NULL)
		return 0;
	else
		return CountFull(T->Left) + CountFull(T->Right) + (T->Left != NULL && T->Right != NULL);
}
BinaryTree Insert(ElementType x, BinaryTree T)
{
	if (T == NULL)
	{
		T = malloc(sizeof(struct TreeNode));
		if (T == NULL)
			perror("Out of space!!!");
		else
		{
			T->Left = T->Right = NULL;
			T->Element = x;
		}

	}
	else
	{
		if (x < T->Element)
		{
			T->Left=Insert(x, T->Left);
		}
		else if (x > T->Element)
		{
			T->Right = Insert(x, T->Right);
		}
	}
	return T;
}
ElementType RandInt(int Lower, int Upper)
{
	return rand() % (Upper - Lower + 1) + Lower;
}
/*生成具有N个节点的随机二叉查找树，具有1-N的不同关键字*/
BinaryTree MakeRandomTree(int Lower,int Upper)
{
	BinaryTree T=NULL;
	ElementType RandomNum;
	if (Lower <= Upper)
	{
		T = malloc(sizeof(struct TreeNode));
		if (T != NULL)
		{
			T->Element = RandomNum = RandInt(Lower, Upper);
			T->Left = MakeRandomTree(Lower, RandomNum - 1);
			T->Right = MakeRandomTree(RandomNum + 1, Upper);
		}
		else
			perror("Out of space!!!");
	}
	return T;
}
BinaryTree MakeRandomTree1(int N)
{
	return MakeRandomTree(1, N);
}
int main()
{
	int n;
	srand((unsigned)time(NULL));
	printf("请输入生成的随机二叉查找树节点个数：");
	scanf_s("%d", &n);
	BinaryTree T = NULL;
	T = MakeRandomTree1(n);
	printf("该二叉树的节点个数为：%d\n", CountNodes(T));
	printf("树叶节点个数为：%d\n", CountLeaves(T));
	printf("满节点个数为：%d\n", CountFull(T));
	return 0;
}
