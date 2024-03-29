#include <iostream>

#include "libpacketmanager/packet_manager.hpp"

int main() {

    packet_manager packetManager;

    packetManager.insertPacketDataToQueue({ 0, 0 });
    packetManager.insertPacketDataToQueue({ 255, 0, 255 });
    packetManager.insertPacketDataToQueue({ 255, 0 });
    packetManager.insertPacketDataToQueue({ 255, 255 });
    packetManager.insertPacketDataToQueue({ 43, 26 });
    packetManager.insertPacketDataToQueue({ 12, 23, 45, 67 });

    std::cout << packetManager << std::endl;

    for (int i = 0; i < 100; ++i) {
        std::cout << packetManager.popNextBit();
    }

    return 0;
}

