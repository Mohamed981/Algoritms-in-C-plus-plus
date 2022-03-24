#include <bits/stdc++.h>
#include<stdio.h>
using namespace std;

int main() {

string s1="bdcaba",s2="abcbdab",s="";
vector<vector<int>>v(s2.length()+1,vector<int>(s1.length()+1,false));

for(int i=1;i<=s2.length();i++){
    for(int j=1;j<=s1.length();j++){
        if(s1[j-1]==s2[i-1]){
            v[i][j]=v[i-1][j-1]+1;
        }
        else{
            v[i][j]=max(v[i-1][j],v[i][j-1]);
        }
    }
}


int j=v[0].size()-1,i=v.size()-1;
while(i!=0&&j!=0){
    if(v[i][j]!=v[i-1][j]&&v[i-1][j]==v[i][j-1]){
                s+=s1[j-1];
                j=j-1;
                i=i-1;
            continue;
        }
        if(v[i-1][j]==v[i][j])
            i--;
        else
            j--;
}
reverse(s.begin(),s.end());

cout<<s<<endl;

int w=5;
vector<vector<int>>matrix{{2,3},{3,4},{4,5},{5,6}};
vector<vector<int>> sack(matrix.size()+1,vector<int>(w+1,false));

for(int i=1;i<sack.size();i++){
    for(int j=1;j<sack[0].size();j++){
        if(matrix[i-1][0]>j)
            sack[i][j]=sack[i-1][j];
        else{
            sack[i][j]=max(sack[i-1][j],sack[i-1][j-matrix[i-1][0]]+matrix[i-1][1]);
        }
    }
}
j=sack[0].size()-1;
i=sack.size()-1;
vector<int> ss;
while(i!=0&&j!=0){
    if(sack[i][j]!=sack[i-1][j]){
                ss.push_back(matrix[i-1][0]);
                j=j-matrix[i-1][0];
                i-=1;
            continue;
        }
            i--;

}
cout<<ss[0]<<" "<<ss[1];
    return 0;
}
