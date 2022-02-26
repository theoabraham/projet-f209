#include <iostream>
#include <string>


int main(){
    std::string str = "Bonsoir yoyoy oui";
    //std::cout<< str.substr(4,3)<<std::endl; 
    //std::cout<< str[5] <<std::endl; 
    std::cout << "\u25AE" << std::endl; //mur vertical 
    std::cout << "\u25AC" << std::endl; //mur horizontal 
    return 0;
}