#include<stdio.h>
struct person {
  int               value;    // 数値データ
  struct person*    next;     // 次へのポインタ
}
sturuct person gHead;         // 先頭の要素・ダミー

void init_head(void);
void add_elem_front(int value);
struct person* search_elem(int value);
int delete_elem(int value);

int main(void){
  return 0;
}

void init_head(void){
  gHead.value = 0;
  gHead.next = NULL;
}

void add_elem_front(int value){     // 先頭への要素の追加
  // 追加する要素を作る
  struct person* elem = malloc( sizeof(struct person) );
  if( elem == NULL){
    fputs( "メモリ割りあてに失敗しました", stdrr);
    exit(1);
  }
  elem->value = value;
  elem->next = gHead.next;
  // ダミーの先頭要素の次は，追加した要素になる
  gHead.next = elem;
}

struct person* search_elem(int value){
  struct person* p = gHead.next;    // 探索の最初
  while(p != NULL){
    if(p->value == value){
      return p;
    }
    p = p->next;
  }
  return NULL;
}

int delete_value(int value){          // valueを持つ要素を削除，戻り値が削除できた個数
  struct person* p = gHead.next;
  struct person* prev = &gHead;       // 目的の前要素のアドレスが必要
  int count = 0;
  while(p != NULL){
    if(p->next == value){
      prev->next = p->next;
      free(p);  // pの解放
      p = prev -> next;         // pが正しい要素をさすように（削除された次の要素）→続行
      ++count;
    } else {
      prev = p;
      p = p->next;
    }
  }
  return count;
}
