#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>
#include <mutex>
#include <memory>

// 确保一个类只有一个实例。
// 提供全局访问点，让用户方便访问
// 懒汉式（线程安全，推荐写法）
// 懒汉式（Lazy Singleton）：延迟创建对象（用时才创建）
class Singleton_Lazy {
public:
    // 第一次 调用时，执行内部的 lambda 表达式，创建一个新的单例对象。
    // 后续所有次 调用时，都直接跳过这个 lambda，不再执行创建对象的操作。
    static Singleton_Lazy* getInstance() {
        // template< class Callable, class... Args >
        // void call_once(std::once_flag& flag, Callable&& f, Args&&... args);
        // 确保给定的**可调用对象（如lambda表达式）**仅被调用一次。
        // 如果多个线程同时执行该行代码，也能确保只有一个线程实际执行了初始化操作，其他线程则会等待，直到第一次调用完成后再继续执行，且不会重复执行初始化操作。
        // flag：一个标志位，标识对应的初始化是否已经完成。
        // Callable：一个可调用对象（比如lambda表达式或函数），代表真正要执行的初始化动作。
        std::call_once(initFlag, []() {
            std::cout << "\n[Lazy] 创建新的实例" << std::endl;
            // instance = std::make_unique<Singleton_Lazy>(); // ✅ 更安全，更推荐
            instance.reset(new Singleton_Lazy());
        });

        std::cout << "\n[Lazy] 获取单例实例" << std::endl;
        return instance.get();
    }

    void doSomething() const {
        std::cout << "\n[Lazy] 正在执行任务..." << std::endl;
    }

private:
    Singleton_Lazy() {
        std::cout << "\n[Lazy] 构造函数调用" << std::endl;
    }

    ~Singleton_Lazy() {
        std::cout << "\n[Lazy] 析构函数调用" << std::endl;
    }

    // 拷贝构造函数（Copy Constructor）
    // 当使用一个已存在对象初始化另一个新对象时，调用拷贝构造函数
    Singleton_Lazy(const Singleton_Lazy&) = delete;

    // 拷贝赋值运算符（Copy Assignment Operator）
    // 当使用一个已存在的对象去给另一个已存在的对象赋值时调用。
    Singleton_Lazy& operator=(const Singleton_Lazy&) = delete;

    // ⚠️一定要保留这两个声明！
    static std::unique_ptr<Singleton_Lazy> instance;
    static std::once_flag initFlag;

    // 🔑加上这一句：
    // 允许 std::unique_ptr 调用私有析构函数
    friend class std::default_delete<Singleton_Lazy>;
};

// 饿汉式（立即加载）
// 饿汉式（Hungry Singleton）：程序启动时立即创建对象
class Singleton_Hungry {
public:
    static Singleton_Hungry* getInstance() {
        std::cout << "\n[Hungry] 获取单例实例" << std::endl;
        static Singleton_Hungry instance; // 推荐方法，更安全更现代化
        return &instance;
    }

    void doSomething() const {
        std::cout << "\n[Hungry] 正在执行任务..." << std::endl;
    }
    
private:
    // 禁止外界创建新的实例（私有构造、删除拷贝构造和拷贝赋值）。
    Singleton_Hungry() {
        std::cout << "\n[Hungry] 构造函数调用" << std::endl;
    }

    ~Singleton_Hungry() {
        std::cout << "\n[Hungry] 析构函数调用" << std::endl;
    }

    Singleton_Hungry(const Singleton_Hungry&) = delete;
    Singleton_Hungry& operator=(const Singleton_Hungry&) = delete;

    // static Singleton_Hungry* instance;
};

// 静态成员初始化 ⚠️头文件定义静态变量，错误！
// 根本原因：违反了单一定义规则（One Definition Rule, ODR）
// 你在头文件中定义了一个静态变量，头文件会被多个.cpp文件包含，这就导致在每个.cpp文件中都定义了一遍，最终会导致链接时的冲突，出现重复定义（multiple definition）错误。
// Singleton_Hungry* Singleton_Hungry::instance = new Singleton_Hungry();

#endif // __SINGLETON_H__