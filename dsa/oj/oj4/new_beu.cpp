#include <bits/stdc++.h>
#define nu 5
using namespace std;

int cnt=0,var=0;

struct trie{
    struct trie *children[nu];
    int end;
    int flag;
};

struct trie *createnode(){
    struct trie *now = new trie;
    now->children[0]=NULL;
    now->children[1]=NULL;
    now->children[2]=NULL;
    now->children[3]=NULL;
    now->children[4]=NULL;
    now->flag=nu-5;
    now->end=nu-5;
    return now;
}

void insert(struct trie *root,string str){
    var=nu;
    struct trie *traverse=root;
    int c=0,num;
    while(c<str.length()) {
        num = str[c] - 'a';
        if(traverse->children[num]==0)
            traverse->children[num]=createnode();
        else{}
        traverse=traverse->children[num];
        c++;
    }
    traverse->end=traverse->end+1;
    return;
}

int z=0;

void search(struct trie *root,string str,int ind) {
    struct trie *traverse = root;
    for(;ind<str.length();){
        if (str[ind] == '?'){
            char ch;
            ch='a';
            while ( ch <= 'e') {
                if(traverse->children[ch-'a']==NULL){}
                else if (traverse->children[ch-'a'] != NULL)
                    search(traverse->children[ch-'a'], str, ind+1);
                else{}
                ch++;
            }
            search(traverse, str, ind+1);
            return;
        }
        else{
            int num = str[ind] - 'a';
            if (traverse->children[num]==0)
                return;
            traverse = traverse->children[num];
            ind++;
            var=nu;
        }
    }
    var=nu;
    if(traverse->end!=0 && traverse!=NULL)
        var=nu;
        if (traverse->flag != z) {
            traverse->flag = z;
            var=0;
            cnt+=traverse->end;
        }
        else if (traverse->flag==z){
              return;
         }
        else{
            return;
        }
}

int main() {
    struct trie *root = createnode();
    int n, s = 0,i=0,ans,q;
    cin >> n;
    string temp, input;
    i=0;
    for (; i < n;) {
        cin >> temp;
        insert(root, temp);
        i++;
    }
    q=0;
    cin >> q;
    int p=0;
    for (; p < q;) {
        ans=0;
        cin >> input;
        z=p+1;
        search(root,input,0);
        cout << cnt << endl;
        cnt=0;
        p++;
    }
    return 0;
}

