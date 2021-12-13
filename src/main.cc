#include<iostream>
#include "../inc/Pendu.h"

int main(){
    //game init
    std:: srand(static_cast<unsigned>(time(NULL)));
    Pendu pendu;
    //game loop
    while(pendu.running()){
        pendu.update();
        pendu.render();
    }
}
