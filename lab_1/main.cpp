#include <iostream>

int main()
{
    std::cout << "Hello, world" << std::endl;
    int i;
    if (!std::cin>>i)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::cout << "i = " << i << std::endl;
    return 0;
}