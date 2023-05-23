#include "inet/projects/dtn_network/dtn_module/dtn_traffic.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicPacket.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/InterfaceTable.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"
namespace inet{
    Define_Module(DtnTraffic);

    DtnTraffic::~DtnTraffic() {
        cancelAndDelete(startMsg);
        cancelAndDelete(stopMsg);
        cancelAndDelete(sendMsg);
    }

    Ipv4Address DtnTraffic::getIpv4Address()
    {
        auto * table = dynamic_cast<InterfaceTable*>(this->getParentModule()->
        getParentModule()->
        getSubmodule(this->destAddress.c_str())
        ->getSubmodule("interfaceTable"));
        // traverse the interface and get the ipv4 address
        for(int i = 0; i < table->getNumInterfaces(); i++){
            NetworkInterface * entry = table->getInterface(i);
            if(entry->isLoopback())
                continue;
            if(entry->isUp()){
                return entry->getProtocolData<Ipv4InterfaceData>()->getIPAddress();
            }
        }
        return {};
    }

    void DtnTraffic::handleMessageWhenUp(omnetpp::cMessage *msg) {
        if(msg->isSelfMessage()){
            if(msg->getKind() == START){
                if(std::strcmp(this->destAddress.c_str(), "") != 0){
                    destIpv4Address = this->getIpv4Address();
                }
                std::cout << this->getFullPath() << " start" << std::endl;
                scheduleAt(simTime(), sendMsg);
            } else if(msg->getKind() == SEND){
                this->sendPacket();
                scheduleAt(simTime() + this->sendInterval, sendMsg);
            }
            else if(msg->getKind() == STOP){
                this->handleStopOperation(nullptr);
            } else {
                std::cout << "unknown self message kind" << std::endl;
            }
        }
    }

    Packet* DtnTraffic::createPacket(){
        auto *pk = new Packet();
        // set name
        pk->setName(NEIGHBOR_REAL_PACKET_NAME.c_str());
        std::string uuid = dtn::generateUuid();
        // add application packet
        // here we need to create a EpidemicHeader
        const auto& epidemicHeader = makeShared<EpidemicHeader>();
        epidemicHeader->setType(EpidemicPacket::Type::NEIGHBOR_REAL_PACKET_TYPE); // it represents that we sent real packet
        epidemicHeader->setChunkLength(B(100));
        epidemicHeader->setUuid(uuid.c_str());
        epidemicHeader->setDestAddr(this->destIpv4Address);
        pk->insertAtBack(epidemicHeader);
        return pk;
    }

    void DtnTraffic::sendPacket() {
        int upNeighborCount = 0;
        // we create packet
        Packet* pk = this->createPacket();
        // peek EpidemicHeader to get uuid
        auto epidemicHeader = pk->peekAtFront<EpidemicHeader>();
        std::string uuid = epidemicHeader->getUuid();
        // store the packet in the buffer first - then we gonna send the packet in this buffer
        this->dtn_module->packets_buffer[uuid] = std::make_pair(pk, simTime());
        this->dtn_module->packetIds.insert(uuid);
    }

    void DtnTraffic::initialize(int stage) {
        OperationalBase::initialize(stage);
        if(stage == INITSTAGE_LOCAL){
            this->startTime = par("startTime").doubleValue();
            this->stopTime = par("stopTime").doubleValue();
            this->sendInterval = par("sendInterval").doubleValue();
            this->destAddress = par("destAddress").stringValue();
        }
    }

    void DtnTraffic::handleStartOperation(inet::LifecycleOperation *operation) {
        if(this->startTime < this->stopTime){
            std::cout << this->getFullPath() << " handle start operation" << std::endl;
            this->startMsg = new cMessage("startTimer");
            this->startMsg->setKind(START);
            scheduleAt(simTime(), startMsg);
            this->stopMsg = new cMessage("stopTimer");
            this->stopMsg->setKind(STOP);
            scheduleAt(simTime() + this->stopTime, stopMsg);
            this->sendMsg = new cMessage("sendTimer");
            this->sendMsg->setKind(SEND);
            this->dtn_module = dynamic_cast<dtn*>(this->getParentModule()->getSubmodule("dtn"));
        }
    }

    void DtnTraffic::handleCrashOperation(inet::LifecycleOperation *operation) {

    }

    void DtnTraffic::handleStopOperation(inet::LifecycleOperation *operation) {
        std::cout << this->getFullPath() << " handle stop operation" << std::endl;
        if(this->sendMsg->isScheduled()){
            cancelEvent(this->sendMsg);
        }
    }
}
