#include <iostream>

int value = 1234598;
int* ptrone = &value;
int** ptrtwo = &ptrone;

float valuef = 3.98649;

int main() {
    do {
    std::cout << "INT   : " << std::hex << std::uppercase << &value << std::endl;
    std::cout << "INT VALUE : " << std::dec << value << std::endl;
    std::cout << "PTR1  : " << std::hex << std::uppercase << &ptrone << std::endl;
    std::cout << "PTR2  : " << std::hex << std::uppercase << &ptrtwo << std::endl;
    std::cout << "FLOAT : " << std::hex << std::uppercase << &valuef << std::endl;
    std::cout << "FLOAT VALUE : " << valuef << std::endl;
    std::cout << "Enter Enter to continue : \n";
    getchar();
    system("clear");
    }while(1);
    return 0;
}