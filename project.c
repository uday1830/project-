#include<stdio.h>
#include<stdlib.h>   //following code is done using avl trees concepts
#include<string.h>

struct members  // structure for members 
{
	int member_id;
	int age;
	char name[50];
	char gender[10];
	int numofprograms;
	int programs[4];
	int feespaid[4];
	int heightm;
	
	struct members* left;
	struct members* right;
};

struct trainers        // structures for trainers
{
	int trainer_id;
	char name[50];
	int totalprograms;
	int trainerprograms[4];
	int remun;
	int height;
	
	struct trainers* left;
	struct trainers* right;
};
void printmember(struct members* root1 )  //prints the member node data 
{
	int i;
	printf("\n member id is %d ",root1->member_id);
	printf("\n the age of the member is %d ",root1->age);
	printf("\n the name of the member is %s ",root1->name);
	printf("\n the gender of the member is %s ",root1->gender);
	printf("\n total number of programs taken by the member is %d",root1->numofprograms);
	printf("\n programs taken by the member is/are ");
	for(i=0;i<root1->numofprograms;i++)
	{
		if(root1->programs[i]==1)
		{
			printf("\n yoga");
		}
		else if(root1->programs[i]==2)
		{
			printf("\n cardio");
		}
		else if(root1->programs[i]==3)
		{
			printf("\n zumba");
		}
		else if(root1->programs[i]==4)
		{
			printf("\n weight lifting");
		}
	}
	printf("\n the fees paid for the each program by the member is ");
	for(i=0;i<root1->numofprograms;i++)
	{
		printf("\n %d",root1->feespaid[i]);
	}
}
void printtrainer(struct trainers* root1 )  //prints the trainer nodes data
{
	int i;
	printf("\n trainer id is %d ",root1->trainer_id);
	printf("\n the name of the trainer is %s ",root1->name);
	printf("\n total number of programs taught by the trainer is %d",root1->totalprograms);
	printf("\n programs taught by the trainer is/are ");
	for(i=0;i<root1->totalprograms;i++)
	{
		if(root1->trainerprograms[i]==1)
		{
			printf("\n yoga");
		}
		else if(root1->trainerprograms[i]==2)
		{
			printf("\n cardio");
		}
		else if(root1->trainerprograms[i]==3)
		{
			printf("\n zumba");
		}
		else if(root1->trainerprograms[i]==4)
		{
			printf("\n weight lifting");
		}
	}
	printf("\n the remuniration taken for each program by the trainer is ");
	printf("\n %d",root1->remun);
	
}
int max(int a,int b)  //returns the maximum value 
{
	if(a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
int heightmm(struct members *m) // gibes height of a node in a member tree
{
    if (m==NULL)
    {
	return 0;
    }
    else
    {
    return 1+max(heightmm(m->left), heightmm(m->right));
	}
    
}
int heighttt(struct trainers *t)  // gives height of a node in a  trainer tree
{
    if (t==NULL)
    {
	return 0;
    }
    else
    {
    return 1+max(heighttt(t->left), heighttt(t->right));
	}
    
}
struct members *rightRotatem(struct members *y)  //it is for right rotating a member tree useful in making a tree avl
{
    struct members *x = y->left;
    struct members *T2 = x->right;
 
    x->right = y;
    y->left = T2;                       
    y->heightm = heightmm(y);
    x->heightm = heightmm(x);
    return x;
}
struct members *leftRotatem(struct members *x) //it is for left rotating a trainer tree useful in making avl tree
{
    struct members *y = x->right;
    struct members *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    x->heightm = heightmm(x);
    y->heightm = heightmm(y);
    return y;
}
struct trainers *rightRotatet(struct trainers *y)// right rotating function for trainer 
{
    struct trainers *x = y->left;
    struct trainers *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = heighttt(y);
    x->height = heighttt(x);
    return x;
}
struct trainers *leftRotatet(struct trainers *x) // left rotating function for trainer
{
    struct trainers *y = x->right;
    struct trainers *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = heighttt(x);
    y->height = heighttt(y);
    return y;
}
int getBalancem(struct members *N) // gives the difference in height of left side and right side fpr member tree
{
    if (N == NULL)
    {
    return 0;
    }
    else
    {
    return heightmm(N->left)-heightmm(N->right);
	}
}
int getBalancet(struct trainers *N) // gives the difference in height of left and right side of trainer tree
{
    if (N == NULL)
        return 0;
    else
        {
          return heighttt(N->left)-heighttt(N->right);
      }
}

struct members* insertmember(struct members* node, struct members* member1) //function for inserting a node in an avl tree for member list
{
    if(node==NULL)
    {
    return member1;
    }
    if(member1->member_id<node->member_id)
        {
		node->left=insertmember(node->left,member1);
	}
    else if(member1->member_id > node->member_id)
    {
    node->right=insertmember(node->right,member1);
    }
    else
	{ 
        return node;
    }
 
    node->heightm = heightmm(node); //heights might have changed so updating height
 
    
    int balance = getBalancem(node); //we will get the balance and then upon that balance value we go further
 
    // different cases on balance
    if (balance>1&&member1->member_id<node->left->member_id)
    {
        return rightRotatem(node);
    }
    if (balance<-1&&member1->member_id>node->right->member_id)
    {
        return leftRotatem(node);
    }
    if (balance>1&&member1->member_id > node->left->member_id)
    {
        node->left =  leftRotatem(node->left);
        return rightRotatem(node);
    }
 
    
    if (balance<-1&&member1->member_id<node->right->member_id)
    {
        node->right = rightRotatem(node->right);
        return leftRotatem(node);
    }

    return node;
}
struct trainers* inserttrainer(struct trainers* node, struct trainers* trainer1)
{

    if(node==NULL)
    {
	return trainer1;
    }
    if(trainer1->trainer_id<node->trainer_id)
    {
		node->left=inserttrainer(node->left,trainer1);
	}
    else if(trainer1->trainer_id > node->trainer_id)
    {
	node->right=inserttrainer(node->right,trainer1);
    }
    else
	{ 
    return node;
    }
    node->height=heighttt(node);
    int balance=getBalancet(node);
    if (balance>1&&trainer1->trainer_id<node->left->trainer_id)
    {
    return rightRotatet(node);
    }
    if (balance<-1&&trainer1->trainer_id>node->right->trainer_id)
    {
	return leftRotatet(node);
    }
    if(balance>1&&trainer1->trainer_id>node->left->trainer_id)
    {
        node->left=leftRotatet(node->left);
        return rightRotatet(node);
    }
    if(balance<-1&&trainer1->trainer_id<node->right->trainer_id)
    {
        node->right=rightRotatet(node->right);
        return leftRotatet(node);
    }
    return node;
}
void preOrderm(struct members *root) // traversal through the tree in preorder format
{
    if(root != NULL)
    {
        printf("%d ", root->member_id);
        preOrderm(root->left);
        preOrderm(root->right);
    }
}
void preOrdert(struct trainers *root)
{
    if(root != NULL)
    {
        printf("%d ", root->trainer_id);
        preOrdert(root->left);
        preOrdert(root->right);
    }
}
void searchmemberage(struct members *root,int k) //function for searching a function with the age
{
	struct members *m;
	m=root;
	
	
    if(m!= NULL)
    {
        if(m->age==k)
        {
        	printmember(m);
		}
        searchmemberage(m->left,k);
        searchmemberage(m->right,k);
    }
   
}
void searchtrainerrem(struct trainers *root,int k) //searching trainers with remuniration
{
	struct trainers *m;
	m=root;
	
	
    if(m!= NULL)
    {
        if(m->remun==k)
        {
        	printtrainer(m);
		}
        searchtrainerrem(m->left,k);
        searchtrainerrem(m->right,k);
    }
   
}
void searchmembername(struct members* m1,char str[]) //function to search the member with name
{
	if(m1!=NULL)
	{
		if(strcmp(m1->name,str)==0)
		{
			printmember(m1);
		}
		searchmembername(m1->left,str);
		searchmembername(m1->right,str);
	}
}
void searchtrainername(struct trainers* m1,char str[]) //function to search trainer with name
{
	if(m1!=NULL)
	{
		if(strcmp(m1->name,str)==0)
		{
			printtrainer(m1);
		}
		searchtrainername(m1->left,str);
		searchtrainername(m1->right,str);
	}
}
struct members* minValueNodem(struct members* node) //function to find minimum  value node in an avl tree
{
    struct members* temp = node;
    while (temp->left != NULL)
    {
	
        temp = temp->left;
    }
    return temp;
}
 
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct members* deleteNodem(struct members* root, int memberid)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (memberid< root->member_id )
        root->left = deleteNodem(root->left,memberid);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if(memberid>root->member_id )
    {
	
        root->right = deleteNodem(root->right,memberid);
        
    }
    else  //here in this case the member id will be same as given in the input
    {
        if((root->left==NULL)||(root->right==NULL) )
        {     
		      struct members *temp1 = root->left ? root->left : root->right; //ternory operator
            if (temp1==NULL)
            {
            temp1=root;
            root=NULL;
            }
            else 
            {
			*root=*temp1;
		    } 
            free(temp1);
        }
        else
        {
            struct members* temp1=minValueNodem(root->right);
            root->member_id=temp1->member_id;
            root->right=deleteNodem(root->right, temp1->member_id);
        }
    }
    if(root==NULL)
      return root;
 
    //after deletion updation of  heights
    root->heightm=1+max(heightmm(root->left),heightmm(root->right));
    int balance=getBalancem(root);// now we check for balance and if it is not balanced we make it balanced 
    if (balance>1&&getBalancem(root->left)>=0)
    {
	return rightRotatem(root);
    }
    if(balance>1&&getBalancem(root->left)<0)
    {
    root->left=leftRotatem(root->left);
    return rightRotatem(root);
    }
    if(balance<-1&&getBalancem(root->right)<=0)
    {
	return leftRotatem(root);
    }
    if(balance<-1&&getBalancem(root->right)>0)
    {
    root->right = rightRotatem(root->right);
    return leftRotatem(root);
    }
    return root;
}
struct trainers* minValueNodet(struct trainers* node)
{
    struct trainers* temp=node;
    while(temp->left!=NULL)
    {
	temp=temp->left;
    }
    return temp;
}
struct trainers* deleteNodet(struct trainers* root, int trainerid)
{
    
 
    if(root==NULL)
    {
	return root;
    }
    if(trainerid<root->trainer_id )
    {
	root->left=deleteNodet(root->left,trainerid);
    }
    else if(trainerid>root->trainer_id )
    {
    root->right=deleteNodet(root->right,trainerid);   
    }

    else
    {
        if((root->left == NULL)||(root->right == NULL))
        {
            struct trainers *temp1 = root->left ? root->left : root->right;
            if (temp1==NULL)
            {
            temp1=root;
            root=NULL;
            }
            else 
            {
			*root = *temp1;
			} 
			free(temp1);
        }
        else
        {
        struct trainers* temp1 = minValueNodet(root->right);
        root->trainer_id = temp1->trainer_id;
        root->right = deleteNodet(root->right, temp1->trainer_id);
        }
    }
    if (root==NULL)
    {
	return root;
    }
    root->height=1+max(heighttt(root->left),heighttt(root->right));
    int balance=getBalancet(root);
    if (balance>1&&getBalancet(root->left)>= 0)
    {
	return rightRotatet(root);
    }
    if (balance>1&&getBalancet(root->left)<0)
    {
    root->left=leftRotatet(root->left);
    return rightRotatet(root);
    }
    if (balance<-1&&getBalancet(root->right)<=0)
    {
	return leftRotatet(root);
    }
    if (balance<-1&&getBalancet(root->right)>0)
    {
    root->right=rightRotatet(root->right);
    return leftRotatet(root);
    }
    return root;
}
void searchmember(struct members* m1,int k) //function to search member with member id
{   
    struct members* m;
    m=m1;
    int l,stat=1;
    char str[50];
	
		while(m!=NULL&&stat==1)
		{
			if(m->member_id==k)
			{
				printmember(m);
				stat=0;	
			}
			else if(k<m->member_id)
			{
				m=m->left;
			}
			else if(k>m->member_id)
			{
				m=m->right;
			}
		
		if(stat==1)
		{
			printf("\n invalid member id");
		}
	}
	
	
}
void searchtrainer(struct trainers* m1,int k)
{   
    struct trainers* m;
    m=m1;
    int l,stat=1;
    char str[50];
	
		while(m!=NULL&&stat==1)
		{
			if(m->trainer_id==k)
			{
				printtrainer(m);
				stat=0;	
			}
			else if(k<m->trainer_id)
			{
				m=m->left;
			}
			else if(k>m->trainer_id)
			{
				m=m->right;
			}
		
		if(stat==1)
		{
			printf("\n invalid trainer id");
		}
	}
	
	
}
void searchmembergender(struct members* m,char gen[])  //function search a member with gender
{
	if(m!=NULL)
	{
		if(strcmp(m->gender,gen)==0)
		{
			printmember(m);
		}
		searchmembergender(m->left,gen);
		searchmembergender(m->right,gen);
	}
}
void searchmemberprogram(struct members *m,int n) //function to search a member based on the programs he has took
{
	int i;
	 if(m!=NULL)
	 {
	 	for(i=0;i<m->numofprograms;i++)
	 	{
	 		if(m->programs[i]==n)
	 		{
	 			printmember(m);
			 }
		 }
		 searchmemberprogram(m->left,n);
		 searchmemberprogram(m->right,n);
	 }
}
void searchtrainerprogram(struct trainers *m,int n) //function to search trainer based on the programs he teaches
{
	int i;
	 if(m!=NULL)
	 {
	 	for(i=0;i<m->totalprograms;i++)
	 	{
	 		if(m->trainerprograms[i]==n)
	 		{
	 			printtrainer(m);
			 }
		 }
		 searchtrainerprogram(m->left,n);
		 searchtrainerprogram(m->right,n);
	 }
}
void printmemberlist(struct members* m)//function to print list of members
{
	if(m!=NULL)
	{
		printmember(m);
		printmemberlist(m->left);
		printmemberlist(m->right);
	}
}
void printtrainerlist(struct trainers* m)//function to print the list of trainers0
{
	if(m!=NULL)
	{
		printtrainer(m);
		printtrainerlist(m->left);
		printtrainerlist(m->right);
	}
}
void rangemembersearch(struct members* m,int id1,int id2 )
{ 
    int i;
	if(m!=NULL)
	{
		for(i=id1;i<=id2;i++)
		{
			searchmember(m,i);
		}
	}
}

int main()
{
	struct members* m1;
	struct trainers* m2;
	struct members* root;
	struct trainers* root1;
	char str3[50],str4[50];
	root1=NULL;
	root=NULL;
	int l,l1=1,j,l2=1,mid,k1,k2,k3;
	int s=1000,t=2000;
	printf("\n the member list is empty add a member to proceed");
	m1=NULL;
	
	m1=(struct members*)malloc(sizeof(struct members));
	printf("\n  the member id is %d",s);
	m1->member_id=s;
	s++;
	
	printf("\n enter the name ");
	scanf("%s",m1->name);
	printf("\n enter the gender");
	scanf("%s",m1->gender);
	printf("\n enter the age");
	scanf("%d",&m1->age);
	printf("\n enter the num of programs taken by the member");
	scanf("%d",&m1->numofprograms);
	for(j=0;j<m1->numofprograms;j++)
		{
			printf("\n enter 1 for yoga slot \n enter 2 for cardio slot \n enter 3 for zumba slot \n enter 4 for weight lifting slot ");
			scanf("%d",&m1->programs[j]);
			printf("\n enter the fees that has paid for the respective program");
			scanf("%d",&m1->feespaid[j]);
			
		}
		root=insertmember(root,m1);
		printf("\n member added succesfully");
	printf("\n the trainer list is empty add a trainer to proceed");
	
	m2=NULL;
	
	m2=(struct trainers*)malloc(sizeof(struct trainers));
	printf("\n the trainer id is %d",t);
	m2->trainer_id=t;
	t++;
	printf("\n enter the name of the trainer ");
	scanf("%s",m2->name);
	printf("\n enter the num of programs trainer can train");
	scanf("%d",&m2->totalprograms);
	for(j=0;j<m2->totalprograms;j++)
		{
			printf("\n enter 1 for yoga slot \n enter 2 for cardio slot \n enter 3 for zumba slot \n enter 4 for weight lifting slot ");
			scanf("%d",&m2->trainerprograms[j]);
			
			
		}
		printf("\n enter the remuniration");
			scanf("%d",&m2->remun);
		root1=inserttrainer(root1,m2);
		printf("\n trainer added succesfully");
		int n=0;
	
    while(n!=10)
    {
	
	printf("\n input  1 for adding a member");
	printf("\n input 2 for adding a trainer");
	printf("\n input 3 for deleting a member");
	printf("\n input 4 for deleting a trainer");
	printf("\n input 5 for search a member");
	printf("\n input 6 for search a trainer");
	printf("\n input 7 for print the member list");
	printf("\n input 8 for print the trainer list");
	printf("\n input 9 for range member search");
	printf("\n input 10 for ending the session");
    scanf("%d",&n);
    if(n==1)
    {  
    l1=1;
    	while(l1!=2)
	{ 
	printf("\n enter the value 1 for adding a node into an avl tree and 2 for stopping the process");
    scanf("%d",&l);
    
    
    if(l==1)
	{
	 l1=1;
	m1=NULL;
	
	m1=(struct members*)malloc(sizeof(struct members));
	printf("\n the member id is %d",s);
	m1->member_id=s;
	s++;
	
	printf("\n enter the name ");
	scanf("%s",m1->name);
	printf("\n enter the gender");
	scanf("%s",m1->gender);
	printf("\n enter the age");
	scanf("%d",&m1->age);
	printf("\n enter the num of programs taken by the member");
	scanf("%d",&m1->numofprograms);
	for(j=0;j<m1->numofprograms;j++)
		{
			printf("\n enter 1 for yoga slot \n enter 2 for cardio slot \n enter 3 for zumba slot \n enter 4 for weight lifting slot ");
			scanf("%d",&m1->programs[j]);
			printf("\n enter the fees that has paid for the respective program");
			scanf("%d",&m1->feespaid[j]);
			
		}
		root=insertmember(root,m1);
		printf("\n member added succesfully");
	}
	else if(l==2)
	{
		l1=2;
	}
}
	}
  else if(n==2)
  { l2=1;
  	while(l2!=2)
	{ 
	printf("\n enter the  value 1 for adding a node into an avl tree and 2 for stopping the process");
    scanf("%d",&l);
    if(l==1)
	{
	 l1=1;
	m2=NULL;
	m2=(struct trainers*)malloc(sizeof(struct trainers));
	printf("\n the trainer id is %d",t);
	m2->trainer_id=t;
	t++;
	printf("\n enter the name of the trainer ");
	scanf("%s",m2->name);
	printf("\n enter the num of programs trainer can train");
	scanf("%d",&m2->totalprograms);
	for(j=0;j<m2->totalprograms;j++)
		{
			printf("\n enter 1 for yoga slot \n enter 2 for cardio slot \n enter 3 for zumba slot \n enter 4 for weight lifting slot ");
			scanf("%d",&m2->trainerprograms[j]);
			
			
		}
		printf("\n enter the remuniration");
			scanf("%d",&m2->remun);
		root1=inserttrainer(root1,m2);
		printf("\n member added succesfully");
	}
	else if(l==2)
	{
		l2=2;
	}
}
  }
  else if(n==3)
  {
  	printf("\n enter the member id of the node to be deleated");
  	scanf("%d",&mid);
  	root=deleteNodem(root,mid);
  }
  else if(n==4)
  {
  	printf("\n enter the trainer id of the node to be deleated");
  	scanf("%d",&mid);
  	root1=deleteNodet(root1,mid);
  }
  else if(n==5)
  {
  	 printf("\n enter 1 to search with member id \n enter 2 to search with age \n enter 3 to search with name \n enter 4 to search with gender \n enter 5 to search with programs taken");
		         scanf("%d",&k1);
		         if(k1==1)
		         {  
		         printf("\n enter the member id of the member to be searched");
		         scanf("%d",&k2);
		         	searchmember(root,k2);
				 }
				 else if(k1==2)
				 {
				 	printf("\n enter the age of the member to be searched ");
				 	scanf("%d",&k2);
				 	searchmemberage(root,k2);
				 }
				 else if(k1==3)
				 {
				 	printf("\n enter the name of the member to be searched");
				 	scanf("%s",str3);
				 	searchmembername(root,str3);
				 }
				 else if(k1==4)
				 {
				 	printf("\n enter the gender of the members to be searched");
				 	scanf("%s",str3);
				 	searchmembergender(root,str3);
				 }
				 else if(k1==5)
				 {
				 	printf("\n enter 1 for searching members who took yoga ");
		            printf("\n enter 2 for searching members who took cardio");
	             	printf("\n enter 3 for searching members who took zumba ");
		            printf("\n enter 4 for searching members who took weight lifting");
		            scanf("%d",&k3);
		            searchmemberprogram(root,k3);
				 }
  }
  else if(n==6)
  {
  	printf("\n enter 1 to search with trainers id \n enter 2 to search with name of the trainer \n enter 3 to search with programs they train");
		         scanf("%d",&k1);
		         if(k1==1)
		         {
		         	printf("\n enter the trainer id of the trainer to be searched");
		         	scanf("%d",&k2);
		         	searchtrainer(root1,k2);
		         	
				 }
				 else if(k1==2)
				 {
				 	printf("\n enter the trainer name to be searched ");
				 	scanf("%s",str3);
				 	searchtrainername(root1,str3);
				 }
				 else if(k1==3)
				 {
				 	printf("\n enter 1 for searching trainers who trains yoga ");
		            printf("\n enter 2 for searching trainers who trains cardio");
		            printf("\n enter 3 for searching trainers who trains zumba ");
		            printf("\n enter 4 for searching trainers who trains weight lifting");
		            scanf("%d",&k3);
		            searchtrainerprogram(root1,k3);
				 }
  }
  else if(n==7)
  { 
  if(root==NULL)
  {
  	printf("\n the member list is empty ");
  }
  else
  {
  printmemberlist(root);
  }
  }
  else if(n==8)
  {
  	if(root1==NULL)
  	{
  		printf("\n the trainer list is empty");
	  }
	  else
	  {
	  
  	printtrainerlist(root1);
  }
  }
  else if(n==9)
{
	printf("\n enter the initial range of the member ids to be searched");
	scanf("%d",&k1);
	printf("\n enter the final range of the member ids to be searched ");
	scanf("%d",&k2);
	rangemembersearch(root,k1,k2);
}
else if(n==10)
{
	printf("\n session expired");
}
}

}
  
  
	
	