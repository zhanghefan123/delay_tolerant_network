//
// Created by zhf on 23-5-18.
//

#ifndef DELAYTOLERANTNETWORK_DTNCONST_H
#define DELAYTOLERANTNETWORK_DTNCONST_H
#include <string>
namespace inet{
    // dtn const variables
    // -------------------------------------------------------------------
    const std::string LOOPBACK_INTERFACE_NAME = "lo";
    const std::string DTN_START_MSG_NAME = "dtn_start_msg";
    const std::string CHECK_NEIGH_EXPIRE_MSG_NAME = "neighbor_expire_msg";
    const std::string CHECK_BUFFER_EXPIRE_MSG_NAME = "buffer_expire_msg";
    const std::string NEIGHBOR_DETECT_MSG_NAME = "neighbor_detect_msg";
    const std::string NEIGHBOR_EXCHANGE_MSG_NAME = "neighbor_exchange_msg";
    const std::string NEIGHBOR_SEND_PACKET_TIMER = "neighbor_send_packet_timer";

    const std::string PAR_NEIGHBOR_DETECTION_INTERVAL = "neighbor_detection_interval";
    const std::string PAR_NEIGHBOR_EXPIRATION_TIME = "neighbor_expiration_time";
    const std::string PAR_CHECK_NEIGHBOR_EXPIRATION_INTERVAL = "check_neighbor_expiration_interval";
    const std::string PAR_BUFFER_EXPIRATION_TIME = "buffer_expiration_time";
    const std::string PAR_CHECK_BUFFER_EXPIRATION_INTERVAL = "check_buffer_expiration_interval";
    const std::string PAR_NEIGHBOR_EXCHANGE_INTERVAL = "neighbor_exchange_interval";
    const std::string PAR_SEND_PACKET_INTERVAL = "send_packet_interval";

    const std::string NEIGHBOR_DETECT_PACKET_NAME = "neighbor_detect_packet";
    const std::string NEIGHBOR_ID_DB_PACKET_NAME = "neighbor_id_db_packet";
    const std::string NEIGHBOR_REAL_PACKET_REQUEST_NAME = "neighbor_real_packet_request";
    const std::string NEIGHBOR_REAL_PACKET_NAME = "neighbor_real_packet";


    const std::string INTERFACE_TABLE_NAME = "interfaceTable";
    // -------------------------------------------------------------------
}
#endif //DELAYTOLERANTNETWORK_DTNCONST_H
