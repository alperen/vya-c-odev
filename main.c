/* ALPEREN TÜRKÖZ - 171601037 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX_NONCE 15
#define HOT_PATATO_USER_COUNT 5

void siralamaEkrani();
void sicakPatatesEkrani();

const char* Names[] = {
	"Gelicem Nerdesin",
	"Ben Tek Siz Hepiniz",
	"Nick Mason",
	"Rick Wright",
	"Roger Waters",
	"David Gilmour",
	"Syd Barret",
};

/* utilities */

void clear(){
	system("@cls||clear");
}

int randRange(int min,int max){
	srand(time(NULL));
	return rand() % (max + 1 - min) + min;
}

/**/

void mainMenu(){
	short int selection;
	do
	{
		printf("|--- SECIMINIZI YAPIN ---|\n");
		printf("| Siralama      icin: [1]|\n");
		printf("| Sicak Patates icin: [2]|\n");
		printf("| Cikis yapmak  icin: [3]|\n\n");
		printf("Secim bekleniyor:");
		scanf("%d", &selection);

		clear();

		if (selection == 1)
		{
			siralamaEkrani();
			break;
		}
		else if (selection == 2)
		{
			sicakPatatesEkrani();
			break;
		}

	} while (selection != 3);
}

void askMainMenu(){
	int choose;
	printf("\n\n>> Ana menuye donmek istiyor musunuz? (1/0): ");
	scanf("%d",&choose);

	if(choose){
		clear();
		mainMenu();
	}
}

char progress(int x){
	char *a = "\\/_|";

	return (char) a[x];
}

/* Siralama Ekrani icin: */

struct Stack
{
	int count;
	struct Node *top;
};

struct Queue
{
	int count;
	struct Node *front;
	struct Node *rear;
};

struct Node
{
	int value;
	struct Node *next;
};

typedef struct Node *NODE_POINTER;
typedef struct Stack *STACK_POINTER;
typedef struct Queue *QUEUE_POINTER;

NODE_POINTER createNode()
{
	return (NODE_POINTER)malloc(sizeof(struct Node));
}

QUEUE_POINTER createQueue(){
	QUEUE_POINTER newQueue = (QUEUE_POINTER)malloc(sizeof(struct Queue));
	newQueue->front = NULL;
	newQueue->rear  = NULL;
	newQueue->count = 0;

	return newQueue;
}

STACK_POINTER createStack(){
	STACK_POINTER newStack = (STACK_POINTER)malloc(sizeof(struct Stack));
	newStack->count = 0;

	return newStack;
}

void pushStack(STACK_POINTER stack, int value){
	NODE_POINTER newNode = createNode();
	newNode->value = value;
	newNode->next = stack->top;
	stack->top = newNode;
	stack->count++;
}

void pushQueue(QUEUE_POINTER queue,int value){
	NODE_POINTER newNode = createNode();

	if(queue->front == NULL){
		queue->front = newNode;
	}else{
		queue->rear->next = newNode;
	}
	newNode->value = value;
	newNode->next = queue->front;
	queue->rear = newNode;
	queue->count++;
}

void printStack(STACK_POINTER stack){

	NODE_POINTER top = stack->top;

	for (int i = 0; i < stack->count; i++)
	{
		printf(" %d ", top->value);
		top = top->next;
	}
}

int popStack(STACK_POINTER stack){
	NODE_POINTER top = stack->top;
	int value = top->value;
	if (stack->count == 0)
	{
		return -1;
	}
	stack->count--;
	stack->top = top->next;
	return value;
}

int popQueue(QUEUE_POINTER  queue){
	if(queue->front == NULL){
		exit(1);
	}

	int value;

	if(queue->front == queue->rear){
		value = queue->front->value;
		queue->front = queue->rear = NULL;
	}else{
		NODE_POINTER temp = queue->front;
		value = temp->value;
		queue->front = temp->next;
		queue->rear->next = queue->front;
	}

	queue->count--;

	return value;
}

void showStack(STACK_POINTER stack, char *name){
	printf("|[%s]: ", name);

	if (stack->count == 0)
	{
		printf("[STACK BOS]");
	}

	NODE_POINTER top = stack->top;
	for (int i = 0; i < stack->count; i++)
	{
		printf(" %d ", top->value);
		top = top->next;
	}
	printf("|\n");
}

void showQueue(QUEUE_POINTER queue){
	printf("| KUYRUK:");

	NODE_POINTER temp = queue->front;
	while(temp->next != queue->front){
		printf(" %s ",Names[temp->value]);
		temp = temp->next;
	} 
	printf(" %s ", Names[temp->value]);
	printf(" |");
}

STACK_POINTER AStack;
STACK_POINTER BStack;

void siralamaEkrani(){

	AStack = createStack();
	BStack = createStack();

	int nonce = 0;

	while (nonce != MAX_NONCE)
	{

		showStack(AStack, "A");
		showStack(BStack, "B");

		int number;
		printf("[%d] Bir sayi girin:", (nonce + 1));
		scanf("%d", &number);

		int lastInsert = AStack->top->value;
		while(number > lastInsert && AStack->count != 0){
			pushStack(BStack,lastInsert);
			popStack(AStack);
			lastInsert = AStack->top->value;
		}

		pushStack(AStack,number);

		while(BStack->count != 0){
			pushStack(AStack,popStack(BStack));
		}

		//	push(AStack, number);

		nonce++;

		if (nonce != MAX_NONCE)
		{
			clear();
		}
	}

	clear();

	showStack(AStack, "A");
	showStack(BStack, "B");

	printf("Siralamayi buyukten kucuge olarak degistirmek istiyor musunuz? (1/0):");
	int secim;
	scanf("%d", &secim);

	if (secim == 1)
	{
		showStack(AStack, "KUCUKTEN BUYUGE");

		int value = popStack(AStack);
		while (value != -1)
		{
			pushStack(BStack, value);
			value = popStack(AStack);
		}
		
		showStack(BStack, "BUYUKTEN KUCUGE");
	}

	askMainMenu();
}

/* Program */
QUEUE_POINTER Users;

void sicakPatatesEkrani()
{
	Users = createQueue();

	for(int i = 0; i < 2; i++){
		pushQueue(Users,i);
	}
	showQueue(Users);
	
	//int loop = 1;

	int gameDuration = randRange(10,25);
	int seconds = 1;
	int keepDuration = randRange(1,3);	
 
	while(1){
		clear();
		showQueue(Users);
		printf("\n| PATATES : %s |", Names[Users->front->value]);
		printf(" SIRADAKI: %s  |\n", Names[Users->front->next->value]);

		printf("|[%c] MUZIK SURESI: %d | ELDE TUTMA SURESI: %d | GECEN SURE: %d |",progress(time(NULL) % 4),gameDuration,keepDuration, (seconds+1));
		
		if(seconds % keepDuration == 0){
			keepDuration = randRange(1,3);
			int popped = popQueue(Users);
			pushQueue(Users,popped);
		}

		Sleep(1000);
		seconds += 1;
		if(gameDuration == seconds){

			printf("| YANAN KISI: %s |\n",Names[Users->front->value]);
			popQueue(Users);

			if(Users->count == 1){
				break;
			}

			Sleep(2000);
			seconds = 0;
			int gameDuration = randRange(10,25);
		}
	}
	
	askMainMenu();
}

int main(int argc, char *argv[])
{
	mainMenu();

	return 0;
}
