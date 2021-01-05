 #include<stdio.h>
 #define size 6
struct station{
	float skyviewfactor;
	float vegitationdensityratio;
	float populationdensity;
	int pervioussurfacefraction;
	int impervioussurfacefraction;
	char stationstatus[6];
	int distance[size];	
	float temp[3];
};
int main()
{
	int i,j,k=0,t=0,s=0,maxcount;
	int count[size];
	int m[size] = {0};
	float avgtemp,sum=0;
	struct station city[size]; 
for(i=0;i<size;i++)
{
for(j=0;j<3;j++){
printf("enter the temp of %d station on day %d:-\n",i,j);
	scanf("%f",&city[i].temp[j]);
		sum+=city[i].temp[j];
}
}
//*finding avg temp*//
avgtemp=(sum*1.0)/(3*size);
for(i=0;i<size;i++){
	for(j=0;j<3;j++){
		if(city[i].temp[j]>avgtemp)
			k++;
		}
		count[i]=k;
		k=0;
		}
		//*maximum count is found*//
	maxcount=count[0];
	for(i=1;i<size;i++){
		if(count[i]>=maxcount){
			maxcount=count[i];
			}
		}
	for(i=0;i<size;i++){
		if(count[i]==maxcount)
	printf("the stations with highest heat degree days are %d:-\n",i);
	}
}
