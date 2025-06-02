/*File body untuk ADT Queue*/
/*Dibuat tanggal 28-3-2013*/

#include "Queue2.h"

/*Membuat sebuah queue baru dengan Front dan Rear NULL*/
void CreateQueue (Queue *Q)
{
	Q->front = NULL;
    Q->rear = NULL;
}


/*Memeriksa apakah queue kosong */
boolean is_Empty (Queue Q)
{
	return (Q.front == NULL && Q.rear == NULL);
}

/*Memeriksa apakah queue penuh */
boolean is_Full (Queue Q)
{
	int count = 0;
    address p = Q.front;

    while(p != NULL) {
        count++;
        if(count == NBElement) {
            return true;
        }
        p = p->next;
    }
    return false;
}

/*Melekukan insertion pada queue*/
void EnQueue (Queue *Q, infotype X)
{
	address add;
    List l;
    l.First = Q->rear;
    if(is_Full(*Q)) return;

    add = Alokasi(X);
    InsertLast(&l, add);
    Q->rear = add;
    if(Q->front == NULL) {
        Q->front = add;
    }
}

/*Melakukan deletion pada queue*/
void deQueue (Queue *Q, infotype *X)
{
	List l;
    l.First = Q->front;

    if(is_Empty(*Q)) return;
    
    DelVFirst(&l, X);
    Q->front = l.First;
    if(Q->front == NULL) {
        Q->rear = NULL;
    }
}


void PrintQueue(Queue q) {
    address cursor;

    cursor = q.front;
    if(is_Empty(q)) {
        printf("Antrian Kosong...\n");
        return;
    }
    printf("Antrian sekarang: ");
    while (cursor != q.rear->next)
    {
        printf("%d ", cursor->info);
        cursor = cursor->next;
    }
    

    printf("\n");
}