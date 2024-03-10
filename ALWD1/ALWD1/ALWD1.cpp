#include <iostream>
#include "Calculator.h"
#include "GraphMaker.h"

typedef double DataType;

int main() {
    std::locale::global(std::locale(""));
    DataType a, b, h, precision;
    std::cout << "Enter a" << std::endl;
    std::cin >> a;
    std::cout << "Enter b" << std::endl;
    std::cin >> b;
    std::cout << "Enter h" << std::endl;
    std::cin >> h;
    std::cout << "Enter the precision: " << std::endl;
    std::cin >> precision;
    
    GraphMaker<DataType> graph = GraphMaker<DataType>();
    Calculator<DataType> calculator = Calculator<DataType>();

    for (; a <= b; a += h)
        graph.PushPoint(calculator.Calculate(a, precision));
    
    graph.PrintGraph("Header");
    return 0;
}