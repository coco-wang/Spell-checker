#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cop4530;

vector<string> line_split(string line)
{
    string word; vector<string> word_list;
    istringstream iss(line);
    while(getline(iss,word,' ')){
         int count=0;
         for (auto itr=word.begin();itr!=word.end();++itr){
                 if(*itr>=65 && *itr<=122)
                         ++count;}
         if(count==word.length())
             word_list.push_back(word);
    }
    return word_list;
}

void replace (string word,int k,vector<string>&box)
{
        string final;
        for(char i='a';i<='z';++i){
            final=word.replace(k,1,1,i);
            box.push_back(final);
        }

}

vector<string> screen(const vector<string>& wd, HashTable<string> f1)
{
    vector<string> list;
    for(int i=0;i<wd.size();++i){
        if(f1.contains(wd[i])&&list.size()<10)
             list.push_back(wd[i]);
    }
    return list;
}
void display(const vector<string>& v,string& wd,string copy)
{
        cout<<"===================================="<<endl;
        for(int i=0;i<v.size();++i)
        cout<<i<<"):"<<v[i]<<endl;
        cout<<"n (no change):"<<endl;
        cout<<"===================================="<<endl;
        char a;
        cout<<"Your choice:";
        cin>>a;
        if (a=='n')
            wd=copy;
        else{
            int num = int(a)-48;
            wd=v[num];}
}

int main(int argc, char*argv[])
{
        HashTable<string> f1;
        f1.load(argv[1]);

        ifstream input(argv[2]);string line;
        getline(input,line);
        vector<string> words=line_split(line);
        ofstream output_file(argv[3]);

        vector<string> candi;vector<string> final; string copy1,copy2;
        for(auto&wd:words){
            if (f1.contains(wd))
                 output_file<<wd<<" ";
            else{
            copy1= copy2 = wd;
            transform(copy1.begin(),copy1.end(),copy1.begin(),::toupper);
            cout<<copy1<<" "<<endl;
            for(int k =0 ;k<wd.length();++k)
                replace(wd,k,candi);
            final=screen(candi,f1);
            display(final,wd,copy2);
            output_file << wd <<" ";
            final.clear();
            candi.clear();
            }
         cout<<"\n";


     }

    return 0;
};
