#include <stdio.h>
void print(int f[], int n){
for(int i=0;i<n;i++) printf(f[i]==-1?" - ":" %d ",f[i]);
printf("\n");
}

int main(){
int n,m;
printf("Enter no. of pages: ");
scanf("%d",&n);
int ref[n];
printf("Enter reference string: ");
for(int i=0;i<n;i++) scanf("%d",&ref[i]);
printf("Enter frame size: ");
scanf("%d",&m);
if(m<3){ printf("Min 3 frames!\n"); return 0; }

int f[m],pf=0,next=0;
for(int i=0;i<m;i++) f[i]=-1;

printf("\nFIFO Page Replacement:\n");
for(int i=0;i<n;i++){
int found=0;
for(int j=0;j<m;j++) if(f[j]==ref[i]){found=1;break;}
if(!found){ f[next]=ref[i]; next=(next+1)%m; pf++; }
print(f,m);
}
printf("Total Page Faults: %d\n",pf);
return 0;
}
