package inet.projects.dtn_network.dtn_module;
simple DtnTraffic{
	parameters:
	    string destAddress = default(""); // dest ip
	    volatile double sendInterval @unit(s) = default(0.5s); // packet send interval
	    double startTime @unit(s) = default(0s);
	    double stopTime @unit(s) = default(0s);
}