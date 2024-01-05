#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define MAX_Queue_SIZE 100   //最大队长


typedef struct Patient{    //定义病人结构体
    char name[15];
    int num;
}patient;

typedef struct QueueNode{  
    struct QueueNode* front;
    struct QueueNode* rear;
    struct QueueNode* next;
    int size;
    patient* data;
}QueueNode;

// 初始化队列
QueueNode* initQueue(){
        QueueNode* q = (QueueNode*)malloc(sizeof(QueueNode));
        q -> front = q;
        q -> rear = q;
       q -> data = NULL ;
        q -> size = 0;
        q -> next = NULL;
        return q;   //返回初始化的队列
}

// 判断队列是否为空
int isempty(QueueNode* q){
    if(q -> rear == q || q -> data == 0){
        return 1;   //队空
    }
    else{
        return 0;
    }
}

//进行病人的入队操作
void enQueue(QueueNode* q,patient data){
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode)); 
    node->data = (patient*)malloc(sizeof(patient));
    *(node->data) = data;
    node -> next = NULL;
    if(isempty(q)){    
        q -> front = q -> rear = node;
    }else{
        q -> rear -> next = node;
        q -> rear = node;
    }
    q -> size ++;
    q -> data ++; 
}

//就诊操作，即出队操作
int deQueue(QueueNode* q){
    if(!isempty(q)){
        patient temp ;
        temp = *(q -> front -> data);  //设置一个临时变量temp储存出队信息
        QueueNode* temp1 = q -> front;
        if(q -> rear == q -> front){
            q -> rear = q -> front = NULL; 
        }else{
            q -> front = q -> front -> next;
        }
        free(temp1);
        q -> data --;
        q -> size --;
        return temp.num;   //返回出队病人的病历号
    }
    return -1;
}

//打印队列，即输出排队列表
void printQueue(QueueNode* q){
    QueueNode* node = q -> front;
    int index = 1;
    while(node){
        printf("排队序号 ：%d  病人编号：%d \n",index++,(node -> data)->num);
        node = node -> next;   
    }
    if(isempty(q)){
        printf("没有病人了");
    }
}

int main(){
    patient p[10];
    int index = 0 ;
    int option;
    // strcpy(p[0].name,"xiaoming");
    // p[0].num = 01;
    // strcpy(p[1].name,"xiaozhang");
    // p[1].num = 02;
    // strcpy(p[2].name,"xiaozang");
    // p[2].num = 03;
    QueueNode* q = initQueue();
    // enQueue(q,p[0]);
    // printf("病历号为：%d 的病人就诊完成\n",deQueue(q));
    // printf("%d",deQueue(q));
    printf("\n");
    printf("======== 排队系统菜单 ========");
    while (1) {
        printf("\n1. 排队");
        printf("\n2. 就诊");
        printf("\n3. 查看排队");
        printf("\n4. 不再排队，余下依次就诊");
        printf("\n5. 下班");
        printf("\n请选择操作（1-5）: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
            // //排队功能
                printf("请输入排队人数");
                scanf("%d",&index);
                if(index <= 10){
                for(int i = 0 ; i < index ; i++){
                  patient temp;     //设置临时变量用于储存排队的患者
                  printf("请输入病人的病历号：");
                  scanf("%d",&temp.num);
                 enQueue(q,temp);
                }
                 printf("排队成功");
                break;
            }

            case 2:
            //就诊功能
                printf("请 %d 号病人就诊",deQueue(q));
                break;

            case 3:
            //查看排队功能
                printQueue(q);
                break;

            case 4:
            //不再排队，余下依次就诊
                while(!isempty(q)){
                    printf("请 %d 号患者就诊！\n",deQueue(q));
                }
                printf("今日看诊结束，不再接受排队！系统将退出\n");
                return 0;

            case 5:
                printf("系统已退出。");
                return 0;

        }
  }
   return 0;
}