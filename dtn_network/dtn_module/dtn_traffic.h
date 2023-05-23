#ifndef __INET_DTN_TRAFFIC_H
#define __INET_DTN_TRAFFIC_H
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
namespace inet{
    class DtnTraffic : public OperationalBase, protected cListener{
    // self variables
    public:
        enum SelfMsgKinds {
            START = 1,
            SEND,
            STOP
        };
        cMessage* startMsg = nullptr;
        cMessage* stopMsg = nullptr;
        cMessage* sendMsg = nullptr;
        dtn* dtn_module = nullptr;
        std::string destAddress; // module name
        Ipv4Address destIpv4Address; // ipv4 address
        double startTime{};
        double stopTime{};
        double sendInterval{};

    public:
        DtnTraffic() = default;
        ~DtnTraffic() override;
        std::string getFullPath() const override { return cSimpleModule::getFullPath(); }
    public:
        int numInitStages() const override {return NUM_INIT_STAGES; }
        void initialize(int stage) override;
        void handleMessageWhenUp(cMessage* msg) override;
        Packet* createPacket();
        void sendPacket();
        Ipv4Address getIpv4Address();
    public:
        // lifecycle method
        bool isInitializeStage(int stage) override { return stage == INITSTAGE_LINK_LAYER; }
        bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_LINK_LAYER; }
        bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_LINK_LAYER; }
        void handleStartOperation(LifecycleOperation *operation) override;
        void handleStopOperation(LifecycleOperation *operation) override;
        void handleCrashOperation(LifecycleOperation *operation) override;

    };
}

#endif
