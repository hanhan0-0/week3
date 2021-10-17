#include <stdio.h>
#include <stdlib.h>
typedef struct BalanceTree* avl;
struct BalanceTree
{
	avl left;//左孩子
	avl right;//右孩子
	int num;//值
	int height;//树的高度
};
int Max(avl T1, avl T2)
{
	if (T1 == NULL && T2 == NULL)
		return -1;
	else if (T1 == NULL)
		return T2->height;
	else if (T2 == NULL)
		return T1->height;
	else
	{
		if (T2->height > T1->height)
			return T2->height;
		else
			return T1->height;
	}
}
avl maketree(int num)//建立一个无左右孩子的树
{
	avl T = (avl)malloc(sizeof(struct BalanceTree));
	T->height = 0;
	T->left = NULL;
	T->right = NULL;
	T->num = num;
	return T;
}
avl SingleLeft(avl T)//左左
{
	avl P;
	P = T->left;
	T->left = P->right;
	P->right = T;
	T->height = Max(T->right, T->left) + 1;
	P->height = Max(P->right, P->left) + 1;
	return P;

}
avl SingleRight(avl T)//右右
{
	avl P;
	P = T->right;
	T->right = P->left;
	P->left = T;
	T->height = Max(T->right, T->left) + 1;
	P->height = Max(P->right, P->left) + 1;
	return P;
}
avl DoubleLeft(avl T)//左右
{
	T->left = SingleRight(T->left);
	return SingleLeft(T);
}
avl DoubleRight(avl T)//右左
{
	T->left = SingleLeft(T->left);
	return SingleRight(T);
}
avl insert(avl T, int num)//插入且使平衡
{
	int a;
	if (T == NULL)
	{
		T = maketree(num);
		return T;
	}
	else if (num < T->num)
	{
		T->left = insert(T->left, num);
		if (T->right == NULL)
			a = -1;
		else
			a = T->right->height;
		if (T->left->height - a == 2)
		{
			if (num > T->left->num)
				T = DoubleLeft(T);
			else
				T = SingleLeft(T);
		}

	}
	else if (num > T->num)
	{
		T->right = insert(T->right, num);
		if (T->left == NULL)
			a = -1;
		else
			a = T->right->height;
		if (T->right->height - a == 2)
		{
			if (num > T->right->num)
				T = SingleRight(T);
			else
				T = DoubleRight(T);
		}

	}

	T->height = Max(T->right, T->left) + 1;
	return T;
}

void printTree(int h, const avl T)
{

	if (T == NULL)
		return;

	int m = h - T->height;
	while (m != 0)
	{
		m = m - 1;
		printf(" ");
	}
	printf("%d\n", T->num);
	printTree(h, T->left);;
	printTree(h, T->right);


}
int main()
{
	int num;
	avl T;
	T = maketree(1);

	for (int i = 0; i < 10; i++)
	{

		T = insert(T, i * 2 + 1);
	}

	printTree(T->height, T);
	return 0;
}
