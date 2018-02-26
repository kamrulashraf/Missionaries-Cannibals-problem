#include <bits/stdc++.h>
using namespace  std;

#define N 3000
#define inf 2e9
#define rep(i,x,y)  for(int i = x ; i< y ; i++)
#define F(i,x)  for(int i = 0 ; i< x ; i++)
#define ff first
#define ss second
#define pii pair < int , int>
#define ll long long
#define ull unsigned ll
#define MP make_pair
#define PB push_back
#define sca(a) scanf("%d",&a)
#define scaa(a,b) scanf("%d%d",&a,&b)
#define scaaa(a,b,c) scanf("%d%d%d",&a,&b,&c)



void conv(int n){
   for(int i = 0 ; i < 6 ; i++){
          if(n&(1<<i)){
             cout << 1 ;
          }
          else cout << 0;
   }
   cout << endl;
}



class State{
     int vis[N][3] ;
     map  < pii , pii > par;
     public:



     bool isIllegalState(int s){
         int man = 0, giant = 0;
         for(int i = 0 ; i< 3 ; i++){
            if(s & (1<<i)) man++;
         }
         for(int i = 3 ; i< 6 ; i++){
             if(s & (1<<i)) giant++;
         }
         bool flag = 0;
         if(man < giant && man) flag = 1;
         if(3-man < 3- giant && (3-man)) flag = 1;
         return 1-flag;
     }

     int filpBit(int n){
        int temp = 0;
        for(int i = 0 ; i< 6 ; i++){
            if(i != n){
                temp |= (1<<i);
            }
     }

     return temp;
    }
     vector < pii > generateNextState(pii s){
         vector < pii > v;
         int tt = s.ff;

         for(int i = 0 ; i< 6 ; i++){
              int temp = s.ff & (1<<i);
              if( (temp && s.ss) || (temp == 0 && s.ss == 0) ){
                  for(int j = i+1 ; j < 6 ; j++){
                     int temp1 = s.ff & (1<<j);
                     if( (temp1 && s.ss) || (temp1==0 && s.ss == 0)){
                          if(s.ss == 0){
                               tt |= (1<<i);
                               tt |= (1<<j);
                          }
                          else{
                               tt = (tt & filpBit(i));
                               tt = (tt & filpBit(j));

                          }
                          if(isIllegalState(tt)){
                                  v.push_back(MP(tt,1-s.ss));
                          }
                          tt = s.ff;
                     }
                  }
              }
         }

         tt = s.ff;

         for(int i = 0 ; i< 6 ; i++){
             int temp = s.ff & (1<<i);

             if( (temp && s.ss) || (temp == 0 && s.ss == 0) ){
                   if(s.ss == 0){
                       tt |= (1<<i);

                    }
                    else{
                       tt &= filpBit(i);

                    }
                    if(isIllegalState(tt)){
                        v.push_back(MP(tt,1-s.ss));
                    }
             }

             tt = s.ff;
         }

         return v;
     }
     void bfs(){

          queue < pii >  q;
          q.push(MP(0,0));
          vis[0][0] = 1;

          while(!q.empty()){
              pii u = q.front();
              q.pop();
              vector < pii > temp = generateNextState(u);
              for(int i = 0 ; i< temp.size() ; i++){
                  pii v = temp[i];
                  if(vis[v.ff][v.ss] == 0){
                         q.push(v);
                         vis[v.ff][v.ss] = 1;
                         par[v] = u;
                  }
              }
          }

     }

     void print(){
        pii temp = MP(63,1);
        vector <pii> v;
        v.push_back(temp);
        while(temp.ff  || temp.ss){
           temp =par[temp];
           v.push_back(temp);
        }
        reverse(v.begin() , v.end());

        printf("BIT STATE PRINT\n");
        printf("________________\n\n");
        for(int i = 0 ; i< v.size() ; i++){
             conv(v[i].ff);
        }
        printf("\n");

        printf("SOLUTION PRINT\n");
        printf("___________________\n\n");

        for(int i = 1 ; i< v.size() ; i++){
             int t = v[i-1].ff ^ v[i].ff;

             int cnt = 0;
             for(int j = 0 ; j< 3 ; j++){
                if(t & (1<<j)){
                      cnt++;

                }
             }

             bool flag = 0;
             if(cnt > 0){
                flag  = 1;
                if(cnt > 1) printf("%d MISSIONARIES ",cnt);
                else printf("%d MISSIONARIE ",cnt);
             }

             cnt = 0;
             for(int j = 3 ; j< 6 ; j++){
                if(t & (1<<j)){
                      cnt++;
                }
             }

             if(cnt > 0){
                if(flag == 1) printf("AND ");
                if(cnt > 1) printf("%d CANNIBALS ",cnt);
                else printf("%d CANNIBAL ",cnt);
             }

             if(v[i].ss == 0) printf("COME BACK\n");
             else printf("GO TO OTHER SITE OF RIVER\n");
        }

     }
};
int main()
{

    State a;
    a.bfs();
    a.print();

}
