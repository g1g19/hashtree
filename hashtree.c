#include<stdio.h>
#include<stdlib.h>

typedef struct itemnode
{
    int** id;
    long support;
}item;

typedef struct treenode
{
	struct treenode* left;
	struct treenode* right;
	struct treenode* self;
	
	item** list;
}tnode;
int** transac;
item C1[75+1];
item** F1;
int rows,columns,j,k,zx,yx,f1,ctr;
void generateitemsetC1(void);
item** generate_candidate_itemset(item** F,int Fsize,int ctr);
int check(int x,int** id,int ctr);
tnode* hashtree(void);
void hash(tnode** T,int* s,int count);
void update_hashtree(tnode* T,int count);
void generate_Freqitemset(tnode* T,float support,int count,FILE* fk,FILE* fb);

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
	F1 = (item**)malloc(1000*sizeof(item*));
	long long h;
	for(h=0;h<1000;h++)
	{
		F1[h] = (item*)malloc(sizeof(item));
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
	item** F = F1;
	item** C = NULL;
	tnode* T = NULL;
	int Fsize = zx;
	f1 = zx;
	ctr = 1;
	int g,z,d,temp,b,bn;	
	FILE* fk = NULL;
	FILE* fb = NULL;
	int q[75];
	while(F != NULL)
	{
		if(T != NULL)
		   free(T);
		T = NULL;
		generate_candidate_itemset(F,Fsize,ctr);
		//if(ctr == 5)
		//	break;
		printf("Almost there\n");
		T = hashtree();
		printf("Almost there2\n");
		update_hashtree(T,ctr+1);
		printf("Almost there3\n");
		fk = fopen("output","w");
		fb = fopen("support","w");		
		fprintf(fk,"%d\n",ctr+1);
		printf("Almost there4\n");
		generate_Freqitemset(T,0.9,ctr+1,fk,fb);	
		printf("Almost there5\n");	
		printf("T3 = %p\n",T);	
		fclose(fk);
		fclose(fb);
		if(F != F1)
			free(F);
		F = NULL;
		fk = fopen("output","r");
		fb = fopen("support","r");
		fscanf(fk,"%d",&bn);
		Fsize = 0;
		int kh = 0;
		if(fscanf(fk,"%d",&q[0]) == EOF)
		{
			F = NULL;
		}
		else
		{
			fclose(fk);
			fk = fopen("output","r");
			fscanf(fk,"%d",&bn);
			F = (item**)malloc(100000*sizeof(item*));
			for(kh = 0;kh < 100000; kh++)
			{
				F[kh] = (item*)malloc(sizeof(item));
			}
			int y= 0;
			while(fscanf(fk,"%d",&q[0]) != EOF)
			{
				Fsize++;
				for(kh=1;kh<ctr+1;kh++)
				{
					fscanf(fk,"%d",&q[kh]);
				}
				fscanf(fb,"%d",&bn);
				F[y]->id = (int**)malloc((ctr+1)*sizeof(int));
				int z = 0;		
				kh = 0;
				for(z=0;z<(ctr+1);z++)
				{
					F[y]->id[z] = (int*)malloc(sizeof(int));
					F[y]->id[z][0] = q[kh];
					kh++;
				}
				F[y]->support = bn;
				y++;
			}
			
			fclose(fk);	
			fclose(fb);
		}
		ctr++;	
		
	}
	
}

void generateitemsetC1(void)
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
		if(C1[i].support > (0.9*rows))  //support 
		{
			F1[j]->id = (int**)malloc(sizeof(int*));
			*(F1[j])->id = (int*)malloc(sizeof(int));			
			**(F1[j])->id = i;
			(*F1[j]).support = C1[i].support;
			j++;
		}
	}
	zx = j;
	f1 = j;
}



item** generate_candidate_itemset(item** F,int Fsize,int ctr)
{
	FILE* fl = fopen("output","w");
	fprintf(fl,"%d\n",ctr+1);
	int i,j,p,q;
	k = 0;
	item** C;
	printf("Fsize = %d\n",Fsize);
	C = (item**)malloc((Fsize*f1)*sizeof(item*));
	for(i=0;i<Fsize;i++)
	{
	   for(j=0;j<f1;j++)
	   {
		if(check(**((F1[j])->id),F[i]->id,ctr))
		{
			C[k] = (item*)malloc(sizeof(item));
			C[k]->id = NULL;
			C[k]->support = 0;
			C[k]->id = (int**)malloc((ctr+1)*sizeof(int*));
			int c = 0;
			for(c=0;c<=ctr;c++)
			{			
				(C[k]->id)[c] = (int*)malloc(sizeof(int));
			}
							
			*((C[k]->id))[0] = *(F1[j]->id)[0];
			fprintf(fl,"%d ",*(C[k]->id)[0] );
			for(p=0;p<ctr;p++)
			{
				*(C[k]->id)[p+1] = *((F[i])->id)[p];
				if(*(C[k]->id)[p+1] > 75)
					*(C[k]->id)[p+1] = *(C[k]->id)[p+1]%75;
				
				fprintf(fl,"%d ",*(C[k]->id)[p+1] );
			}
			fprintf(fl,"\n");
			k++;
		}
	   }
	}
	yx = k;
	fclose(fl);
	return C;
}

int check(int x,int** id,int ctr)
{
	int check = 1;
	int i;
	for(i=0;i<ctr;i++)
	{
		if(id[i][0] == x)
		{
			check = 0;
			break;
		}
	}
	return check;
}

tnode* hashtree(void)
{
     FILE* f = fopen("output","r");		
     if(f == NULL)
     {	
	printf("FILE ERROR\n");
	exit(1);
     }
     tnode* T = NULL;
     int count,i;
     fscanf(f,"%d",&count);
     int s[100];
     while((fscanf(f,"%d",&s[0])) != EOF)
     {
	for(i=1; i<count; i++)
	{
	   fscanf(f,"%d",&s[i]);
        }
	hash(&T,s,count);
     }
    return T;
}


void hash(tnode** T,int* s,int count)
{
	if(*T == NULL)
	{
		(*T) = (tnode*)malloc(sizeof(tnode));
		(*T)->left = NULL;
		(*T)->right = NULL;
		(*T)->self = NULL;
		(*T)->list = NULL;
	}
	int i,n;
	tnode* temp = *T;
	for(i=0;i<count;i++)
	{
		n = s[i]%3;
		if(n == 1 || n == 4 || n == 7)
		{
			if(temp->left != NULL)
			{
				temp = temp->left;
			}
			else
			{
				temp->left = (tnode*)malloc(sizeof(tnode));
				temp->left->left = NULL;
				temp->left->right = NULL;
				temp->left->self = NULL;
				temp->left->list = NULL;
				temp = temp->left;
			}
			
		}
		else if(n == 2 || n == 5 || n == 8)
		{
			if(temp->self != NULL)
			{
				temp = temp->self;
			}
			else
			{
				temp->self = (tnode*)malloc(sizeof(tnode));
				temp->self->left = NULL;
				temp->self->right = NULL;
				temp->self->self = NULL;
				temp->self->list = NULL;
				temp = temp->self;
			}
		}
		else
		{
			if(temp->right != NULL)
			{
				temp = temp->right;
			}
			else
			{
				temp->right = (tnode*)malloc(sizeof(tnode));
				temp->right->left = NULL;
				temp->right->right = NULL;
				temp->right->self = NULL;
				temp->right->list = NULL;
				temp = temp->right;
			}
		}
	}
	int h;
	if(temp->list == NULL)
	{
		temp->list = (item**)malloc(100000*sizeof(item*));
		for(h=0;h<100000;h++)
		{
			temp->list[h] = NULL;		
		}
	}
	h = 0;
	while(temp->list[h] != NULL)
	{
		h++;
	}
	temp->list[h] = (item*)malloc(sizeof(item));
	(temp->list[h])->id = (int**)malloc(75*sizeof(int*));
	int y;
	int uh;
	for(uh=0;uh<75;uh++)
	{
	   (temp->list[h]->id[uh]) = (int*)malloc(count*sizeof(int));
	}
	for(y=0;y<count;y++)
	{	
		temp->list[h]->id[y][0] = s[y];		
		(temp->list[h])->support = 0;
	}
	return;
}

void update_hashtree(tnode* T,int count)
{	
	if(T == NULL)
	    return;
	int i,j,k,check;
	i = 0;
	if(T->list != NULL)
	{
	    check = 1;
	    while(T->list[i] != NULL)
	    {
		for(k=0;k<rows;k++)
		{
			check = 1;
			for(j=0;j<count;j++)
			{
			if(T->list[i]->id != NULL && T->list[i]->id[j] != NULL && !transac[k][T->list[i]->id[j][0]])
			{
				check = 0;
			}
			}
			if(check == 1)	
			{
				T->list[i]->support++;
			}
		}		
		i++;
	    }
	}
	update_hashtree(T->left,count);
	update_hashtree(T->self,count);
	update_hashtree(T->right,count);
	return;
}

void generate_Freqitemset(tnode* T,float support,int count,FILE* fk,FILE* fb)
{
	if(T == NULL)
	{
	    return;
	}
	long ths = support*rows;
	int i = 0,j = 0;
	while(T->list != NULL && T->list[i] != NULL)
	{
		if(T->list[i]->support >= ths)
		{
			for(j = 0; j < count; j++)
			{
				fprintf(fk,"%d ",T->list[i]->id[j][0]);			
			}
			fprintf(fb,"%ld\n",T->list[i]->support);
			fprintf(fk,"\n");
		}
		i++;
	}
	generate_Freqitemset(T->left,support,count,fk,fb);
	generate_Freqitemset(T->self,support,count,fk,fb);
	generate_Freqitemset(T->right,support,count,fk,fb);
}










