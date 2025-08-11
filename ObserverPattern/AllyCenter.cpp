#include "AllyCenter.h"
#include "Observer.h"

#include <algorithm>

constexpr std::size_t kMaxPlayers = 4;

/***********   AllyCenter    ****************/
AllyCenter::AllyCenter(){
	printf("大吉大利，今晚吃鸡!\n");
}

// 加入玩家
void AllyCenter::join(Observer* player){
    if (!player) return;
    if (playerList.size() >= kMaxPlayers){
        std::printf("玩家已满!\n");
        return;
    }
    // 可选：检查重复
    if (std::find(playerList.begin(), playerList.end(), player) != playerList.end()) {
        std::printf("玩家 %s 已在队伍中\n", player->getName().c_str());
        return;
    }
    std::printf("玩家 %s 加入\n", player->getName().c_str());
    playerList.push_back(player);
    if (playerList.size() == kMaxPlayers){
        std::printf("组队成功，不要怂，一起上！\n");
    }
}


// 移除玩家
void AllyCenter::remove(Observer* player){
    if (!player) return;
    auto it = std::remove(playerList.begin(), playerList.end(), player);
    if (it != playerList.end()) {
        std::printf("玩家 %s 退出\n", player->getName().c_str());
        playerList.erase(it, playerList.end());
    }
}

/***********   AllyCenter    ****************/


/**********   AllyCenterController    *******/
AllyCenterController::AllyCenterController() {}

void AllyCenterController::notify(INFO_TYPE infoType, const std::string& name) {
    switch (infoType){
    case RESOURCE:
        for (Observer* obs : playerList){
            if (!obs || obs->getName() == name) continue;

            // reinterpret_cast<Player*>(obs)
            // 只适合做底层、与继承无关的位级转换（整型↔指针、不同不相关指针类型之间的桥接等），不应用于类层次转型。
            if (auto* p = dynamic_cast<Player*>(obs)) p->come();
        }
        break;
    case HELP:
        for (Observer* obs : playerList){
            if (!obs || obs->getName() == name) continue;
            if (auto* p = dynamic_cast<Player*>(obs)) p->help();
        }
        break;
    default:
        std::printf("Nothing\n");
    }
}
/**********   AllyCenterController    *******/