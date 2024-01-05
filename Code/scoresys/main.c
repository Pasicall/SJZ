#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SCORE 50
#define MAX_DEPARTMENT 10

typedef struct Department{  //定义部门结构体
    int depart_id;
    char name[20];
    int male_score[6];
    int male_index;
    int male_totalscore;
    int female_score[6];
    int female_index;
    int female_totalscore;
    int team_score[6];
    int team_index;
    int team_totalscore;
    int totalscore;
}Department;

typedef struct ScoreManegeSystem{     //定义管理系统结构体
    Department deparment[MAX_DEPARTMENT];
    int department_num;
}System;

void addDepartment(System* system , int depart_id , char* name,int index);
void addScore(System* system , Department* department);
void initDepartment(System* system);
void totalScore(System* system);
void printDepartment(System* system);
void bubblesort(System* system);  //冒泡排序算法
void insertsort(System* system); //直接插入排序算法
void selectionsort(System* system);//选择排序算法
void QuickSort(System* system);  //快速排序算法
void Qsort(int* arr,int left,int right,System* system);
int Partition(int* arr,int left,int right,System* system);   
void deSearch(System* system);          //按部门编号查询
void projectSearch(System* system);     //项目编号查询
void writeDepartment(System* system);

int main(){
    System system;
    system.department_num = 0;
    initDepartment(&system);
    totalScore(&system);

    //操作菜单
    int option;
    printf("======欢迎使用运动会分数管理系统======\n");
    while(1){
        printf("请选择需要进行的操作:\n");
        printf("1.按部门编号输出:\n");
        printf("2.按部门总分输出:\n");
        printf("3.按男子总分输出:\n");
        printf("4.按女子总分输出:\n");
        printf("5.按团体总分输出:\n");
        printf("6.按部门编号查询:\n");
        printf("7.按项目编号查询:\n");
        printf("8.导出数据\n");
        printf("9.退出系统:\n");
        scanf("%d",&option);

        switch(option){
            case 1 :
               printDepartment(&system);
                break;
            case 2 :
                bubblesort(&system);
                break;
            case 3 :
                insertsort(&system);
                break;
            case 4 :
                selectionsort(&system);
                break;
            case 5 :
                QuickSort(&system);
                break;
            case 6 :
                deSearch(&system);
                break;
            case 7 :
                projectSearch(&system);
                break;
            case 8 :
            writeDepartment(&system);
                break;
            case 9:
            return 0;
        }
    }
     //bubblesort(&system);
     //insertsort(&system);
     //selectionsort(&system);
    //QuickSort(&system);
    deSearch(&system);
    projectSearch(&system);
    //printDepartment(&system);
    return 0;
}




                            /* 
                                功能实现函数区
                                                */
void addDepartment(System* system , int depart_id , char* name,int index){
    if (system -> department_num < MAX_DEPARTMENT){
        Department newdepartment;
        newdepartment.depart_id = depart_id;
        strcpy(newdepartment.name,name);
        system -> deparment[system -> department_num ++] = newdepartment;  
    }else{
        printf("超出最大部门数量\n!");
    }
}

void initDepartment(System* system){
    addDepartment(system, 1 , "DeparmentA",0);
    addDepartment(system, 2 , "DeparmentB",0);
    addDepartment(system, 3 , "DeparmentC",0);
    addDepartment(system, 4 , "DeparmentD",0);
    addDepartment(system, 5 , "DeparmentE",0);
    addDepartment(system, 6 , "DeparmentF",0);


    //进行分数的初始化
    for(int i = 0 ; i < system->department_num ; i ++){
        system -> deparment[i].male_index = 0;
        system -> deparment[i].female_index = 0;
        system -> deparment[i].team_index = 0;
        system -> deparment[i].totalscore = 0 ;
        system -> deparment[i].male_totalscore = 0 ;
        system -> deparment[i].female_totalscore = 0 ;
        system -> deparment[i].team_totalscore = 0 ;

        for(int j = 0 ; j < 6 ; j ++){  
            system -> deparment[i].male_score[j] = 0 ; 
            system -> deparment[i].female_score[j] = 0 ; 
            system -> deparment[i].team_score[j] = 0 ;    
        }
    }
    addScore(system,system->deparment);
}


//添加成绩到部门
void addScore(System* system , Department* department ){
    printf("请输入男子项目前六名所属部门编号: \n");
    for(int i = 0 ; i < 6 ; i ++){
        printf("第 %d 名  : " , i+1);
        int index;
        scanf("%d",&index);  //记录对应编号的部门的计算男子分数的数组
        switch(i) {
            case 0:
            system -> deparment[index-1].male_score[system->deparment[index-1].male_index++] = 7;
            break;

            case 1:
            system -> deparment[index-1].male_score[system->deparment[index-1].male_index++] = 5;
            break;

            case 2:
            system -> deparment[index-1].male_score[system->deparment[index-1].male_index++] = 4;
            break;

            case 3:
            system -> deparment[index-1].male_score[system->deparment[index-1].male_index++] = 3;
            break;

            case 4:
            system -> deparment[index-1].male_score[system->deparment[index-1].male_index++] = 2;
            break;

            case 5:
            system -> deparment[index-1].male_score[system->deparment[index-1].male_index++] = 1;
            break;
        }
        
    }

     printf("请输入女子项目前六名所属部门编号: \n");
    for(int i = 0 ; i < 6 ; i ++){
        printf("第 %d 名  : " , i+1);
        int index;
        scanf("%d",&index);  //记录对应编号的部门的计算女子分数的数组
        switch(i) {
             case 0:
            system -> deparment[index-1].female_score[system->deparment[index-1].female_index++] = 7;
            break;

            case 1:
            system ->  deparment[index-1].female_score[system->deparment[index-1].female_index++] = 5;
            break;

            case 2:
            system ->  deparment[index-1].female_score[system->deparment[index-1].female_index++] = 4;
            break;

            case 3:
            system ->  deparment[index-1].female_score[system->deparment[index-1].female_index++] = 3;
            break;

            case 4:
            system ->  deparment[index-1].female_score[system->deparment[index-1].female_index++] = 2;
            break;

            case 5:
            system ->  deparment[index-1].female_score[system->deparment[index-1].female_index++] = 1;
            break;
        }
    }

    printf("请输入团体项目前六名所属部门编号: \n");
    for(int i = 0 ; i < 6 ; i ++){
        printf("第 %d 名  : " , i+1);
        int index;
        scanf("%d",&index);  //记录对应编号的部门的计算团体分数的数组
        switch(i) {
             case 0:
            system -> deparment[index-1].team_score[system->deparment[index-1].team_index++] = 14;
            break;

            case 1:
            system ->  deparment[index-1].team_score[system->deparment[index-1].team_index++] = 10;
            break;

            case 2:
            system ->  deparment[index-1].team_score[system->deparment[index-1].team_index++] = 8;
            break;

            case 3:
            system ->  deparment[index-1].team_score[system->deparment[index-1].team_index++] = 6;
            break;

            case 4:
            system ->  deparment[index-1].team_score[system->deparment[index-1].team_index++] = 4;
            break;

            case 5:
            system ->  deparment[index-1].team_score[system->deparment[index-1].team_index++] = 2;
            break;
        }
    }
}

//计算总分
void totalScore(System* system){
    //部门总分
    for(int i = 0 ; i < system -> department_num ; i ++){
        for(int j = 0 ; j < 6 ; j ++ ){
            system -> deparment[i].totalscore += system ->deparment[i].male_score[j];
            system -> deparment[i].totalscore += system ->deparment[i].female_score[j];
            system -> deparment[i].totalscore += system ->deparment[i].team_score[j];
        }
    }
    //男子总分
    for(int i = 0 ; i < system -> department_num ; i ++){
        for(int j = 0 ; j < 6 ; j ++ ){
            system -> deparment[i].male_totalscore += system ->deparment[i].male_score[j];
        }
    }
    //女子总分
     for(int i = 0 ; i < system -> department_num ; i ++){
        for(int j = 0 ; j < 6 ; j ++ ){
            system -> deparment[i].female_totalscore += system ->deparment[i].female_score[j];
        }
    }
    //团队总分
     for(int i = 0 ; i < system -> department_num ; i ++){
        for(int j = 0 ; j < 6 ; j ++ ){
            system -> deparment[i].team_totalscore += system ->deparment[i].team_score[j];
        }
    }
}

//按照部门总分排序
void bubblesort(System* system){

    int index[system->department_num];
    int temp;                       
    for(int i = 0 ; i < system ->department_num ; i ++){
        index[i] = system -> deparment[i].depart_id - 1;
    }

    for(int i = 0 ; i < system -> department_num -1 ; i ++){
        for(int j = 0 ; j < system -> department_num -1 - i; j ++){
            if(system -> deparment[index[j]].totalscore < system -> deparment[index[j+1]].totalscore){
                 temp = index[j];
                 index[j] = index[j+1];
                 index[j+1] = temp;
            }
    }
 }

    printf("部门总分排序为: \n");
    for(int i = 0 ; i < system -> department_num ; i ++){
      printf("第 %d 名 : %s  总分为: %d \n", i+1 , system -> deparment[index[i]].name , system ->deparment[index[i]].totalscore);
    }
    //将printf的内容写入文件
    FILE *fp = fopen("department_totalscore.txt","w");
    fprintf(fp,"部门名次    部门名称    部门总分\n");
    for(int i = 0 ; i < system -> department_num ; i ++){
      fprintf(fp,"第 %d 名   %s      %d \n", i+1 , system -> deparment[index[i]].name , system ->deparment[index[i]].totalscore);
    }
    fclose(fp);
}

//按照男子项目总分排序
void insertsort(System* system){
    int index[system->department_num];
    int temp;                       
    for(int i = 0 ; i < system ->department_num ; i ++){
        index[i] = system -> deparment[i].depart_id - 1;
    }

    for(int i = 1 ; i < system -> department_num ; i ++){
        for (int j = 0; j < i; j ++)
        {
            //比较第i个部门和第j个部门男性总得分
            if(system -> deparment[index[i]].male_totalscore > system -> deparment[index[j]].male_totalscore){
                //如果第i个部门得分高，则交换位置
                int temp = index[i];
                for(int k = i - 1 ; k >= j ; k --){
                    index[k + 1] = index[k];
                }
                index[j] = temp;
            }
        }
        
    }
    printf("男子总分排序为:\n");
    for (int i = 0; i < system -> department_num; i++){
       // printf("%d\n",index[i]);
        printf("第 %d 名 : %s  男子总分为: %d \n", i+1 , system -> deparment[index[i]].name , system -> deparment[index[i]].male_totalscore);
    }  
    //将printf的内容输出到文件中
    FILE *fp = fopen("male_totalscore.txt","w");
    fprintf(fp,"部门名次    部门名称     男子总分\n");
    for (int i = 0; i < system -> department_num; i++){
        fprintf(fp,"第 %d 名   %s        %d \n", i+1 , system -> deparment[index[i]].name , system -> deparment[index[i]].male_totalscore);
    }
    fclose(fp);
}

//按照女子项目总分排名
void selectionsort(System* system){
    int index[system->department_num];
    int temp,max;                       
    for(int i = 0 ; i < system ->department_num ; i ++){
        index[i] = system -> deparment[i].depart_id - 1;
    }
    for(int i = 0; i < system -> department_num - 1 ;i ++){
        max = i ;
        for(int j = i + 1 ; j < system ->department_num ; j ++ ){
            if(system -> deparment[max].female_totalscore < system -> deparment[index[j]].female_totalscore)
                max = j ;
        }
        temp = index[i];
        index[i] = index[max];
        index[max] = temp;
    }
    printf("女子总分排序为:\n");
    for (int i = 0; i < system -> department_num; i++){
       // printf("%d\n",index[i]);
        printf("第 %d 名   %s  女子总分为: %d \n", i+1 , system -> deparment[index[i]].name , system -> deparment[index[i]].female_totalscore);
    }
    //将printf的内容输出到文件中
    FILE *fp = fopen("female_totalscore.txt","w");
    fprintf(fp,"部门名次    部门名称     女子总分\n");
    for (int i = 0; i < system -> department_num; i++){
        fprintf(fp,"第 %d 名   %s       %d \n", i+1 , system -> deparment[index[i]].name , system -> deparment[index[i]].female_totalscore);
    }
    fclose(fp);

}

/*按照团队总分排序*/
void QuickSort(System* system){
    int index[system->department_num];
    for(int i = 0 ; i < system ->department_num ; i ++){
        index[i] = system -> deparment[i].depart_id - 1;
    }

    Qsort(index,0,system->department_num-1,system);

    printf("团队总分排序为:\n");
    for (int i = 0; i < system -> department_num; i++){
       // printf("%d\n",index[i]);
        printf("第 %d 名   %s  团队总分为: %d \n", i+1 , system -> deparment[index[i]].name , system -> deparment[index[i]].team_totalscore);
    }

    FILE *fp = fopen("team_totalscore.txt","w");
    fprintf(fp,"部门名次    部门名称     团队总分\n");
    for (int i = 0; i < system -> department_num; i++){
        fprintf(fp,"第 %d 名   %s       %d \n", i+1 , system -> deparment[index[i]].name , system -> deparment[index[i]].team_totalscore);
    }
    fclose(fp);
}

void Qsort(int* arr,int left,int right,System* system){  
    if(left < right){
        int index = Partition(arr,left,right,system);
        Qsort(arr,left,index-1,system);
        Qsort(arr,index+1,right,system);
    }
}
int Partition(int* arr,int left,int right,System* system){  //用于基准元素于其他元素的比较
    int base = arr[left];
    while(left < right){
        //当left小于right，且arr[right]的分数小于base的分数时，right减一
        while(left < right && system -> deparment[arr[right]].team_totalscore < system -> deparment[base].team_totalscore){
            right --;
        }
        //将arr[right]的值赋给arr[left]
        arr[left] = arr[right];
        //当left小于right，且arr[left]的分数大于等于base的分数时，left加一
        while(left < right && system -> deparment[arr[left]].team_totalscore >= system -> deparment[base].team_totalscore){
            left ++;
        }
        //将arr[left]的值赋给arr[right]
        arr[right] = arr[left];
    }
    //当left等于right时，将base的值赋给arr[left]
    arr[left] = base;
    return left;
}
/*按照团队总分排序*/

//通过部门编号查询
void deSearch(System* system){
    printf("请输入需要查询的部门编号: \n");
    int index;
    scanf("%d",&index);
    printf("请输入需要查询的项目编号:\n");
    printf("1.男子项目\n");
    printf("2.女子项目\n");
    printf("3.团体项目\n");
    int option;
    scanf("%d",&option);
    switch(option){
        printf("该部门的得分情况为:\n");
        case 1:
            printf("男子项目得分: %d \n",system -> deparment[index-1].male_totalscore);
            break;
        case 2:
            printf("女子项目得分: %d \n",system -> deparment[index-1].female_totalscore);
            break;
        case 3:
            printf("团体项目得分: %d \n",system -> deparment[index-1].team_totalscore);
            break;
    }
}

//通过项目名称查询
void projectSearch(System* system){
    printf("请输入需要查询的项目编号:\n");
    printf("1.男子项目\n");
    printf("2.女子项目\n");
    printf("3.团体项目\n");
    int option;
    scanf("%d",&option);
    switch(option){
        case 1:
            insertsort(system);
            break;
        
        case 2:
            selectionsort(system);
            break;

        case 3:
            QuickSort(system);
            break;
    }

}

void printDepartment(System* system){
    for(int i = 0 ; i < system->department_num ; i ++){
        printf("部门名称: %s  部门编号 %d \n" , system -> deparment[i].name,system -> deparment[i].depart_id);
        printf("部门总分为:%d\n",system->deparment[i].totalscore);
        printf("\n");
    }
    
}

//将部门总分写入文件
void writeDepartment(System* system){
    FILE* fp = fopen("department.txt","w");
    //写入自定义文字到文件
    fprintf(fp,"部门名称    部门编号    部门总分\n");
    for(int i = 0 ; i < system->department_num ; i ++){
        fprintf(fp,"%s     %d         %d\n",system -> deparment[i].name,system -> deparment[i].depart_id,system -> deparment[i].totalscore);
    }
    
    fclose(fp);
}


