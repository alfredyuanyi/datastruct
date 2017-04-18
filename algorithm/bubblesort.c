#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M (100)

//常规冒泡排序
void BubbleSort(int *a, int n){
    int temp, i, j;
    for(i = 0; i < n; i++){
        for(j = 1; j < n - i; j++){
            if(a[j] < a[j - 1]){
                temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
            }
        }
    }
}

/*进阶版冒泡排序,设置了flag,当上一轮没有发生交换时,排序直接结束,同时设置k,记录每轮扫描最后发生交换的位置,下一轮扫描只要扫描到k位置即可.
对于改进后的冒泡排序,
时间复杂度: 最好情况,数组本身有序,只需要进行 n -1 次比较,时间复杂度为O(n); 最坏情况,数组本身逆序, 需要进行 n*(n - 1)/2 次比较, 时间复杂度为O(n**2);
            平均情况,时间复杂度为O(n**2);
空间复杂度: 最好情况=最坏情况=平均情况=O(1)
*/
void BubbleSortAdvance(int *a, int n){
    int temp, i;
    int flag = 1;
    int k = n;
    while(flag > 0){
        flag = 0;
        for(i = 1; i <= k; i++){
            if(a[i] < a[i - 1]){
                temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
                flag = i;
            }
        }
        k = flag;
    }
}

int main(){
    int i = 0;
    int a[M];
    srand((unsigned)time(0));
    for(; i < M; i++){
        a[i] = rand() % (100-0);
    }
    BubbleSortAdvance(a, M);
    for(i = 0; i < M; i++)
        printf("%d | ", a[i]);
    printf("\n");
    return 0;
}