#include<stdio.h>
struct station{
float populationdensity;
float temp[3];
int numberofstation;
float maxtemp;
};
void structuresort(struct station city[],int n,int y)
{
    struct station replace;
    struct station restore[n];
    int i,j,min,p;
    //*temporary structure restore is used*//
    for(i=0;i<n;i++)
    {
        restore[i]=city[i];
    }
    //*sorting in order of minimum population density*//
    for(i=0;i<y;i++)
    {
        min=restore[i].populationdensity;
        p=i;
    for(j=i+1;j<n;j++)
        {
        if(min>restore[j].populationdensity)
            {
                min=restore[j].populationdensity;
                p=j;
            }
        else if(min==restore[j].populationdensity)
            {
            if(restore[j].maxtemp>restore[p].maxtemp)
                {
                 	min=restore[j].populationdensity;	
                    p=j;
                }
            }
        }
        //*swapping values*//
        replace=restore[i];
        restore[i]=restore[p];
        restore[p]=replace;
    }
    printf("The top %d stations with minimum population density with highest max.temperature are as follows in order:-\n",y);
    for(i=0;i<y;i++)
    {
        printf("Station %d\n",restore[i].numberofstation);

    }
}
int main(){
		int size,k,i,j;
		printf("enter the no. of stations:-\n");
		scanf("%d",&size);
struct station city[size];
	printf("enter the value of k:\n");
		scanf("%d",&k);
for(i=0;i<size;i++)
{
printf("enter the populationdensity and station no.:-\n");
scanf("%f",&city[i].populationdensity);
scanf("%d",&city[i].numberofstation);
for(j=0;j<3;j++){
	printf("enter the temp of station %d on day %d:-\n",i,j);
	scanf("%f",&city[i].temp[j]);
}
}
//*assigning random value to compare*//
for(i=0;i<size;i++){
	city[i].maxtemp=city[i].temp[0];
}
//*finding max temperature of every city*//
for(i=0;i<size;i++){
	for(j=1;j<3;j++){
	if(city[i].temp[j]>city[i].maxtemp)
	{
		city[i].maxtemp=city[i].temp[j];
	}
}
}
//*calling sorting function*//
structuresort(city,size,k);
}
