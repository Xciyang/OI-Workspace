#include <iostream>
using namespace std;
int f[51][51];
int main(){
    int n,y,x;
    //人数、最后一列人数(有人但未坐满）、坐了人的列数
    cin>>n;
    if(n>=3)f[3][2]=1;//那个最特别的位置
    if(n<4)y=n,x=1;//特判<4的情况
    else {
        n-=4;
        x=n/3+2;
        y=n%3;
    }
//  cout<<n<<endl;
//  cout<<x<<endl<<y<<endl;
    for(int i=1;i<=4;i++)
        for(int j=1;j<x;j++){//中间部分标记，1有人，0没人
            if(i==3)break;
            f[i][2*j]=1;
        }
    for(int i=1;i<=y;i++)f[i][x*2]=1;//有人但未坐满的最后一列
    cout<<"+------------------------+\n";
    for(int i=1;i<=4;i++){
        for(int j=1;j<=26;j++){
            if(i==1&&j==25)cout<<"D";//司机
            else if(i==2&&j==25)cout<<".";//
            else if(i==4&&j==25)cout<<".";//几个特殊的点
            else if(i==3&&j==24)cout<<".";//
            else if(j==1||j==24||j==26)cout<<"|";//
            else if(j%2==1&&j<=23)cout<<".";//列数为奇数的基本上是“.”
            else{//座位
                if(i==3&&j!=2)cout<<".";//特殊位子
                else if(f[i][j]==1)cout<<"O";
                else cout<<"#";
            }
        }
        if(i==1||i==4)cout<<")";//车灯（应该是吧）
        cout<<endl;
    }
    cout<<"+------------------------+\n";
}