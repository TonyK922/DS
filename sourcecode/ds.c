#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20  //顺序表的最大长度
typedef int KeyType; //定义关键字类型为整型
typedef char InfoType; 


typedef struct {
	KeyType key;   //关键字项
	//InfoType otherinfo; //其他数据项
}RedType;   //记录类型

typedef struct{
	RedType r[MAXSIZE+1]; //r[0]闲置或用做哨兵单元
	int length;  //顺序表的实际长度,除去r[0]
}SqList;

void InsertSort(SqList *L)
{
	int i,j;

	for(i = 2; i<=L->length-1; ++i) //r[0]不用的所以length-1
	{
		if(L->r[i].key < L->r[i-1].key)  //＂<＂需将r[i]插人有序子表
		{
			L->r[0] = L->r[i];  //设置哨兵
			for(j = i-1; L->r[0].key < L->r[j].key; --j) 
			{
				L->r[j+1] = L->r[j]; //大的依次后移
			}
			L->r[j+1] = L->r[0]; //上面循环最后一次执行了--j 这里j+1是对的位置
		}
	}
}
void BInsertSort(SqList *L)
{
	int i = 0, j = 0;

	for(i = 2; i<=L->length; ++i) //依次插入2到n个元素
	{
		L->r[0] = L->r[i]; //需要被插入的元素存到哨兵
		int low = 1, high = i-1; //二分法的两个位置指针.
		
		while(low <= high)   //low > high的时候查找就结束了.
		{
			int mid = (low + high) >> 1; //除以2
			if (L->r[0].key < L->r[mid].key)
				high = mid - 1;
			else
				low = mid + 1;
		} //找到了high+1为插入位置
		for(j = i-1;j>=high + 1; --j) //high+1往后的依次移动
			L->r[j+1] = L->r[j];
		L->r[high+1] = L->r[0]; //插入
	}
}
int dlta[5] = {4,3,1};
void CalDlta(SqList *L)
{
	
	int i ;
	dlta[0] = L->length>>1;
	for(i = 1; dlta[i-1] >= 1; i++)
	{
		int r;
		r = dlta[i-1] >> 1;
		if( r < 1 )
			break;
		dlta[i] = r;
		printf(" %d %d ", i, dlta[i]);
	}
	//for(int a = 0; a < i; a++)
	//printf("%d ",dlta[a]);
	
}
void ShellInsert(SqList *L, int dk)
{
	int i,j;
	//对顺序表L做`一趟`增量是dk的希尔插入排序 dk是步长因子
	for(dk = L->length >> 1; dk >= 1; dk >>= 1)
	{
		for(i = dk+1; i<=L->length; ++i)//0位置做哨兵
		{
			if(L->r[i].key<L->r[i-dk].key) //需将L->r[i]插入有序增扯子表
			{
				L->r[0] = L->r[i]; //暂存在哨兵
				for(j=i-dk; j>0 && (L->r[0].key < L->r[j].key); j-=dk) 
					L->r[j+dk] = L->r[j]; //分组的直接插入排序
				L->r[j+dk] = L->r[0]; /*循环最后一步执行了j=-dk, 所以j+dk才是正确位置    
									位置移完把r[i]插到正确位置*/
			}
		}
	}
}
void ShellInsert2(SqList *L)
{
	int i,j,dk;
	//对顺序表L做`一趟`增量是dk的希尔插入排序 dk是步长因子
	for(dk = L->length >> 1; dk >= 1; dk >>= 1)
	{
		printf(" %d ", dk);
		for(i = dk+1; i<=L->length; ++i)//0位置做哨兵
		{
			if(L->r[i].key<L->r[i-dk].key) //需将L->r[i]插入有序增扯子表
			{
				L->r[0] = L->r[i]; //暂存在哨兵
				for(j=i-dk; j>0 && (L->r[0].key < L->r[j].key); j-=dk) 
					L->r[j+dk] = L->r[j]; //分组的直接插入排序
				L->r[j+dk] = L->r[0]; /*循环最后一步执行了j=-dk, 所以j+dk才是正确位置    
									位置移完把r[i]插到正确位置*/
			}
		}
	}
}
//dk值依次存于dlta[t]中
void ShellSort(SqList *L, int dlta[], int t)
{
	CalDlta(L);
	for(int k = 0; k < t; ++k)
		ShellInsert(L, dlta[k]); //一趟增址为dt[t]的希尔插入排序
}
void BubbleSort(SqList *L)
{
	//对顺序表L做冒泡排序
	int m = L->length - 1, flag = 1; //flag用来标记某一趟排序是否发生交换
	while ((m > 0) && (flag==1))
	{
		flag = 0; //flag置为0,如果本趟排序没有发生交换，则不会执行下一趟排序
		for (int j=1; j<=m; j ++)
		{
			if(L->r[j].key > L->r[j+1].key)
			{
				flag = 1; //flag置为1, 表示本趟排序发生了交换
				RedType x = L->r[j];
				L->r[j] = L->r[j+1];
				L->r[j+1] = x;
			}
		}
		m--; 
	} //while
}
//写法二:
void bubble_Sort(SqList *L)
{
	int flag = 1, n = L->length;

	for(int i = 1; i <= n-1 && 1 == flag;i++)
	{
		//if(!flag) break; //上一趟已经没有进行交换了 结束		
		flag = 0; //flag置为0,如果本趟排序没有发生交换，则不会执行下一趟排序
		for(int j = 1;j <= n-i; j++)//for(;j <= n - i; j++)
		{
			if(L->r[j].key > L->r[j+1].key)
			{
				flag = 1; //flag置为1, 表示本趟排序发生了交换
				L->r[0] = L->r[j];//r[0]没有被使用, 是哨兵
				L->r[j] = L->r[j+1];
				L->r[j+1] = L->r[0];//x;
			}
		}
	}
}
void QSort(SqList *L, int low, int high);
int Partition(SqList *L, int low, int high);
void QuickSort(SqList *L);

void QuickSort(SqList *L)
{ //对顺序表L做快速排序
	QSort(L, 1, L->length); //调用QSort
}

void QSort(SqList *L, int low, int high)
{ //调用前置初值： low= 1; high= L->length;
	//对顺序表L中的子序列L->r[low .. high]做快速排序
	if(low < high)  //长度大于1
	{
		//将L.r[low.. high] 一分为二，pivotloc是枢轴位置
		int pivotloc = Partition(L, low, high); 
		QSort(L, low, pivotloc - 1);  //对左子表递归排序
		QSort(L, pivotloc+1, high);  //对右子表递归排序
	}
}

int Partition(SqList *L, int low, int high)
{ ///对顺序表L中的子表r[low .. high]进行一趟排序，返回枢轴位置
	L->r[0] = L->r[low];  //用子表的第一个记录做枢轴记录
	KeyType pivotkey = L->r[low].key; //枢轴记录关键字保存在pivotkey中
	while(low < high) //从表的两端交替地向中间扫描
	{
		while(low < high && L->r[high].key >= pivotkey) 
			high--;
		//low 的值已经被移到r[0]了,low的值可以被覆盖	
		L->r[low] = L->r[high];  //将比枢轴记录小的记录移到低端
		while(low < high && L->r[low].key <= pivotkey)
			low++;

		L->r[high] = L->r[low]; //将比枢轴记录大的记录移到高端
	} //while
	L->r[low] = L->r[0];  //枢轴记录到位
	return low;  //／返回枢轴位置	
}
void SelectSort(SqList *L)
{ //对顺序表L做简单选择排序
	for(int i = 1; i < L->length; i++)
	{
		int minred = i;
		for(int j = i+1; j<=L->length; j++) 
			if(L->r[j].key < L->r[minred].key) 
				minred = j;  //minred指向此趟排序中关键字最小的记录
				
	    if(minred != i) //意味着i就是最小的那个
		{
			L->r[0] = L->r[i]; //r[0]是哨兵位
			L->r[i] = L->r[minred];
			L->r[minred] = L->r[0];
		}
	}
	
}

void HeapAdjustBig(SqList *L,int s,int m)
{ //假设r[s+1..m]已经是堆， 将r[s.. m]调整为以r[s]为根的大根堆
	RedType rc = L->r[s];
	for(int j= s<<1; j<=m; j<<=1) //沿key较大的孩子结点向下筛选
	{
		if(j < m && L->r[j].key < L->r[j+1].key) //j为key较大的记录的下标
			++j;  //开始往后面去调整, 保证改后子树也是堆
		if(rc.key >= L->r[j].key) break; //rc应在位置s上 后面就不执行.
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = rc;
}
//小根堆
void HeapAdjustLittle(SqList *L,int s,int m)
{ //假设r[s+1..m]已经是堆， 将r[s.. m]调整为以r[s]为根的小根堆
	RedType rc = L->r[s];
	for(int j = s<<1; j<=m; j<<=1) //沿key较小的孩子结点向下筛选
	{
		if(j < m && L->r[j].key > L->r[j+1].key) //j为key较大的记录的下标
			++j;   //j+1更小所以让j++ 同时继续往子树去调整
		if(rc.key <= L->r[j].key) break; //r[s]不需要动
		L->r[s] = L->r[j]; //较小的孩子赋值给根r[s]
		s = j; // s 存r[j]
	}
	L->r[s] = rc; //完成r[s]与r[j]交换
}
void CreatHeap(SqList *L)
{
	int n = L->length; //可以是length-1 如果r[0]是哨兵.
	for(int i = n>>1; i >= 1; i--) //从n/2开始
		HeapAdjustBig(L, i, n);
}

#define swap(x, y) do {\
	typeof(x) c = (y);\
	(y) = (x);\
	(x) = c;}while(0)

void HeapSort(SqList *L)
{ //对顺序表L进行堆排序
	CreatHeap(L); //无序序列建成大根堆
	for(int i=L->length; i > 1; --i) //r[0]是哨兵
	{
		swap(L->r[1], L->r[i]); //将堆顶记录和当前未经排序子序列r[1..i]中最后一个记录互换
		HeapAdjustBig(L, 1, i-1); //将r[1..i-1]重新调整为大根堆
 	}
}
//插入, 插到最后
void HeapInsert(SqList *L, RedType e)
{
	if(L && L->length < MAXSIZE)
	{
		L->r[++L->length] = e;
		//printf("%d %d\n", L->length, L->r[L->length].key);
		HeapSort(L);
	}
}
void HeapDelete(SqList *L, int pos)
{
	if(L && pos <= L->length && pos >= 1)
	{
		L->r[pos] = L->r[L->length--];
		//printf("%d pos:%d %d\n", L->length, pos,L->r[pos].key);
		HeapSort(L);
	}
}
//将有序表R[low..mid]和R[mid+1..high]归并为有序表T[low..high]
void Merge(RedType *R, RedType *T, int low, int mid, int high)
{
	int i = low, j = mid+1, k =low;
	while(i<=mid && j<=high) //将R中记录由小到大地并入T中
	{
		if(R[i].key <= R[j].key)  T[k++] = R[i++];
		else T[k++] = R[j++];
	}
	while(i<=mid) T[k++] = R[i++]; 
	while(j<=high) T[k++] = R[j++];
}
void MSort(RedType *R,RedType *T,int low,int high)
{//R[low .. high]归并排序后放人T[low.. high]中
	RedType *S = malloc((high+1)*sizeof(RedType));
	if(!S)  return ;

	if(low == high) T[low] = R[low];
	else
	{
		int mid = (low+high) >> 1; //将当前序列一分为二， 求出分裂点mid
		//对子序列R[low..mid]递归归并排序,结果放入S[low..mid]
		MSort(R,S,low,mid); 
		//对子序列R[mid+1..high]递归归并排序,结果放人S[mid+ 1..high]
		MSort(R,S,mid+1,high); 
		//将S[low..mid]和S[mid+1..high]归并到T[low..high]
		Merge(S,T,low,mid,high);
	}
	free(S);
}

void MergeSort(SqList *L)
{//对顺序表L做归并排序
	MSort(L->r, L->r, 1, L->length);
}
int main()
{

    SqList SL = { 
        .r={ [1].key=49,38,65,97,76,13,27,49, 50, 1, 100 },
        .length = 11
        };

    //CreatHeap(&SL);
	//InsertSort(&SL);
	//BInsertSort(&SL);
	//ShellInsert2(&SL);
	//CalDlta(&SL);
	//bubble_Sort(&SL);
	//QuickSort(&SL);
	//SelectSort(&SL);
	//HeapSort(&SL);
	MergeSort(&SL);
    for(int i = 1; i <= SL.length; i++)
        printf("%d ",SL.r[i].key);
    putchar('\n');
	//HeapInsert(&SL, (RedType){.key = 30});
	// for(int i = 1; i <= SL.length; i++)
    //    printf("%d ",SL.r[i].key);
    //putchar('\n');
	//HeapDelete(&SL, 7);
	//HeapDelete(&SL, 8);
	//for(int i = 1; i <= SL.length; i++)
     //   printf("%d ",SL.r[i].key);
    //putchar('\n');
}