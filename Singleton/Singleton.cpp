#include "Singleton.h"

std::unique_ptr<Singleton_Lazy> Singleton_Lazy::instance = nullptr;
std::once_flag Singleton_Lazy::initFlag;