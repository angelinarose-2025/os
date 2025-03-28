#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
//#include <qsort.h>
#define MT 256
#define MC 3
typedef struct {
 int p;
 char t[MT];
} Msg;
int compare_priority(const void *a, const void *b) {
 Msg *msgA = (Msg *)a;
 Msg *msgB = (Msg *)b;
 return (msgA->p - msgB->p);
}
int main() {
 int qid, count = 0;
 Msg msgs[MC];
 key_t key = ftok("sender.c", 65);
 if (key == -1) {
 perror("ftok failed");
 exit(1);
 }
 qid = msgget(key, 0666 | IPC_CREAT);
 printf("\nReceived Messages in Increasing Order of Priority:\n");
 for (int i = 0; i < MC; i++) {
 Msg m;
 if (msgrcv(qid, &m, sizeof(m.t), 0, IPC_NOWAIT) == -1) {
 if (errno == ENOMSG) {
 printf("No more messages in the queue.\n");
 break;
 } else {
 perror("msgrcv failed");
 break;
 }
 }
 msgs[count++] = m;
 }

 qsort(msgs, count, sizeof(Msg), compare_priority);
 for (int i = 0; i < count; i++) {
 printf("Priority %d: %s\n", msgs[i].p, msgs[i].t);
 }
 if (msgctl(qid, IPC_RMID, NULL) == -1) {
 perror("msgctl failed");
 }
 return 0;
}