#include <iostream>
#include "Trie.h"

int main(){
    Trie Names;
    Names.insert("h5llo");
    Names.insert("hEy");
    Names.insert("sup");
    Names.insert("heyda");
    std::cout<<(Names.contains("hEy") ? "True" : "False")<<std::endl;
    std::cout<<(Names.contains("hEyo") ? "True" : "False")<<std::endl;
    Names.printWords();

    return 0;
}