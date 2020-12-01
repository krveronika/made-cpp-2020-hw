#include "fuction.h"
#include "compose.h"


int func2(const int * x, int y)
{
    return (*x) + y;
}

using std::cout;
using std::endl;

void check1()
{
    typedef function<int (const int * , int)> int_function_with_two_args_t;
    int_function_with_two_args_t f2(func2);
    
    int x = 10;
    cout << "calling function with signature int (const int * , int):              " <<  f2(&x, 20) << endl;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    check1();

    const std::function<bool(int)> a = [] (int x) -> bool {
        std::cout << "a" << std::endl;
        return x > 10;
    };
    
    const std::function<int(float)> b = [] (float y) -> int {
        std::cout << "b" << std::endl;
        return int(y * y);
    };
    
    const std::function<float(bool)> c = [] (bool z) -> float {
        std::cout << "c" << std::endl;
        return z ? 3.1f : 3.34f;
    };
    
    {
        auto d = compose(a, b, c, a, b, c);
        auto true_res = c(b(a(c(b(a(true))))));
        if (d(true) != true_res) {
            cout << "Test Failed" << endl;
        }
    }
    
    {
        int x = 100;
        auto res = compose(a);
        auto true_res = a(x);
        if (res(x) != true_res) {
            cout << "Test Failed" << endl;
        }
    }
    
    return 0;

}
