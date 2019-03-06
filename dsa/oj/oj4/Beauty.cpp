#include <bits/stdc++.h>
using namespace std;

int cnt=0;

struct trie{
    struct trie *children[5];
    int end;
    int flag;
};

struct trie *createnode(){
    struct trie *now = new trie;
    for (int i = 0; i < 5; ++i) {
        now->children[i]=NULL;
    }
    now->flag=0;
    now->end=0;
    return now;
}

void insert(struct trie *root,string str){
    struct trie *traverse=root;
    for(int c=0;c<str.length();c++) {
        int num = str[c] - 'a';
        if(!traverse->children[num])
            traverse->children[num]=createnode();
        traverse=traverse->children[num];
    }
    traverse->end+=1;
    return;
}

int z=0;

void search(struct trie *root,string str,int ind) {
    struct trie *traverse = root;
    while(ind<str.length()){
        if (str[ind] == '?'){
            for (char ch = 'a'; ch <= 'e'; ch++) {
                if (traverse->children[ch-'a'] != NULL)
                    search(traverse->children[ch-'a'], str, ind+1);
            }
            search(traverse, str, ind+1);
            return;
        }
        else{
            int num = str[ind] - 'a';
            if (!traverse->children[num])
                return;
            traverse = traverse->children[num];
            ind++;
        }
    }
    if(traverse->end!=0 && traverse!=NULL)
        if (traverse->flag != z) {
            traverse->flag = z;
            cnt+=traverse->end;
        }
        else
            return;
}

int main() {
    struct trie *root = createnode();
    int n, s = 0;
    scanf("%d",&n);
    char temp;
    for (int i = 0; i < n; i++) {
        scanf("%c",&temp);
        insert(root, temp);
    }
    int q;
    scanf("%d",&q);
    for (int p = 0; p < q; ++p) {
        int ans=0;
        char input;
        scanf("%c",&input);
        z=p+1;
        search(root,input,0);
        printf("%d\n",cnt);
        cnt=0;
    }
    return 0;
}
