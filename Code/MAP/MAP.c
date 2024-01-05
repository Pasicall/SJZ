#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 32767  //标识顶点不通

typedef struct school{
    char name[30];
    int num;
    char intro[100];
}school;

typedef struct User {
    char username[30];
    char password[30];
    int userType;  // 1表示游客，2表示管理员
} User;

typedef struct Graph{
    school* vexs;
    int** arcs;
    int vexsnum;
    int arcsnum;
    User* user;
    int usernum;
}Graph;



Graph* initGraph(int vexsnum){   //图的初始化
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G -> vexs = (school*)malloc(sizeof(school)*vexsnum);
    G -> arcs = (int**)malloc(sizeof(int*)*vexsnum);
    for(int i = 0 ; i < vexsnum ; i ++){
        G -> arcs[i] = (int*)malloc(sizeof(int)*vexsnum);
    }
        G -> vexsnum = vexsnum ;
        G -> arcsnum = 0;
        G -> usernum = 0;
        return G;
}
void initSchoolLocal(school* local,int index,char* s,int num,char* intro){    //学校地点信息的初始化
    local[index].num = num;
    strncpy(local[index].name, s, sizeof(local[index].name) - 1);
    local[index].name[sizeof(local[index].name) - 1] = '\0';
    strncpy(local[index].intro, intro, sizeof(local[index].intro) - 1);
    local[index].intro[sizeof(local[index].intro) - 1] = '\0';
}

void createGraph(Graph* G,school* vexs,int* arcs){  //图的创建
    for(int i = 0 ; i < G -> vexsnum ; i ++){
        G -> vexs[i].num = vexs[i].num;
        strcpy(G -> vexs[i].name,vexs[i].name);
        strcpy(G -> vexs[i].intro,vexs[i].intro);
        for(int j = 0 ; j < G -> vexsnum ; j++){
            G -> arcs[i][j] = *(arcs + i*G->vexsnum + j);
            if(G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX){
                G -> arcsnum ++;
            }
        }
    }
    G -> arcsnum /= 2;
}

int getmin(int* d,int* s,Graph* G){
    int min = MAX;
    int index;
    for(int i = 0 ; i < G -> vexsnum ; i ++){
        if(!s[i] && d[i]<min){
            min = d[i];
            index = i;
        }
    }
    return index;   //返回最小值的索引
}

void dijkstra(Graph* G,int index,int target){
    int* s = (int*)malloc(sizeof(int)*G->vexsnum);  //记录了目标顶点到其他顶点的最短路径是否求得
    int* p = (int*)malloc(sizeof(int)*G->vexsnum); //记录目标顶点到其他顶点的最短路径的前驱节点
    int* d = (int*)malloc(sizeof(int)*G->vexsnum); //记录目标顶点到其他顶点的最短路径长度

    for(int i = 0;i < G -> vexsnum;i ++){
        if(G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX){  //判断当前顶点到其他顶点是否可达
            d[i] = G -> arcs[index][i];
            p[i] = index;
        }else{
            d[i] = MAX;
            p[i] = -1;
        }
        if(i == index){
            s[i] = 1;
            d[i] = 0;
        }else{
            s[i] = 0;
        }
    }

    for(int i = 0 ; i < G  -> vexsnum ; i ++){
        //找到d数组中最小值
        int index = getmin(d,s,G);
        //将s数组中对应下标的值设为1
        s[index] = 1;
        //遍历d数组
        for(int j = 0 ; j < G -> vexsnum ; j ++){
            //如果s数组中对应下标的值不为1，且d数组中对应下标的值加上G数组中对应下标的值小于d数组中对应下标的值
            if(!s[j] && d[index] + G -> arcs[index][j] < d[j]){
                //将d数组中对应下标的值设为d数组中对应下标的值加上G数组中对应下标的值
                d[j] = d[index] + G -> arcs[index][j];
                //将p数组中对应下标的值设为index
                p[j] = index;
            }
        }
    }
    printf("%d \n",d[target]);
}

void DFS(Graph* G,int* visited,int index){  //深度优先遍历
        printf("V_%d ",G -> vexs[index].num);
        visited[index]=1;
        for(int i = 0 ; i < G -> vexsnum ; i ++){
            if(G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]){
                DFS(G,visited,i);
            }
        }
}

//增加场所
void addVertex(Graph* G , school* newVertex , int* newArc){
        if(G -> vexsnum < 10){

            G -> vexs[G -> vexsnum] = *newVertex;
            
            //添加新的矩阵行以及列
            for(int i = 0 ; i < G -> vexsnum ; i ++){
                G -> arcs[G->vexsnum][i] = newArc[i];
                G -> arcs[i][G -> vexsnum] = newArc[i];
                if(newArc[i]!=0 && newArc[i]!=MAX){
                    G -> arcsnum ++;
                }
            }

            G -> vexsnum ++;
        }
        else{
            printf("当前顶点数已达上限,请删除后再添加!");
        }
}

//删除场所
void deleteVertex(Graph* G,int index){
    if(index >=0 && index < G -> vexsnum){
        //执行删除操作
        for(int i = 0 ; i < G -> vexsnum ; i ++){
            G -> arcs[i][index] = MAX;
            G -> arcs[index][i] = MAX;
            if(G -> arcs[i][index] != 0 && G -> arcs[i][index] != MAX){
                G -> arcsnum -- ;
            }
        }

        //更新顶点信息
        for(int i = index ; i < G -> vexsnum -1 ; i ++){
            G -> vexs[i] = G -> vexs[i+1];
        }
        G -> vexsnum --;
        //更新代号
        for(int i = index ; i < G -> vexsnum; i ++){
            G -> vexs[i].num = G -> vexs[i].num - 1 ;
        }
        printf("删除操作已完成\n");
    }else{
        printf("超出索引范围\n");
    }
}

//修改场所
void modifyVertex(Graph* G , school* modifyvertex,int index){
    if(index >= 0 && index < G -> vexsnum){
        G -> vexs[index] = *modifyvertex;
        strcpy(G -> vexs[index].name,modifyvertex -> name);
    }else{
        printf("超出索引范围");
    }
}

//删除路径
void deleteArc(Graph* G , int start , int end){  //路径的删除
    if(start >= 0 && start < G -> vexsnum && end >=0 && end < G -> vexsnum){
        G -> arcs[start][end] = MAX;
        G -> arcs[end][start] = MAX;
        if(G -> arcs[start][end] != 0 && G -> arcs[start][end] != MAX){
            G ->arcsnum --;
        }
    }else{
        printf("无效的索引!");
    }
}

//增加路径
void addArc(Graph* G , int start , int end, int weight){ //增加路径操作
    if(start >= 0 && start < G -> vexsnum && end >=0 && end < G -> vexsnum && G -> arcs[start][end] == MAX){
        G -> arcs[start][end] = weight;
        G -> arcs[end][start] = weight;
        if(weight!= 0 && weight != MAX){
            G ->arcsnum ++;
        }
    }
    else{
        printf("无效的索引!检查是否路径已经存在或者该顶点不存在\n");
    }
}

//修改路径
void modifyArc(Graph* G , int start , int end, int weight){  //修改路径信息
    if(start >= 0 && start < G -> vexsnum && end >=0 && end < G -> vexsnum){
        G -> arcs[start][end] = weight;
        G -> arcs[end][start] = weight;
        if(weight!= 0 && weight != MAX){
            G ->arcsnum ++;
        }
        if(weight ==0 || weight == MAX){
            G -> arcsnum --;
        }
    }
}

//场景查询功能函数
void infoSearch(Graph* G){
    printf("欢迎使用查询系统！\n") ;
    printf("请输入场景的代号进行具体信息的查询：\n");
    for(int i = 0 ; i < G -> vexsnum ; i ++){
    printf("%d.%s  ",G -> vexs[i].num,G -> vexs[i].name);
    }
    printf("\n");
    int option1;
    scanf("%d",&option1);
    printf("该场景的具体信息为:%d.%s: %s \n",G -> vexs[option1-1].num,G -> vexs[option1-1].name,G -> vexs[option1-1].intro);
}

   /*用户函数区域*/
void initUser(Graph* G){
    G -> user = (User*)malloc(sizeof(User)*100); //假设系统最大容纳100名用户
}

//添加用户
void addUser(Graph* G ,char* username,char* password,int type){
    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.userType = type;

    G->user[G -> usernum] = newUser;
    G->usernum++;
}

//登录模块
int login(Graph* G , char* username,char* password){
    for(int i = 0 ; i < G -> usernum ; i ++){
        if(strcmp(username , G -> user[i].username )==0 && strcmp(password,G -> user[i].password)==0){
            return G -> user[i].userType;
        }
    }
    return 0;
}

//修改用户权限
int modifyuser(Graph* G ,char* username){
    int flag = 0;  //检验是否更改完成
    for(int i = 0 ; i < G -> usernum; i ++){
    if(strcmp(username,G -> user[i].username)==0){
        if(G -> user[i].userType == 1) G -> user[i].userType = 2;
        if(G -> user[i].userType == 2) G -> user[i].userType = 1;
        flag = 1;
    }
  }
  return flag;
}

int main(){
    Graph* G = initGraph(10);
    int arcs[10][10] = {
        {0,4,MAX,MAX,MAX,MAX,5,MAX,MAX,MAX},
        {4,0,7,MAX,MAX,MAX,MAX,MAX,MAX,MAX},
        {MAX,7,0,5,MAX,MAX,MAX,MAX,MAX,MAX},
        {MAX,MAX,5,0,1,4,MAX,3,MAX,MAX},
        {MAX,MAX,MAX,1,0,MAX,MAX,2,6,MAX},
        {3,MAX,MAX,4,MAX,0,MAX,MAX,MAX,MAX},
        {5,MAX,MAX,MAX,MAX,MAX,0,6,MAX,8},
        {MAX,MAX,MAX,3,2,MAX,6,0,7,MAX},
        {MAX,MAX,MAX,MAX,6,MAX,MAX,7,0,7},
        {MAX,MAX,MAX,MAX,MAX,MAX,8,MAX,7,0}
    };
    school local[10];
    initSchoolLocal(local,0,"西门",1,"学校的西大门");
    initSchoolLocal(local,1,"博物馆",2,"内设有校史馆及会议厅");
    initSchoolLocal(local,2,"学院楼",3,"各学院实验大楼");
    initSchoolLocal(local,3,"图书馆",4,"仙溪校区主图书馆");
    initSchoolLocal(local,4,"教学楼",5,"教学大楼，内有多个教室");
    initSchoolLocal(local,5,"食堂",6,"学生及教职工用餐地");
    initSchoolLocal(local,6,"宿舍",7,"学生休息处");
    initSchoolLocal(local,7,"钟楼",8,"标志性建筑");
    initSchoolLocal(local,8,"体育场",9,"学生及教职工进行体育活动的场所");
    initSchoolLocal(local,9,"北门",10,"学校的北大门，也是地铁站的进出站口");
    createGraph(G,local,arcs);

    int* visited = (int*)malloc(sizeof(int)*G->vexsnum);
	for(int i = 0; i < G -> vexsnum; i++){
		visited[i] = 0;
	}
    //DFS(G,visited,0);
    printf("\n");

    /*进行用户类型变量的定义*/
    //初始化
    initUser(G);
    addUser(G, "admin", "admin123", 2);
    addUser(G, "guest", "guest123", 1);
    addUser(G, "guest1", "guest123", 1);
    addUser(G, "guest2", "guest123", 1);
    //登录操作
    char username[30];
    char password[30];
    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);
    int userType = login(G, username, password);


    /*下面是操作菜单的定义*/
    int option;
    printf("======欢迎使用校园导游系统======\n");
    int operator = userType;
    //printf("%d",operator);
    while(1){
        if(operator == 1){
            printf("1.查询场所信息\n");
            printf("2.问路查询\n");
            printf("3.退出系统\n");
            printf("请选择需要进行的操作: ");
            scanf("%d",&option);
            printf("\n==================================\n");
                if(option == 1){  //查询场所
                    infoSearch(G);
                }

                if(option == 2){  //计算最短距离
                    printf("请输入地点1的代号: ");
                    int num1;
                    scanf("%d",&num1);
                    printf("\n");
                    printf("请输入地点2的代号: ");
                    int num2;
                    scanf("%d",&num2);
                    printf("\n");
                    printf("地点：%s 到 地点 %s 的最短路径距离为:  ",G ->vexs[num1-1].name,G ->vexs[num2-1].name);
                    dijkstra(G,num1-1,num2-1);
                    printf("\n");
                }
                
                if(option == 3){
                    return 0;
                }
        }
        if (operator ==2){
            printf("管理员您好!\n");
            printf("1.用户管理\n");
            printf("2.场所管理\n");
            printf("3.路径管理\n");
            printf("4.查看所有场所\n");
            printf("5.退出系统\n");
            printf("请选择需要进行的操作:\n");
            int option ;
            scanf("%d",&option);
            printf("==================================\n");
            if(option == 1){
                printf("请选择需要执行的操作:\n");
                printf("1.用户信息查看:\n");
                printf("2.用户权限修改:\n");
                int option1;
                scanf("%d",&option1);
                if(option1 == 1){
                    for(int i = 0 ; i < G -> usernum ; i ++){
                        printf("username: %s  password: %s  usertype: %d \n",G -> user[i].username,G -> user[i].password,G -> user[i].userType);
                    }
                }
                if(option1 == 2){
                    printf("请输入需要更改权限的用户名:\n");
                    char username[30];
                    scanf("%s",username);
                    int flag = modifyuser(G,username);
                    if(flag == 1){
                        printf("用户权限更改成功!\n");
                    }else{
                        printf("更改失败,请检查用户名是否存在!\n");
                    }
                }
            }

            if(option == 2){
                printf("请选择需要执行的操作:\n");
                printf("1.场所增加\n");
                printf("2.场所修改\n");
                printf("3.场所删除\n");
                int option1;
                scanf("%d",&option1);
                    if(option1 == 1){
                        if(G -> vexsnum < 10){
                        printf("目前系统所储存的场所有:\n");
                        for(int i = 0 ; i < G -> vexsnum ; i ++){
                            printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                        }
                        printf("\n");
                        school newVertex;                     
                        printf("请输入增加场所的名称: ");
                        scanf("%s",newVertex.name);
                        printf("请输入增加场所的代号: ");
                        scanf("%d",&newVertex.num);
                        getchar();
                        printf("请输入增加场所的简介: ");
                        scanf("%s",newVertex.intro);
                        int newArcs[10];
                        printf("请输入新顶点的邻接矩阵行（10个整数,不可达的请用32767代替）：");
                        for (int i = 0; i < 10; ++i) {
                            scanf("%d", &newArcs[i]);
                            }
                        addVertex(G, &newVertex, newArcs);
                    }
                        else printf("当前顶点数已达上限,请删除后再添加!\n");
                    }

                    if(option1 ==2){
                        printf("目前系统所储存的场所有:\n");
                        for(int i = 0 ; i < G -> vexsnum ; i ++){
                            printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                        }
                        printf("输入需要修改的场所编号：\n");
                        int num;
                        scanf("%d",&num);
                        school modifiedVertex;
                        printf("请输入要修改的顶点的名称：");
                        scanf("%s", modifiedVertex.name);
                        printf("请输入要修改的顶点的代号：");
                        scanf("%d", &modifiedVertex.num);
                        printf("请输入要修改的顶点的简介：");
                        scanf("%s", modifiedVertex.intro);
                        modifyVertex(G,&modifiedVertex,num-1);

                    }
                    if(option1 == 3){
                        printf("目前系统所储存的场所有:\n");
                            for(int i = 0 ; i < G -> vexsnum ; i ++){
                                 printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                            }
                        printf("请输入需要删除的顶点代码\n");
                        int num3;
                        scanf("%d",&num3);
                        deleteVertex(G,num3-1);
                    }

        }

            if(option == 3){
                int option1;
                printf("请选择需要执行的操作:\n");
                printf("1.路径增加\n");
                printf("2.路径修改\n");
                printf("3.路径删除\n");
                scanf("%d",&option1);
                if(option1 == 3){
                    printf("目前系统所储存的场所有:\n");
                            for(int i = 0 ; i < G -> vexsnum ; i ++){
                                 printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                            }
                    printf("请输入需要删除的路径的两个顶点之间的编号:\n");
                    int num1,num2;
                    scanf("%d %d",&num1,&num2);
                    printf("原两路径的距离为%d\n",G -> arcs[num1-1][num2-1]);
                    deleteArc(G,num1-1,num2-1);
                    printf("删除后两路径的距离为%d\n",G -> arcs[num1-1][num2-1]);
                }

                if(option1 == 1){
                    printf("目前系统所储存的场所有:\n");
                            for(int i = 0 ; i < G -> vexsnum ; i ++){
                                 printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                            }
                    printf("请输入需要增加的路径的两个顶点之间的编号:\n");
                    int num1,num2,weight;
                    scanf("%d %d",&num1,&num2);
                    printf("原两路径的距离为%d\n",G -> arcs[num1-1][num2-1]);
                    printf("请输入需要增加的路径的两个顶点之间的权值:\n");
                    scanf("%d",&weight);
                    addArc(G,num1-1,num2-1,weight);
                    printf("增加后两路径的距离为%d\n",G -> arcs[num1-1][num2-1]);
                }

                if(option1 == 2){
                    printf("目前系统所储存的场所有:\n");
                            for(int i = 0 ; i < G -> vexsnum ; i ++){
                                 printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                            }
                    printf("请输入需要修改的路径的两个顶点之间的编号:\n");
                    int num1,num2,weight;
                    scanf("%d %d",&num1,&num2);
                    printf("原两路径的距离为%d\n",G -> arcs[num1-1][num2-1]);
                    printf("请输入需要修改的路径的两个顶点之间的权值:\n");
                    scanf("%d",&weight);
                    modifyArc(G,num1-1,num2-1,weight);
                    printf("修改后两路径的距离为%d\n",G -> arcs[num1-1][num2-1]);
                }
                   
            }
            if(option == 4){
                    printf("目前系统所储存的场所有:\n");
                            for(int i = 0 ; i < G -> vexsnum ; i ++){
                                 printf("代号为:%d 场所名: %s\n",G -> vexs[i].num,G -> vexs[i].name);
                            }
                }
            if(option == 5){
                return 0;
            }        
        }
    }
}