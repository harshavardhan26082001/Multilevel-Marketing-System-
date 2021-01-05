#include<stdio.h>
struct station{
	int numberofstation;
	float vegitationdensityratio;
	float temp[30];
};
void structuresort(struct station city[],int y,int n,float avgtemp)
{
    struct station duplicate;
    struct station restore[n];
    int i,j,min,p;
    //*temporary structure restore is used*//
    for(i=0;i<n;i++)
    {
        restore[i]=city[i];
    }
    for(i=0;i<y;i++)
    {
        min=restore[i].vegitationdensityratio;
        p=i;
        for(j=i+1;j<n;j++)
        {
            if(min>restore[j].vegitationdensityratio)
            {
                min=restore[j].vegitationdensityratio;
                p=j;
            }

        }
        //*swapping values*//
        duplicate=restore[i];
        restore[i]=restore[p];
        restore[p]=duplicate;
    }
        for(i=0;i<n;i++){
        	printf("the dates for station %d are:\n",i);
        	for(j=0;j<3;j++){
        			if(city[i].temp[j] > avgtemp)
		{
			printf("%d\t",j);
	}

			}
    }
}
int main(){
	int i,j,size,t=0;
	float avgtemp,sum=0;
	printf("enter the no. of stations:-\n");
	scanf("%d",&size);
	struct station city[size];
for(i=0;i<size;i++)
{
printf("enter the vegetation density ratio and no. of station-%d:-\n",i);
scanf("%f",&city[i].vegitationdensityratio);
scanf("%d",&city[i].numberofstation);
for(j=0;j<3;j++){
	printf("enter the temp of station %d on day %d:-\n",i,j);
scanf("%f",&city[i].temp[j]);
}
}
	for(i=0;i<size;i++)
	{
	for(j=0;j<3;j++){
	sum+=city[i].temp[j];
	}
}
//*calculating avgerage temperature*//
avgtemp=(sum*1.0)/(3*size);
//*sorting stations with decreasing vegitation density ratio*//
//*calling function*//
structuresort(city,size,size,avgtemp);
}
