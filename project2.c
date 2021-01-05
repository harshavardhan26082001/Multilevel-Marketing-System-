#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define size 3
struct station{
	char stationstatus[5];
	int distance[size];
	float temp[3];	
};
int main()
{
	struct station city[size];
	int i,j,u,r=-1,mindist,t=0;
	float tempdiff,mintempdiff;
for(i=0;i<size;i++){
	printf("enter the status of station %d:-\n",i);
	scanf("%s",&city[i].stationstatus);
	for(j=0;j<3;j++){
		printf("enter the temp of station %d on day %d:-\n",i,j);
		scanf("%f",&city[i].temp[j]);
	}
	for(j=0;j<size;j++){
		printf("enter the distance of station %d to station %d:-\n",i,j);
		scanf("%d",&city[i].distance[j]);
}
}
//*for curret urban station finding nearest rural station*//
printf("enter the index of current station:-\n");
scanf("%d",&u);
mindist=10000;
for(i=0;i<size;i++){
	if(strcmp(city[i].stationstatus,"rural")==0 && abs(city[u].distance[i])<mindist){
		mindist=city[u].distance[i];
		r=i;
	}
}
//*finding minimum temperature difference*//
mintempdiff=fabs(city[u].temp[0]-city[r].temp[0]);
	for(i=1;i<3;i++){
			if(fabs(city[u].temp[i]-city[r].temp[i])<mintempdiff){
				mintempdiff=fabs(city[u].temp[i]-city[r].temp[i]);
		}
}	
for(i=0;i<3;i++){
	if(r==-1){
		printf("there is no rural station\n");
	}
	else if(mintempdiff==fabs(city[u].temp[i]-city[r].temp[i])){
		printf("required thermally comfortable day is %d:-\n",i);
	} 	
}						
}
