#include<stdio.h>
#define size 3
struct station{
	int pervioussurfacefraction;
	int distance[size];
	char stationstatus[5];
	float temp[30];
};
int main(){
	int i,j,k=0,l=0,m=0,mindist,maxpervioussf;
	float avgtemp[size];char urban[6]="urban";char rural[6]="rural";
	struct station city[size];int u[size],r[size],ui[size];
for(i=0;i<size;i++){

printf("enter the pervioussf and station status of station-%d:-\n",i);
scanf("%d %s",&city[i].pervioussurfacefraction,&city[i].stationstatus);
for(j=0;j<size;j++){
	printf("enter the distance of %dth station from %dth station:-\n",i,j);
	scanf("%d",&city[i].distance[j]);
}
for(j=0;j<4;j++){
	printf("enter the temp of station %d on day %d:-\n",i,j);
	scanf("%f",&city[i].temp[j]);
}
}
//*counting number of rural stations*//
for(i=0;i<size;i++){
	if(strcmp(city[i].stationstatus,"rural")==0){
	u[l]=i;
	l++;
}
//**counting number of urban stations*//
else{
ui[k]=i;
k++;
}
}
//*assigning random value for comparison *//
for(i=0;i<size;i++){
	avgtemp[i]=0;
}
mindist=10000;
maxpervioussf=-1;
//*finding nearest rural station and assigning max pervoius sf to that city's pervious sf value*//
for(i=0;i<size;i++){
	for(j=1;j<l;j++){
	if(strcmp(city[i].stationstatus,"urban")==0 && abs(city[u[j]].distance[i])<mindist){
		mindist=city[u[j]].distance[i];
		maxpervioussf=city[u[j]].pervioussurfacefraction;
		//*storing indexes of urban station in array*//
		r[m]=u[j];
		m++;
	}
	//*if the distance is equal*//
	else if( strcmp(city[i].stationstatus,"urban")==0 && (city[u[j]].distance[i]) == mindist){
		if(city[u[j]].pervioussurfacefraction > maxpervioussf){
			maxpervioussf=city[u[j]].pervioussurfacefraction;
			r[m]=u[j];
			m++;
		}
	}
}
}
//*finding heat island intensities*//
for(i=0;i<k;i++){
	for(j=0;j<4;j++){
		avgtemp[ui[i]]+=city[ui[i]].temp[j];
		avgtemp[r[i]]+=city[r[i]].temp[j];
		}
		avgtemp[ui[i]]/=4;
		avgtemp[r[i]]/=4;
		printf("The heat island intensity of %d station is %f:-\n",ui[i],avgtemp[ui[i]]-avgtemp[r[i]]);
}
}
