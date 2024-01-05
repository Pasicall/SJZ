#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char **HFCode;

typedef struct TreeNode {
    double weight;
    int parent;
    int lchild;
    int rchild;
    char data;
} TreeNode;

typedef struct HFTree {
    TreeNode* data;
    int length;
} HFTree;

//哈夫曼树的初始化
HFTree* initHFTree(double* weight,int length,char* data){
    HFTree* T = (HFTree*)malloc(sizeof(HFTree));
    T -> data = (TreeNode*)malloc(sizeof(TreeNode)*(2*length-1));
    T -> length =  length ;
    for(int i = 0 ; i < length ; i++){
            T -> data[i].weight = weight[i];
            T -> data[i].parent = 0;
            T -> data[i].lchild = -1;
            T -> data[i].rchild = -1;
            T -> data[i].data = data[i];
    }
    return T;//返回一颗初始化后的哈夫曼树
}

int * getMin(HFTree* T){  //用于获取最小权值和次小权值
    double min = 100.0;
    double lessmin = 100.0;
    int minIndex;
    int lessminIndex;  

    //最小权值的计算
    for(int i = 0 ; i < T -> length ; i ++){
        if(T -> data[i].parent==0){
            if(T -> data[i].weight < min){
                min = T -> data[i].weight;
                minIndex = i;
            }
        }
    }

    //次小权值的计算
    for(int i = 0; i < T -> length; i ++){
        if(T -> data[i].parent==0 && i != minIndex){
            if(T -> data[i].weight < lessmin){
                lessmin = T -> data[i].weight;
                lessminIndex = i;
            }
        }
    }
    int* res = (int*)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = lessminIndex;
    return res; //返回最小和次小权值对应的坐标所构成的一个数组
}

//创建哈夫曼树
void createHFtree(HFTree* T){
    int min;
    int lessmin;
    int* res;
    int length = T -> length * 2 - 1;
    for(int i = T -> length; i < length ; i ++){
        res = getMin(T);
        int min = res[0];
        int lessmin = res[1];
        T -> data[i].weight = T -> data[min].weight + T -> data[lessmin].weight;
        T -> data[i].lchild = min ;
        T -> data[i].rchild = lessmin;
        T -> data[i].parent = 0;
        T -> data[min].parent = i ;
        T -> data[lessmin].parent = i ;
        T -> length ++;
    }
}

void printHFtree(HFTree* T,int index){  //先序排列
    if(index != -1){
        printf("%lf ->",T -> data[index].weight);
        printHFtree(T,T -> data[index].lchild);
        printHFtree(T,T -> data[index].rchild);

    }
}

//构建哈夫曼树的编码
void createHFcode(HFTree* T,HFCode* HC,int length){
    //开辟空间
    *HC = (HFCode)malloc(sizeof(char*)*(length+1));
    char* code = (char*)malloc(sizeof(char)*length);
    code[length-1]='\0';
    //生成哈夫曼编码
    for(int i = 0; i < length; i++){
        int start = length - 1;
        int current = i;
        int p = T -> data[current].parent;
        while(p){
            if(T -> data[p].lchild == current){
                code[--start] = '0';
            }else{
                code[--start] = '1';
            }
            current = p;
            p = T -> data[current].parent;
        }
        (*HC)[i] = (char*)malloc(sizeof(char)*(length-start));
        strcpy((*HC)[i],&code[start]);
    }
    free(code);
}

//哈夫曼解码
void transcodeHFcode(HFTree* T,char* s){
    printf("需要解码的字符串为：%s\n",s);
    int i;
    char *temp = NULL;
    i =  2 * T -> length - 1;
    temp = s;
    printf("解码的结果为：");
    while(*temp != '\0'){
        if(*temp == '0') {i = T -> data[i].lchild;}
        if(*temp == '1') {i = T -> data[i].rchild;}
        if(T->data[i].lchild == -1 && T -> data[i].rchild == -1){
            printf("%c",T -> data[i].data);
            i = T -> length - 1;   //重新回顶部搜索
        }
        temp ++;
    }
    printf("\n");
}

// 对电报进行哈夫曼编码
void CreateNewHFCode(HFTree* T,HFCode* HC,char* ret){
    int i,j,k=0;
    char c[100];
    printf("请输入需要编码的字符串: ");
    fgets(c, sizeof(c), stdin);
    for( i = 0 ; i < strlen(c) ; i ++){
        for ( j = 0 ; j < T -> length ; j ++){
            if (c[i] == T -> data[j].data){
                strcat(ret,HC[j]);
            }
        }
    }
    printf("字符串编码成功");
    ret[strlen(ret)+1]='\0';
}

void printHFcode(char* ret){  //打印特定电报的编码
    printf("所输入电报的编码结果为： \n");
                    for(int i = 0 ; i < strlen(ret); i++){
                        printf("%c",ret[i]);
                    }
                    printf("\n");
}

//打印哈夫曼树
void PrintTree(HFTree* T,HFCode * HC){
    printf("哈夫曼树的先序遍历为：\n");
    printHFtree(T,T -> length - 1);
    printf("\n");
    printf("初始化哈夫曼树：\n");
    for(int i = 0 ; i < 27 ; i ++){
    printf("数据为：%c 编码为：%s\n",T -> data[i].data,HC[i]);
    }
}
int main(){
    printf("哈夫曼树正在初始化...\n");
    double weight[27] ={0.2,0.063,0.052,0.023,0.0175,0.008,0.001,
    0.105,0.059,0.047,0.0225,0.012,0.012,0.003,
    0.071,0.054,0.035,0.0221,0.011,0.002,
    0.0644,0.053,0.029,0.021,0.0105,0.001,0.001} ;
    char data[]={' ','A','S','C','P','V','Z',
    'E','N','H','U','Y','W','K',
    'T','I','D','F','G','X',
    'O','R','L','M','B','J','Q','\0'};
    HFTree* T = initHFTree(weight,27,data);
    createHFtree(T);
    printf("初始化成功！\n");
    printf("\n");
    HFCode HC;
    createHFcode(T,&HC,27);
    char ret[100];
    // CreateNewHFCode(T,HC,ret);
    // printf("\n");
    // for(int i = 0 ; i < strlen(ret); i++){
    //     printf("%c",ret[i]);
    // }
    // printf("\n");
    // transcodeHFcode(T,ret);
     //菜单选项
     
    int option;
    printf("=========== 请选择所需的操作 ===========\n");
     while(1){
        printf("-----------------------------\n");
        printf("1. 编码");
        printf("\n2. 译码");
        printf("\n3. 打印编码");
        printf("\n4. 打印哈夫曼树");
        printf("\n5. 退出系统\n");
        printf("\n");
        printf("请选择操作（1-5）: ");
        scanf("%d", &option);

        while (getchar() != '\n');

            if(option == 1){
                    CreateNewHFCode(T,HC,ret);
                    printf("\n");
            }
            if(option == 2){
                    //printf("所输入电报的译码结果为：\n");
                    transcodeHFcode(T,ret);
            }
            if(option == 3){
                    printHFcode(ret);
            }
            if(option == 4){
                    PrintTree(T,HC);
          }
            if(option == 5){
                return 0;
            }
     }
}
