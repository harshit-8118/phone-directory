#include <bits/stdc++.h>
using namespace std;
map<string, string> mp;
struct Trie{
        vector<Trie*> child;
        bool isend;
        Trie(){
            child.resize(27, NULL);
            isend = false;
        }
};
struct Trie *root = new Trie();
vector<pair<string, string>> res;
void insert(string str){
    struct Trie *node = root;
    for(auto x: str){
        if(x == ' '){
            if(node->child[26] == NULL){
                node->child[26] = new Trie();
            }
            node = node->child[26];
            continue;
        }
        x = (x >= 'A' && x <= 'Z')? x + 32: x;
        if(node->child[x - 'a'] == NULL){
            node->child[x - 'a'] = new Trie();
        }
        node = node->child[x -'a'];
    }
    node->isend = true;
}
bool isendofnode(struct Trie* node){
    return node->isend != false;
}
void display(struct Trie* node, string key){
    if(isendofnode(node)){
        res.push_back({key, mp[key]});
    }
    for(int i= 0;i< 27;i++){
        if(node->child[i]){
            char ch = i+'a';
            if(i == 26){
                ch = ' ';
            }
            key.push_back(ch);
            display(node->child[i], key);
            key.pop_back();
        }
    }
}
bool search(string key){
    int n = key.length();
    struct Trie* node = root;
    for(int i=0;i< n;i++){
        if(key[i] == ' '){
            if(node->child[26] == NULL){
                return false;
            }
            node = node->child[26];
            continue;
        }
        int ind = key[i] - 'a';
        if(node->child[ind] == NULL){
            return false;
        }
        node = node->child[ind];
    }
    display(node, key);
    return true;
}
bool isEmpty(struct Trie* root)
{
    for (int i = 0; i < 27; i++)
        if (root->child[i])
            return false;
    return true;
}
Trie* remove(struct Trie* root, string key, int depth = 0)
{
    if (!root)
        return NULL;
    if (depth == key.size()) {
        if (isendofnode(root))
            root->isend = false;
 
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }
        return root;
    }
    int index;
    if(key[depth] == ' '){
        index = 26;
    }
    else
        index = key[depth] - 'a';
    root->child[index] =
          remove(root->child[index], key, depth + 1);
    if (isEmpty(root) && root->isend == false) {
        delete (root);
        root = NULL;
    }
    return root;
}
void print()
{
    for(auto x: res){
        cout<<x.first<<" "<<x.second<<endl;
    }
}
string validateName(string &name){
    for(auto &x: name){
        x = (x>='A' && x <='Z')? x+32: x;
    }
    return name;
}
int main(){
    
    string name, number;
    while(true){   
        cout<<"Select :"<<endl;
        cout<<"\t\ti : insert"<<endl;
        cout<<"\t\ts : search"<<endl;
        cout<<"\t\td : delete"<<endl;
        cout<<"\t\tx : exit"<<endl;
        cout<<""<<endl;
        char expr;
        cin>>expr;
        expr = tolower(expr);
        cin.ignore();
        if(expr == 'x'){
            break;
        }
        switch (expr)
        {
        case 'i':
            while(1){
                cout<<"Add name : ";
                getline(cin, name);
                name = validateName(name);
                if(mp.find(name) == mp.end()){
                    cout<<name<<endl;
                    cout<<endl<<"Add number : ";
                    cin>>number;        // number validation should be check on demand.
                    cout<<number<<endl;
                    mp[name] = number;
                    insert(name);
                    break;
                }
                else
                cout<<endl<<"name already exists, edit name please"<<endl;
            }  
            break;
        case 's':
            cout<<"Enter name to be search : ";
            getline(cin, name);
            name = validateName(name);
            if(!search(name)){
                cout<<"name doesn't exist";
            }else{
                print();
                res.clear();
            }
            break;
        case 'd':
            cout<<"Enter name to be delete : ";
            getline(cin, name);
            name = validateName(name);
            if(mp.find(name) != mp.end()){
                mp.erase(name);
                remove(root, name, 0);
            }else{
                cout<<"name doesn't exist";
            }
            break;
        default:
            cout<<"wrong input";
            break;
        }
    }
    return 0;
}