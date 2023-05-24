package inet.projects.dtn_network.dtn_module;


simple dtn{
    parameters:
        double neighbor_detection_interval @unit(s) = default(5s);
    	double neighbor_expiration_time @unit(s) = default(20s);
    	double check_neighbor_expiration_interval @unit(s) = default(10s);
    	double buffer_expiration_time @unit(s) = default(50s);
    	double check_buffer_expiration_interval @unit(s) = default(5s);
    	double neighbor_exchange_interval @unit(s) = default(5s);
    	double send_packet_interval @unit(s) = default(0.5s);
	
	gates:
	    input ipIn;
        output ipOut;
}