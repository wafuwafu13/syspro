#include <stdio.h>
struct linear{
   int data;
   struct linear *next;
};

int main(){
   int i, n;
   struct linear arr[5],*ptr,*curr;
   ptr=arr;
   for(i=0;i<5;i++){
      scanf("%d", &ptr->data);
      curr=ptr;
      curr->next=++ptr;
   }
   curr->next=NULL;

   ptr=arr;
   while(ptr!=NULL){
      fprintf(stderr, "%d\n",ptr->data);
      ptr = ptr->next;
   }

   printf("要素番号 :");
   scanf("%d", &n);
   printf("%d\n", arr[n].data);
 
   return 0;
}

// 初期化:

// arr[5]: 5つのlinear構造体の配列
// ptr = arr: ptrは配列の先頭を指す
// リンクリストの構築 (for ループ):

// i = 0:
// 入力: 6
// arr[0].data = 6
// curr = &arr[0]
// ptr は arr[1] を指す
// arr[0].next = &arr[1]

// i = 1:
// 入力: 7
// arr[1].data = 7
// curr = &arr[1]
// ptr は arr[2] を指す
// arr[1].next = &arr[2]

// i = 2:
// 入力: 8
// arr[2].data = 8
// curr = &arr[2]
// ptr は arr[3] を指す
// arr[2].next = &arr[3]

// i = 3:
// 入力: 9
// arr[3].data = 9
// curr = &arr[3]
// ptr は arr[4] を指す
// arr[3].next = &arr[4]

// i = 4:
// 入力: 10
// arr[4].data = 10
// curr = &arr[4]
// ptr は arr[5] を指す (配列の範囲外)
// arr[4].next = &arr[5] (配列の範囲外を指す)

// ループ後の処理:
// curr->next = NULL: arr[4].next が NULL に設定される
// リンクリストの構造 (構築後): 6 -> 7 -> 8 -> 9 -> 10 -> NULL

// 出力 (while ループ):
// ptr = arr (配列の先頭に戻る)
// ループ1: 出力 6
// ループ2: 出力 7
// ループ3: 出力 8
// ループ4: 出力 9
// ループ5: 出力 10
// ループ終了 (ptr が NULL になる)
// 要素番号の入力と出力:
// "要素番号 :" と表示
// ユーザーが要素番号を入力（例えば 2）
// arr[2].data の値（この場合 8）を出力
// プログラム終了