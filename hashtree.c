#include<stdio.h>
#include<stdlib.h>

typedef struct itemnode
{
    int** id;
    long support;
}item;
int** transac;
item C1[75+1];
item F1[40];
int rows;
int columns;
void generateitemsetC1();
item* generate_candidate_itemset(item* F1,int a);
int j;

int main(void)
{
        char filename[25];
        printf("Enter filename: ");  
	scanf("%s",filename);
	FILE* fp1 = fopen(filename,"r");
	if( fp1 == NULL )
   	{
      		perror("Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
	int s,count;
	count = 0;
	while(fscanf(fp1,"%d",&s) != EOF)
	{
	   count++;
	}
	rows = (count/37);
	columns = 75+1;
	transac = (int**)malloc(rows*sizeof(int*));
	int i,j;
	for(i=0;i<rows;i++)
	{
		transac[i] = (int*)malloc(columns*sizeof(int));
		for(j=1;j<columns;j++)
			transac[i][j] = 0;
	}
	i = 1; j = 1;
	int k = 0;
	fclose(fp1);
	fp1 = fopen(filename,"r");

	while(fscanf(fp1,"%d",&i) != EOF)
	{
		j++;
		transac[k][i] = 1;
		if(j == 38)
		{
		     j = 1;
		     k++;
 	        }
	}
	generateitemsetC1();
	int counter = 2;
	itemnode* F = F1;
	itemnode* C = NULL;
	itemnode* T = NULL;
	int Fsize = j;
	while(F != NULL)
	{
		C = generate_candidate_itemset(F,Fsize);
		//T = hashtree(C);
		//update_hashtree(T,transac);
		//F = generate_Freqitemset(T,support);
	}
	
}

void generateitemsetC1()
{
	int i = 0;
	for(i=1;i<76;i++)
	{
		C1[i].id = (int**)malloc(sizeof(int*));
		*(C1[i].id) = (int*)malloc(sizeof(int));
		**(C1[i].id) = i;
		C1[i].support = 0;
	}

	int k;
	j=0;k=0;
	i=1;	
	for(j=0;j<rows;j++)
	{
		for(k=1;k<columns;k++)
		{
			if(transac[j][k])
			{
				C1[k].support++;
			}
				
		}
	}
	j=0;
	for(i=1;i<76;i++)
	{
		printf("C1[%d].support = %ld\n",i,C1[i].support);
		if(C1[i].support > (0.9*rows))  //support = 80%
		{
			F1[j].id = (int**)malloc(sizeof(int*));
			*(F1[j].id) = (int*)malloc(sizeof(int));			
			**(F1[j].id) = i;
			F1[j].support = C1[i].support;
			j++;
		}
	}
	for(i=0;i<j;i++)
	{
		printf("F1[%d].support = %ld\n",i,F1[i].support);
	}
}









