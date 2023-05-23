#ifndef __INET_EPIDEMIC_PACKET_TYPE_H
#define __INET_EPIDEMIC_PACKET_TYPE_H

namespace inet{
    class EpidemicPacket{
        public:
            // definition of the epidemic packet type
            enum Type{
                NEIGHBOR_DETECTION_PACKET_TYPE = 0,
                NEIGHBOR_ID_DB_PACKET_TYPE = 1,
                NEIGHBOR_REAL_PACKET_REQUEST_TYPE = 2,
                NEIGHBOR_REAL_PACKET_TYPE = 3,
            };
            // convert the packet type to string
            static const char* convertPacketTypeToString(Type packetType);
    };
}

#endif // ifndef __INET_EPIDEMIC_PACKET_TYPE_H