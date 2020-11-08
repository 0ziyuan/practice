#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node* lchild;
    struct Node* rchild;
}BiTNode, * PBiTNode;
int s = 0;
int inordindex[100000000];
void PreOrder(PBiTNode bt, int* out1);
void CreatepostBiTree(int preord[], int inord[], int i, int j, int k, int h, PBiTNode &t);
void solve(int n, int* preOrder, int* inOrder, int* outOrder)
{
    PBiTNode root=NULL;
    if (n <= 0 || preOrder==NULL|| inOrder==NULL|| outOrder==NULL)
    {
        return;
    }
    else
    {
        for (int i = 0; i < n; i++)
            inordindex[inOrder[i]] = i;
        CreatepostBiTree(preOrder, inOrder, 0, n - 1, 0, n - 1, root);
        PreOrder(root, outOrder);
    }
}
void CreatepostBiTree(int preord[], int inord[], int i, int j, int k, int h, PBiTNode &t) 
{
    /* ���������д�i��j���������д�k��h������һ�ö���������t��*/
    int m;
    t = (BiTNode*)malloc(sizeof(BiTNode));
    if (t == NULL) return ;
        t->data = preord[i];  /*�������ĸ�*/
        m = inordindex[preord[i]];  /*�����������ж�λ���ĸ�*/
        /*�ݹ���ý���������*/
        if (m == k) t->lchild = NULL;    /*��������*/
        else CreatepostBiTree(preord, inord, i + 1, i + m - k, k, m - 1, (t->lchild));
        /*�ݹ���ý���������*/
        if (m == h) t->rchild = NULL;   /*��������*/
        else CreatepostBiTree(preord, inord, i + m - k + 1, j, m + 1, h, (t->rchild));
}
void PreOrder(PBiTNode bt, int* out1)
{
    if (bt != NULL) { /* ���btΪ�գ�����*/
        out1[s++] = bt->data;  /*���ʸ����*/
        printf("%d ", bt->data);
        PreOrder(bt->rchild, out1);   /*����������������ݹ���ã�*/
        PreOrder(bt->lchild, out1);   /*����������������ݹ���ã�*/
    }
}
int main()
{
    int N;
    scanf_s("%d", &N);
    int* pre = (int*)malloc(N * sizeof(int));
    if (pre == NULL) return 0;
    int* in = (int*)malloc(N * sizeof(int));
    if (in == NULL) return 0;
    int* out = (int*)malloc(N * sizeof(int));
    if (out == NULL) return 0;
    for (int i = 0; i < N; i++)
    {
        scanf_s("%d", &pre[i]);
    }
    for (int j = 0; j < N; j++)
    {
        scanf_s("%d", &in[j]);
    }
    solve(N, pre, in, out);
    printf("\n");
    return 0;
}