#include <cstdio>
#include <memory>
#include "Observer.h"
#include "AllyCenter.h"

int main() {
    // 创建一个战队
	auto controller = std::make_unique<AllyCenterController>();

	// 创建4个玩家，并加入战队
	auto Jungle     = std::make_unique<Player>("Jungle");
    auto Single     = std::make_unique<Player>("Single");
    auto Jianmengtu = std::make_unique<Player>("Diego");
    auto SillyDog   = std::make_unique<Player>("Richard");

    controller->join(Jungle.get());
    controller->join(Single.get());
    controller->join(Jianmengtu.get());
    controller->join(SillyDog.get());

    std::puts("");

    Jungle->call(RESOURCE, controller.get());
    std::puts("");
    SillyDog->call(HELP, controller.get());
    std::puts("");

#ifdef _WIN32
    system("pause");
#endif
    return 0; // 智能指针自动释放
}