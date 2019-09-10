#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int a[500002],b[500002];
long long msortmain(int begin,int mid,int end){
    long long cnt=0;
    int front=begin,middle=mid+1,times=0;
    while(front!=mid+1&&middle!=end+1){
        if(a[front]>a[middle]){
            cnt+=mid-front+1;
            b[times++]=a[middle++];
        }
        else{
            b[times++]=a[front++];
        }
    }
    while(front!=mid+1)b[times++]=a[front++];
    while(middle!=end+1)b[times]=b[middle++];
    for(int i=0;i<times;i++)a[begin+i]=b[i];
    return cnt;
}
long long msort(int begin,int end){
    long long cnt=0;
    if(begin<end){
        int mid=(begin+end)/2;
        cnt+=msort(begin,mid);
        cnt+=msort(mid+1,end);
        cnt+=msortmain(begin,mid,end);
    }
    return cnt;
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	cin>>a[i];
    }
    long long cnt=msort(0,n-1);
    for(int i=0;i<n;i++){
    	cout << a[i] << ' ';
    }
    return 0;
}