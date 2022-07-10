#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP

#include <list>
#include <deque>

/**
 * The class is used to managed the DCC packets used to control model railroad.
 * It offers the possibility to send a new packet to the railway from its data
 * bytes and to retrieve the next bit that needs to be transmitted to the railway
 */
class PacketManager {

public:
// ----------------------------------------------------------- Public properties

    /**
     * This packet is used to
     */
    static const std::list<uint8_t> IDLE_PACKET;

// -------------------------------------------------------------- Public methods

    /**
     * This method retrieves the next bit that needs to be transmitted to the
     * railway, and removes it from the queue of bits
     *
     * @return the bit value that needs to be sent
     */
    bool popNextBit();

    /**
     * This method insert a new DCC packet to the end of the queue of packets.
     * The DCC packet is built from its packet data bytes,
     * ie the address and the command data.
     * This address and command information can occupy several bytes each,
     * in accordance with the NMRA DCC documentation.
     *
     * @see [Communication Standards for DCC - Section 9.2.1
     * ](https://www.nmra.org/sites/default/files/s-9.2.1_2012_07.pdf))
     *
     * @param packetData list of the packet data bytes,
     *  ie the address and the command ones
     */
    void insertPacketDataToQueue(std::list<uint8_t> packetData);

// --------------------------------------------------- Constructors / Destructor

    /** Construct a PacketManager */
    PacketManager();

    /** Destruct the PacketManager object */
    virtual ~PacketManager();

private:
// ---------------------------------------------------------- Private properties

    std::deque<uint8_t> packetQueue;

    uint8_t msbPosition;

    uint8_t nextBitPosition;

// ------------------------------------------------------------- Private methods

    void insertCompletePacketToDataQueue(
            const std::list<uint8_t> &completePacket);

    void insertPacketByteBeginningToDataQueue(uint8_t packetByte);

    void insertPacketByteEndingToDataQueue(
            uint8_t packetByte, bool delimiter);
};

#endif // PACKETMANAGER_HPP
