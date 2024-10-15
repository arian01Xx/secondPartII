#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    //para encontrar el representante del grupo (union-find)
    int find(int x, vector<int>& parent){
        if(parent[x]!=x){
            parent[x]=find(parent[x],parent); 
        }
        return parent[x];
    }

    //funcion para unir dos grupos (union-find)
    //num, factor, parent, size
    //num, num/factor, parent, size
    void unite(int x, int y, vector<int>& parent, vector<int>& size){
        int rootX=find(x,parent);
        int rootY=find(y,parent);
        if(rootX != rootY){
            if(size[rootX] > size[rootY]){
                parent[rootY]=rootX;
                size[rootX]+=size[rootY];
            }else{
                parent[rootX]=rootY;
                size[rootY]+=size[rootX];
            }
        }
    }
public:
    int largestComponentSize(vector<int>& nums) {
        int n=nums.size();
        int maxNum=*max_element(nums.begin(), nums.end());

        vector<int> parent(maxNum+1);
        vector<int> size(maxNum+1,1);
        iota(parent.begin(),parent.end(),0);

        for(int num: nums){
            for(int factor=2; factor*factor<=num; ++factor){
                if(num%factor==0){
                    unite(num, factor, parent, size); //unir con el factor
                    unite(num, num/factor, parent, size); //unir con el cociente
                }
            }
        }

        unordered_map<int,int> componentSize;
        int maxComponent=0;
        for(int num: nums){
            int root=find(num,parent);
            componentSize[root]++;
            maxComponent=max(maxComponent, componentSize[root]);
        }
        return maxComponent;
    }
};

int main(){
    return 0;
}