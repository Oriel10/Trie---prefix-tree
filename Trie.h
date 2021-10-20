
#include <iostream>
#include <vector>
#include <string>

static bool isWord(std::string& word);
static bool isLetter(char c);
static bool isUpperCase(char c);

class Trie{
  static const int ABC_len = 52;
  std::vector<Trie*> characters;
  bool is_leaf;
public:
    Trie() : characters(std::vector<Trie*>(ABC_len)), is_leaf(false){}
    void insert(std::string word);
    bool contains(std::string word) const;
    bool startsWith(std::string prefix) const;
    void printWords() const;
    friend void print_aux(std::string word, const Trie* root);
};

void print_aux(std::string word, const Trie* root){
    if(root == nullptr){
        return;
    }
    if(root->is_leaf){
        std::cout<<word<<std::endl;
    }
    for(int i = 0; i < root->ABC_len; i++){
        if(root->characters[i] != nullptr){
            std::string tmp = word;
            if(i<root->ABC_len/2){
                print_aux(word += ('a' + i), root->characters[i]);
            }
            else{
                print_aux(word += ('A' + i - root->ABC_len/2), root->characters[i]);
            }
            word = tmp;
        }
    }
}

void Trie::insert(std::string word){
    Trie* tmp = this;
    if(!isWord(word)){
        std::cout<<"\""<<word<<"\""<<" is not accepted, only letter words are accepted!"<<std::endl;
        return;
    }
    for(char c : word){
        if(isUpperCase(c)){
          if(tmp->characters[c-'A'+ABC_len/2] == nullptr){
                tmp->characters[c-'A'+ABC_len/2] = new Trie();
          }  
          tmp = tmp->characters[c-'A'+ABC_len/2];
          continue;
        }
        else if(tmp->characters[c-'a'] == nullptr){
            tmp->characters[c-'a'] = new Trie();
        }
        tmp = tmp->characters[c-'a'];
        
    }
    tmp->is_leaf = true;
}

bool Trie::contains(std::string word) const{
    const Trie* tmp = this;
    for(char c : word){
        if(isUpperCase(c)){
          if(tmp->characters[c-'A'+ABC_len/2] == nullptr){
                return false;
          }  
          tmp = tmp->characters[c-'A'+ABC_len/2];
        }
        else if(tmp->characters[c-'a'] == nullptr){
            return false;
        }
        else{
            tmp = tmp->characters[c-'a'];
        }
    }
    return tmp->is_leaf;
}

/* True if there is any word in the trie that starts with the given prefix. */
bool Trie::startsWith(std::string prefix) const{
    const Trie* tmp = this;
    for(int i = 0; i < prefix.length(); i++){
        tmp = tmp -> characters[isUpperCase(prefix[i]) ? (prefix[i]-'A'+ABC_len/2) : (prefix[i]-'a')];
         if(tmp == nullptr){
            return false;
        }
    }
    return true;
}

void Trie::printWords() const{
    print_aux("", this); 
    // std::cout<< "we made it";
}

static bool isWord(std::string& word){
    for(auto& c : word){
        if(!isLetter(c)){
            return false;
        }
    }
    return true;
}

static bool isLetter(char c){
    return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

static bool isUpperCase(char c){
    return (('A' <= c) && (c <= 'Z'));
}
