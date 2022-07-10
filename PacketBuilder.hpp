#ifndef PACKETBUILDER_HPP
#define PACKETBUILDER_HPP

#include <list>

/**
 * Compute the control byte of the DCC Packet, also known as the Error Detection
 * Data Byte. This byte is an exclusive or (XOR) of the all the packet data
 * bytes, ie both the address and instruction bytes
 *
 * @param packetData list of packet data bytes (address and instructions bytes)
 * @return the result of the XOR of the packet data bytes
 */
uint8_t compute_control_byte(const std::list<uint8_t> &packetData);

/**
 * Build a complete DCC packet from its packet data bytes which only contains
 * the bytes of the address and the command.
 * <br/>
 * <br/>
 *
 * The complete packet contains:
 * <li> two preamble bytes having the value 255
 * <li> the packet data bytes (address and instruction)
 * <li> the control byte (or Error Detection Data Byte)
 *
 * @param packetData list of packet data bytes (address and instructions bytes)
 * @return the complete list of the packet data bytes
 */
std::list<uint8_t>
build_complete_packet_data(std::list<uint8_t> &packetData);

#endif //PACKETBUILDER_HPP
