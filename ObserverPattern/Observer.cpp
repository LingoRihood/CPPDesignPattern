#include "Observer.h"
#include "AllyCenter.h"  // 这里需要完整类型，才能调 notify

void Player::call(INFO_TYPE infoType, AllyCenter* ac) {
    switch (infoType) {
        case RESOURCE: std::printf("%s :我这里有物资\n", getName().c_str()); break;
        case HELP:     std::printf("%s :救救我\n",       getName().c_str()); break;
        default:       std::printf("Nothing\n"); break;
    }
    ac->notify(infoType, getName());
}

void Player::help() const { std::printf("%s:坚持住，我来救你！\n", getName().c_str()); }
void Player::come() const { std::printf("%s:好的，我来取物资\n",   getName().c_str()); }
