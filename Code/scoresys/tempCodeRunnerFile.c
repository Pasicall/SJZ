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
            if(system -> deparment[index[i]].male_totalscore > system -> deparment[index[j]].male_totalscore){
                int temp = index[i];
                for(int k = i - 1 ; k >= j ; k --){
                    index[k + 1] = index[k];
                }
                index[j] = temp;
            }
        }
        
    }
    printf("男子总分排序为:");
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
    printf("女子总分排序为:");
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

//按照团队总分排序
void QuickSort(System* system){
    int index[system->department_num];
    for(int i = 0 ; i < system ->department_num ; i ++){
        index[i] = system -> deparment[i].depart_id - 1;
    }

    Qsort(index,0,system->department_num-1,system);

    printf("团队总分排序为:");
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
int Partition(int* arr,int left,int right,System* system){
    int base = arr[left];
    while(left < right){
        while(left < right && system -> deparment[arr[right]].team_totalscore < system -> deparment[base].team_totalscore){
            right --;
        }
        arr[left] = arr[right];
        while(left < right && system -> deparment[arr[left]].team_totalscore >= system -> deparment[base].team_totalscore){
            left ++;
        }
        arr[right] = arr[left];
    }
    arr[left] = base;
    return left;
}

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
