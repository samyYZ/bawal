#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, dir, disk, i;
    printf("Requests: "); scanf("%d",&n);
    int r[n];
    for(i=0;i<n;i++) scanf("%d",&r[i]);
    printf("Head, DiskSize, Dir(1=up,0=down): ");
    scanf("%d%d%d",&head,&disk,&dir);

    for(i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(r[i]>r[j]){int t=r[i];r[i]=r[j];r[j]=t;}

    int move=0;
    if(dir==1){
        for(i=0;i<n&&r[i]<head;i++);
        for(;i<n;i++){move+=abs(head-r[i]);head=r[i];}
        move+=abs(head-(disk-1)); head=disk-1;
        for(i--;i>=0;i--){move+=abs(head-r[i]);head=r[i];}
    }
    else{
        for(i=n-1;i>=0&&r[i]>head;i--);
        for(;i>=0;i--){move+=abs(head-r[i]);head=r[i];}
    }
    printf("Total Movement: %d\n",move);
}

