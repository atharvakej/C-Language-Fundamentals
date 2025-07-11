#include<bits/stdc++.h>
using namespace std;

struct Node {
    Node * links[26];
    bool flag = false;
    bool containskey(char ch){
        return (links[ch-'a']!=NULL);
    }
    void put(char ch, Node* node){
        links[ch-'a'] = node;
    }
    Node* get(char ch){
        return links[ch-'a'];
    }
    bool setEnd(){
        flag = 1;
    }
    bool isend(){
        return flag;
    }
}

class Trie{
    private:
    Node* root; // Head of Trie 

    Trie(){
        root = new Node();

    }

    // O(n) - len of word
    void insert(string word){
        Node* node = root;
        for(int i=0;i<word.size();i++){
            if(!node->containskey(word[i])){
                node-> put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();


    }

    bool search(string word){
        Node* node = root;
        for(int i=0;i<word.size();i++){
            if(!node->containskey(word[i])){
                return false;
            }
            node = node->get(word[i]);
        }
        return node->isend();
    }
    
    bool startswith(string prefix){
        Node* node = root;
        for(int i=0;i<word.size();i++){
            if(!node->containskey(word[i])){
                return false;
            }
            node = node->get(word[i]);
        }
        return true;
    }
}


int main(){

}