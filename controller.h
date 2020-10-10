#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <memory>
#include <functional>
#include <type_traits>

class CDatabase;
class CController
{
public:
    CController();
    virtual ~CController();
protected:
    std::unique_ptr<CDatabase> m_db;
public:
    void Enter();
    void Exit(bool commit = true);
    int test(int t);
};

//template<typename T, typename U, typename...Args> struct  RunOperation;
template<typename T, typename U, typename...Args>
typename std::result_of<U(T, Args...)>::type RunOperation(T&& controller, U&& function, Args...args)
{
    try {
        controller.Enter();
        auto res = std::bind(function, &controller, args...)();
        controller.Exit();
        return res;
    } catch (...) {
        controller.Exit(false);
    }
}

#endif // CONTROLLER_H
