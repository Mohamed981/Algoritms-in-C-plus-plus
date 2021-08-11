#include <bits/stdc++.h>

using namespace std;

bool sortcol( const vector<int>& v1,
               const vector<int>& v2 ) {
 return v1[1] < v2[1];
}

bool canbestacked(vector<int>& top,vector<int>& bottom){
    if (top[0]<bottom[0] && top[1]<bottom[1])
        return 1;
    return 0;

}
int main()
{
    //Boxes
    vector<vector<int>> vect{{1,5,4},{1,2,2},{2,3,2},{2,4,1},{3,6,2},{4,5,3}};
    //Sorting according to length
    sort(vect.begin(), vect.end(),sortcol);
    vector<int> heights;
    //Storing heights of each box
    for (int i=0; i<vect.size(); i++)
    {
        heights.push_back(vect[i][2]);
    }
    
    int maximum=0;
    for(int i=1;i<vect.size();i++){

        for (int j=0;j<i;j++){
            //Check if previous boxes can be stacked
            if(canbestacked(vect[j],vect[i]))
                if(maximum<heights[j])
                    maximum=heights[j];
        }
    heights[i]+=maximum;
    maximum=0;
    }
    cout<<*max_element(heights.begin(), heights.end());
    return 0;
}
