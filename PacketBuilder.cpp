#include "PacketBuilder.hpp"

uint8_t compute_control_byte(const std::list<uint8_t> &packetData) {
    uint8_t control_byte = 0;
    for (auto const &packet_byte: packetData) {
        control_byte ^= packet_byte;
    }

    return control_byte;
}

std::list<uint8_t> build_complete_packet_data(
        std::list<uint8_t> &packetData) {
    uint8_t control_byte = compute_control_byte(packetData);

    // The complete_packet bytes firstly contains the preamble which is two 255
    std::list<uint8_t> complete_packet_bytes = { 255, 255 };

    // The complete_packet bytes then contains the packet data
    complete_packet_bytes.splice(
            complete_packet_bytes.end(), packetData);

    // The complete packet bytes finally contains the control_byte
    complete_packet_bytes.push_back(control_byte);

    return complete_packet_bytes;
}
