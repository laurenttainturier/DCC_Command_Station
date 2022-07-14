#include <libpacketmanager/packet_manager.hpp>

#include <libpacketmanager/details/packet_builder.hpp>

// ----------------------------------------------------------- Public properties

const std::list<uint8_t> packet_manager::IDLE_PACKET = { 255, 0 };

// -------------------------------------------------------------- Public methods

bool packet_manager::popNextBit() {
    // We make sure there is still some complete date inside the packet queue,
    // by adding an IDLE packet to the queue if needed
    if (packetQueue.size() <= 1) {
        insertPacketDataToQueue(IDLE_PACKET);
    }

    // We remove the leading byte of the packet queue if we have read all its bits
    if (nextBitPosition > 7) {
        nextBitPosition = 0;
        packetQueue.pop_front();
    }

    // Retrieve the shift position by firstly increasing nextBitPosition
    int shift = 8 - ++nextBitPosition;

    // We retrieve the bit at the position `nextBitPosition`
    // where the Most Significant Bit is in position 0
    return (packetQueue.front() >> shift) & 1;
}

void packet_manager::insertPacketDataToQueue(std::list<uint8_t> packetData) {
    std::list<uint8_t> completePacket =
            buildCompletePacketData(packetData);

    insertCompletePacketToDataQueue(completePacket);
}

// --------------------------------------------------- Constructors / Destructor

packet_manager::packet_manager() {
    msbPosition = 0;
    nextBitPosition = 0;
}

packet_manager::~packet_manager() = default;

// ------------------------------------------------------------- Private methods

void packet_manager::insertCompletePacketToDataQueue(
        const std::list<uint8_t> &completePacket) {
    uint8_t i = 0;
    for (auto const &packetByte: completePacket) {
        // 1 - Fill the last byte in queue with the beginning of packetByte
        insertPacketByteBeginningToDataQueue(packetByte);

        // The delimiter between bytes is a 1 for the first and last packet byte,
        // ie after the first byte preamble and after the error byte
        bool delimiter = i == 0 || i == completePacket.size() - 1;

        // 2 - Add a new byte to the queue with the remaining bits of packetByte
        insertPacketByteEndingToDataQueue(packetByte, delimiter);

        msbPosition = (msbPosition + 1) % 8;
        i++;
    }
}

void packet_manager::insertPacketByteBeginningToDataQueue(uint8_t packetByte) {
    if (msbPosition == 0) {
        // The packetByte can be appended directly to the end of the queue
        // if the msb_position is equal to 0
        packetQueue.push_back(packetByte);
    } else {
        // Otherwise, we need to retrieve the last byte in the queue and
        // add to it the first part of packetByte
        uint8_t newLastByte =
                packetQueue.back() + (packetByte >> msbPosition);

        // The last byte is then replaced by newLastByte
        packetQueue.pop_back();
        packetQueue.push_back(newLastByte);
    }
}

void packet_manager::insertPacketByteEndingToDataQueue(
        uint8_t packetByte, bool delimiter) {
    // Create a new byte with the ending of packetByte, with a 0 delimiter
    uint8_t remainingBits = packetByte << (8 - msbPosition);

    remainingBits += delimiter << (7 - msbPosition);

    packetQueue.push_back(remainingBits);
}

std::ostream &
operator<<(std::ostream &outputStream, const packet_manager &packetManager) {
    // This will copy all the elements of the packet queue into the outputStream
    // by using an output stream iterator
    std::copy(packetManager.packetQueue.begin(),
              packetManager.packetQueue.end(),
              std::ostream_iterator<std::bitset<8>>(outputStream));

    return outputStream;
}
