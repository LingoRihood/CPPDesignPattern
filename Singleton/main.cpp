#define THREAD_NUM 6
#include <iostream>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "Singleton.h"

pid_t GetThreadId() {
    // syscall 是一个系统调用接口，可以让你直接调用操作系统提供的底层功能。
    // SYS_gettid 是 Linux 系统调用号，表示获取当前线程的线程ID（gettid）。
    // syscall(SYS_gettid) 实际上是执行 gettid() 系统调用的操作，返回当前线程的线程ID。
    // 该调用返回当前线程的线程ID，通常与 pthread_self() 的返回值相同，但是 gettid 是返回内核级线程ID，而 pthread_self() 返回的是 POSIX 线程库级别的线程ID
    // SYS_gettid 是一个常量，表示获取当前线程ID的系统调用号。
    // 每个系统调用都有一个唯一的编号（常量），用于标识该系统调用。SYS_gettid 对应的是获取线程ID的操作。
    return syscall(SYS_gettid);
}

void* callSingleton_Lazy(void* arg) {
    int threadID = *(int*)arg;
    Singleton_Lazy *s = Singleton_Lazy::getInstance();
    printf("[Lazy] 线程编号: %d, 实例地址: %d\n", threadID, GetThreadId());
    // printf("[Hungry] 线程编号: %d, 实例地址: %p\n", threadID, s);
    return 0;
}

void* callSingleton_Hungry(void* arg) {
    // 将arg 从 void* 类型的通用指针强制转换成 int*类型的指针, 然后对转换后的指针解引用，取出实际的整型数值（即线程编号）。
    int threadID = *(int*)arg;
    Singleton_Hungry *s = Singleton_Hungry::getInstance();
    printf("[Hungry] 线程编号: %d, 实例地址: %d\n", threadID, GetThreadId());
    // printf("[Hungry] 线程编号: %d, 实例地址: %p\n", threadID, s);
    return 0;
}

int main() {
    pthread_t threads_pool[THREAD_NUM];
    int tids[THREAD_NUM], params[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++) {
        params[i] = i; // 独立参数，避免竞争

        /*
        int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
        */
        // 前半部分线程调用懒汉式单例
        if(i < THREAD_NUM / 2)
            tids[i] = pthread_create(&threads_pool[i], NULL, callSingleton_Lazy, (void*)&params[i]);
        else // 后半部分线程调用饿汉式单例
            tids[i] = pthread_create(&threads_pool[i], NULL, callSingleton_Hungry, (void*)&params[i]);

        // On success, pthread_create() returns 0; on error, it returns an error number, and the contents of *thread are undefined.
        if(tids[i]) {
            printf("Error: unable to create thread.\n");
            exit(-1);
        }
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        // On success, pthread_join() returns 0; on error, it returns an error number
        tids[i] = pthread_join(threads_pool[i], NULL);
        if(tids[i]) {
            printf("Error: unable to join thread.\n");
            exit(-1);
        }
    }
    printf("main exiting.\n");
    return 0;
}