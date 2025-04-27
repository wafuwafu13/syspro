#include <stdio.h>
struct linear{
   int data;
   struct linear *next;
};

int main(){
   int i;
   struct linear arr[5], *ptr, *prev = NULL;
   ptr = arr;
   // 逆順にリンクリストを構築
   for(i = 0; i < 5; i++){
      scanf("%d", &ptr->data);
      ptr->next = prev;
      prev = ptr;
      ptr++;
   }

   // 逆順に出力
   ptr = prev;  // 最後に追加した要素（最初の入力）から開始
   while(ptr != NULL){
      fprintf(stderr, "%d\n", ptr->data);
      ptr = ptr->next;
   }
 
   return 0;
}


// 初期化:

// arr[5]: 5つのlinear構造体の配列
// ptr = arr: ptrは配列の先頭を指す
// prev = NULL: 前の要素へのポインタ、初期値はNULL
// リンクリストの構築 (for ループ):

// i = 0:
// 入力: 6
// arr[0].data = 6
// arr[0].next = NULL
// prev = &arr[0]
// ptr は arr[1] を指す

// i = 1:
// 入力: 7
// arr[1].data = 7
// arr[1].next = &arr[0]
// prev = &arr[1]
// ptr は arr[2] を指す

// i = 2:
// 入力: 8
// arr[2].data = 8
// arr[2].next = &arr[1]
// prev = &arr[2]
// ptr は arr[3] を指す

// i = 3:
// 入力: 9
// arr[3].data = 9
// arr[3].next = &arr[2]
// prev = &arr[3]
// ptr は arr[4] を指す

// i = 4:
// 入力: 10
// arr[4].data = 10
// arr[4].next = &arr[3]
// prev = &arr[4]
// ptr は arr[5] を指す (配列の範囲外)
// リンクリストの構造 (構築後): 10 -> 9 -> 8 -> 7 -> 6 -> NULL

// 出力準備:
// ptr = prev (つまり &arr[4])
// 出力 (while ループ):
// ループ1: 出力 10, ptr は arr[3] を指す
// ループ2: 出力 9, ptr は arr[2] を指す
// ループ3: 出力 8, ptr は arr[1] を指す
// ループ4: 出力 7, ptr は arr[0] を指す
// ループ5: 出力 6, ptr は NULL になる
// ループ終了
// プログラム終了