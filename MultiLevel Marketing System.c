#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#define lower 1000
#define higher 2000

typedef struct IBO_node_tag{
	int iboid;
	int mentor_score;
	int sale_score;
	int totalscore;
	int descandants;
	struct IBO_node_tag *left;
	struct IBO_node_tag *middle;
	struct IBO_node_tag *right;
}IBO_node;

struct Queue{
	int front ,rear,size;
	unsigned capacity;
	IBO_node **array;
};

IBO_node *new_node(int score){
	IBO_node *temp=(IBO_node*)malloc(sizeof(IBO_node));
	temp->iboid=(rand()%(higher-lower+1))+lower;
	temp->sale_score=score;
	temp->mentor_score=0;
	temp->left=temp->middle=temp->right=NULL;
	return temp;
}

insert_IBO(int iboscore ,int id,IBO_node *mentor){
	IBO_node *temp=new_node(iboscore);
	if(mentor!=NULL){
		if(mentor->iboid == id){
			if(mentor->left == NULL){
				mentor->left=temp;
				mentor->mentor_score=100;
				printf("A new ibo is creted under the mentor with id-%d\n",temp->iboid);
			}
			else if(mentor->middle == NULL){
				mentor->middle=temp;
				mentor->mentor_score=200;
				printf("A new ibo is creted under the mentor with id-%d\n",temp->iboid);
			}
			else if(mentor->right==NULL){
				mentor->right=temp;
				mentor->mentor_score=400;
				printf("A new ibo is creted under the mentor with id-%d\n",temp->iboid);
				}
				else
				printf("not possible");
		}
		else{
			insert_IBO(iboscore,id,mentor->left);
			insert_IBO(iboscore,id,mentor->middle);
			insert_IBO(iboscore,id,mentor->right);
		}

	}
}

void update_mentorscore(IBO_node *mentor){
	if(mentor != NULL){
		mentor->mentor_score+=10*(nodes_underit(mentor)-1)+0.5*(salescore_underit(mentor));
		mentor->descandants=(nodes_underit(mentor)-1);
		mentor->totalscore = mentor->mentor_score + mentor->sale_score;
		update_mentorscore(mentor->left);
		update_mentorscore(mentor->middle);
		update_mentorscore(mentor->right);
	}
}


int nodes_underit(IBO_node *mentor){
	if(mentor == NULL){
		return 0;
	}
	else
	return 1+nodes_underit(mentor->left)+nodes_underit(mentor->middle)+nodes_underit(mentor->right);
	}

int salescore_underit(IBO_node *mentor){
		int ret_val=0;
	if(mentor == NULL)
	ret_val = 0;
	else{
		if(mentor->left != NULL)
		ret_val+=mentor->left->sale_score;
		if(mentor->middle != NULL)
		ret_val+=mentor->middle->sale_score;
		if(mentor->right != NULL)
		ret_val+=mentor->right->sale_score;
	}
	return ret_val;
}

void print_sale(IBO_node *mentor){
	if(mentor!=NULL){
	printf("sale score of ibo is:-%d\n",mentor->sale_score);
	printf("mentor score of ibo is:-%d\n",mentor->mentor_score);
	printf("id of ibo is:-%d\n",mentor->iboid);
	print_sale(mentor->left);
	print_sale(mentor->middle);
	print_sale(mentor->right);
}
}


int height(IBO_node *node){
	if(node == NULL)
	return 0;
	else{
		int lheight=height(node->left);
		int mheight=height(node->middle);
		int rheight=height(node->right);
		if(lheight >= mheight){
			if(lheight >= rheight)
			return (lheight+1);
			else
			return(rheight+1);
		}
		else{
			if(mheight >= rheight)
			return (mheight+1);
			else
			return (rheight+1);
		}
	}
}


struct Queue* createQueue(unsigned capacity){
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->capacity = capacity;
	queue->front=queue->size=0;
	queue->rear = capacity-1;
	queue->array = (IBO_node*)malloc(sizeof(IBO_node));
	return queue;
}

void push(struct Queue* queue,IBO_node *root){
	if(isFull(queue))
	return;
	queue->rear=(queue->rear+1)%queue->capacity;
	queue->array[queue->rear] = root;
	queue->size +=1;
}

IBO_node *pop(struct Queue* queue){
	if(isQueueempty(queue))
	return;
	IBO_node *item = queue->array[queue->front];
	queue->front = (queue->front+1)%queue->capacity;
	queue->size -=1;
	return item;
}

int isQueueempty(struct Queue *queue){
	return (queue->size == 0);
}

int isFull(struct Queue* queue){
	return (queue->size == queue->capacity);
}

void display_max(IBO_node *mentor,int a){
	int count;int level=0;
	int h = height(mentor);
	IBO_node *p,*max_node;int max;
	max_node->totalscore=0;
	struct Queue* queue;
	queue = createQueue(1000);
		push(queue,mentor);
	while(queue->size != 0 && level <= h){
		count=queue->size;
		while(count != 0){
			p = pop(queue);
			if( p->totalscore >= max){
			max_node = p;
			max=p->totalscore;
		}
			count-=1;
			if(p->left != NULL)
			push(queue,p->left);
			if(p->middle != NULL)
			push(queue,p->middle);
			if(p->right != NULL)
			push(queue,p->right);
		}
		printf("The ibo having maximum score in level-%d is id-(%d)\n",level,max_node->iboid);
		level++;
		max = 0;
	}
	mentor->totalscore=a;
}


void max_descendants(IBO_node *mentor){
	int count;int level=0;int max=0;
	int h=height(mentor);
	IBO_node *p,*max_node;
	struct Queue* queue;
	queue=createQueue(500);
	push(queue,mentor);
	while(queue->size != 0 && level <= h){
		count=queue->size;
		while(count!=0){
			p=pop(queue);
			if(p->descandants >= max){
				max_node = p;
				max = p->descandants;
			}
			count-=1;
			if(p->left != NULL)
			push(queue,p->left);
			if(p->middle != NULL)
			push(queue,p->middle);
			if(p->right != NULL)
			push(queue,p->right);
		}
		printf("The ibo having maximum no.of descandants in level-%d is id-(%d)\n",level,max_node->iboid);
		level++;
		max = 0;
	}
}

void find_ibo(IBO_node *mentor){
	if(mentor != NULL){
		if(mentor->left != NULL && mentor->totalscore < mentor->left->totalscore){
			printf("The ibo having id-(%d) is having more points than his mentor\n",mentor->left->iboid);
		}
		if(mentor->middle != NULL && mentor->totalscore < mentor->middle->totalscore){
			printf("The ibo having id-(%d) is having more points than his mentor\n",mentor->middle->iboid);
		}
		if(mentor->right != NULL && mentor->totalscore < mentor->right->totalscore){
			printf("The ibo having id-(%d) is having more points than his mentor\n",mentor->right->iboid);
		}
		find_ibo(mentor->left);
		find_ibo(mentor->middle);
		find_ibo(mentor->right);
	}
}


IBO_node *traverse_tree(IBO_node *mentor,int id){
 if(mentor != NULL){
  if(((mentor->left != NULL) && ( mentor->left->iboid == id))||((mentor->middle != NULL) && (mentor->middle->iboid == id ))|| ((mentor->right != NULL) && (mentor->right->iboid == id))){
			return mentor;
		}
		else if(mentor == NULL){
		return NULL;
	}
		else{
			if(traverse_tree(mentor->left,id) != NULL)
			return traverse_tree(mentor->left,id);
			if(traverse_tree(mentor->middle,id) != NULL)
			return traverse_tree(mentor->middle,id);
			if(traverse_tree(mentor->right,id) != NULL)
			return traverse_tree(mentor->right,id);
		}
	}
}


IBO_node *delete_ibo(IBO_node *mentor1,int id){
	IBO_node *temp,*p,*q,*ret_val;
	if(mentor1->iboid == id){
		p = mentor1;
		if(mentor1->right == NULL){
			if(mentor1->middle == NULL){
				if(mentor1->left == NULL)
				ret_val = NULL;
				else
				ret_val = mentor1->left;
			}
			else{
				if(p->left->right == NULL){
					if(p->left->middle == NULL){
						if(p->left->left == NULL){
							p->left->left = p->middle;
							ret_val = p->left;
						}
						else{
							p->left->middle = p->middle;
							ret_val = p->left;
						}
					}
					else{
						p->left->right = p->middle;
						ret_val = p->left;
					}
				}
				else{
					if(p->middle->right == NULL){
						if(p->middle->middle == NULL){
							if(p->middle->left == NULL){
								p->middle->left = p->left;
								ret_val = p->middle;
							}
							else{
								p->middle->middle = p->left;
								ret_val = p->middle;
							}
						}
						else{
							p->middle->right = p->left;
							ret_val = p->middle;
						}
					}
				}
			}
		}
		else if(mentor1->right != NULL && mentor1->middle != NULL && mentor1->left != NULL){
			printf("Not possible\n");
			ret_val = mentor1;
		}
		else{
			if(p->left->right == NULL){
				if(p->left->middle==NULL){
					if(p->left->left==NULL){
						p->left->left=p->middle;
						p->left->middle=p->right;
						ret_val = p->left;
					}
					else{
						p->left->middle=p->middle;
						p->left->right = p->right;
						ret_val = p->left;
					}
				}
				else{
					printf("Not Possible\n");
					ret_val = mentor1;
				}
			}
			if(p->middle->right == NULL){
				if(p->middle->middle==NULL){
					if(p->middle->left==NULL){
						p->middle->left=p->left;
						p->middle->middle=p->right;
						ret_val = p->middle;
					}
					else{
						p->middle->middle=p->left;
						p->middle->right = p->right;
						ret_val = p->middle;
					}
				}
				else{
					printf("Not Possible\n");
					ret_val = mentor1;
				}
			}
			if(p->right->right == NULL){
				if(p->right->middle==NULL){
					if(p->right->left==NULL){
						p->right->left=p->left;
						p->right->middle=p->middle;
						ret_val = p->right;
					}
					else{
						p->right->middle=p->left;
						p->right->right = p->middle;
						ret_val = p->right;
					}
				}
				else{
					printf("Not Possible\n");
					ret_val = mentor1;
				}
			}
			else{
				printf("Not Possible\n");
				ret_val = mentor1;
			}
		}
	}
	else{
	temp=traverse_tree(mentor1,id);
	q=temp;
			if(temp->left != NULL && temp->left->iboid == id){
				if(temp->right == NULL){
					if(temp->middle == NULL){
							temp->left=q->left->left;
							temp->middle=q->left->middle;
							temp->right=q->left->right;
						}
					else{
						if(temp->left->right != NULL){
							printf("Not possible\n");
							ret_val = mentor1;
						}
						else{
							 if(temp->left->middle != NULL){
							temp->left=temp->left->left;
							temp->right=q->left->middle;
						}
						}
					}
				}
				else{
					if(temp->left->middle==NULL && temp->left->right==NULL){
						temp->left=temp->left->left;
					}
					else{
						printf("Not possible\n");
						ret_val = mentor1;
					}
				}
			}
			else if(temp->middle !=NULL && temp->middle->iboid == id){
				if(temp->middle->right != NULL){
					printf("Not possible\n");
					ret_val = mentor1;
				}
				if(temp->right == NULL){
					if(temp->middle->middle != NULL){
						temp->middle = q->middle->left;
						temp->right = q->middle->middle;
					}
					else{
						 if(temp->middle->left != NULL)
						temp->middle=temp->middle->left;
					}
				}
				else{
					if(temp->middle->middle==NULL && temp->middle->right==NULL)
					temp->middle=temp->middle->left;
					else{
						printf("Not possible\n");
						ret_val = mentor1;
					}
				}
			}
			else if(temp->right != NULL && temp->right->iboid == id){
				if(temp->right->middle==NULL && temp->right->right==NULL){
					temp->right = temp->right->left;
				}
				else{
					printf("Not possible\n");
					ret_val = mentor1;
				}
			}
			ret_val = mentor1;
		}
	return ret_val;
}


int main(){
	IBO_node *mentor,*ibo,*mentor1;int count=0;int a;
	int i,j,ID,score;char flag[]="yes";
	printf("enter the sale-score of mentor:-\n");
	scanf("%d",&score);
	mentor=new_node(score);
	printf("mentor id is:-%d\n",mentor->iboid);
	printf("enter how many nodes you want to add:-");
	scanf("%d",&i);
	FILE *IBO_details;
	IBO_details=fopen("dspd2.txt","r");
		for(j=0;j<i;j++){
			fscanf(IBO_details,"%d",&score);
			ibo=new_node(score);
		printf("do you want to insert the node(yes/no)\n");
		scanf("%s",flag);
		if(strcmp(flag,"no")==0)
		break;
		else if(strcmp(flag,"yes")==0){
			printf("enter the mentor-id under which you want to add the new ibo:-\n");
			scanf("%d",&ID);
			insert_IBO(ibo->sale_score,ID,mentor);
		}
	}
	fclose(IBO_details);
	update_mentorscore(mentor);
	print_sale(mentor);
	a=mentor->totalscore=mentor->mentor_score+mentor->sale_score;
	display_max(mentor,a);
	max_descendants(mentor);
	find_ibo(mentor);
	char flag1[]="yes";mentor1 = mentor;
	while(strcmp(flag1,"yes")==0){
	printf("Do you want to delete the node(yes/no)\n");
	scanf("%s",flag);
		if(strcmp(flag,"no")==0)
		break;
		else if(strcmp(flag,"yes")==0){
		printf("enter the mentor-id which you want to delete:-\n");
		scanf("%d",&ID);
		mentor1 = delete_ibo(mentor1,ID);
		if(mentor1 == NULL)
		printf("Tree is NULL\n");
		else{
		update_mentorscore(mentor1);
		print_sale(mentor1);
		}
		printf("Do u again want to delete the node(yes/no):-\n");
		scanf("%s",flag1);
	}
}
return 0;
}
