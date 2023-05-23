#include "inet/projects/dtn_network/dtn_packets/EpidemicPacket.h"
namespace inet{
    const char* EpidemicPacket::convertPacketTypeToString(Type packetType){
        switch(packetType){
            case NEIGHBOR_DETECTION_PACKET_TYPE:
                return "NEIGHBOR_DETECTION_PACKET_TYPE";
            default:
                return "UNKNOWN_PACKET_TYPE";
        }
    }
}