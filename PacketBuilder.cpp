#include "PacketBuilder.hpp"

uint8_t compute_control_byte(const std::list<uint8_t> &packetData) {
    uint8_t controlByte = 0;
    for (auto const &packetByte: packetData) {
        controlByte ^= packetByte;
    }

    return controlByte;
}

std::list<uint8_t> buildCompletePacketData(
        std::list<uint8_t> &packetData) {
    uint8_t controlByte = compute_control_byte(packetData);

    // The complete_packet bytes firstly contains the preamble which is two 255
    std::list<uint8_t> completePacketBytes = { 255, 255 };

    // The complete_packet bytes then contains the packet data
    completePacketBytes.splice(
            completePacketBytes.end(), packetData);

    // The complete packet bytes finally contains the controlByte
    completePacketBytes.push_back(controlByte);

    return completePacketBytes;
}
