#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> {
private:
    int a_;
    char c_;

public:
    A(int a, char c) : a_(a), c_(c) {}

    void show() {
        auto p = shared_from_this();

        std::cout << "a_ = " << p->a_ << ", c_ = " << p->c_ << std::endl;
    }
};


//继承了std::enable_shared_from_this<T>的类的对象必须要保存在
//shared_ptr指针中
int main() {
// the bellow is wrong code.
//    A a(3, 'a');
//    a.show();

// this is right.
    std::shared_ptr<A> p = std::make_shared<A>(3,'l');
    p->show();

    return 0;
}