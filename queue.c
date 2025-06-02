/*File body untuk ADT Queue*/
/*Dibuat tanggal 28-3-2013*/

#include "queue.h"

/*Membuat sebuah queue baru dengan Front dan Rear NULL*/
void CreateQueue(Queue *Q) 
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

    while(p != NULL) 
    {
        count++;
        if (count == NBElement) 
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

/*Melekukan insertion pada queue*/
void EnQueue(Queue *Q, infotype X) 
{
    if (is_Full(*Q)) return;

    address add = Alokasi(X);
    if (add != NULL) 
    {
        add->next = NULL;

        if (is_Empty(*Q)) 
        {
            Q->front = add;
            Q->rear = add;
        } else {
            Q->rear->next = add;
            Q->rear = add;
        }
    }
}

/*Melakukan deletion pada queue*/
void deQueue(Queue *Q, infotype *X) 
{
    if (is_Empty(*Q)) return;
    address del = Q->front;
    *X = del->info;
    Q->front = Q->front->next;
    if (Q->front == NULL) 
    {
        Q->rear = NULL;
    }
    free(del);
}


void PrintQueue(Queue q) {
    address cursor = q.front;

    if (is_Empty(q)) 
    {
        printf("Antrian kosong...\n");
        return;
    }

    printf("Antrian sekarang:\n");
    while (cursor != NULL) 
    {
        printf("- %s\n", cursor->info.nama);
        cursor = cursor->next;
    }
}