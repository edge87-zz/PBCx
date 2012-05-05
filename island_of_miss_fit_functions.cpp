void request_switch_thread(void*);

sf::Thread tRequestSwitch(&request_switch_thread);
tRequestSwitch.Terminate();
tRequestSwitch.Launch();

void request_switch_thread(void* none){
	sf::Sleep(2.0f);	//sleep because board has too stablize
	while(true){
		//sf::Sleep(0.004f);
		sf::Sleep(.1f);
		serialPortM.Lock();
		req_switches();
		serialPortM.Unlock();
		//sf::Sleep(0.004f);
		sf::Sleep(.1f);
		serialPortM.Lock();
		req_cabinet();
		serialPortM.Unlock();
	};
};

void req_switches(void){
	unsigned char reqCode = OPC_RQSWITCH;
	int written = 0;
	unsigned char* sendReq = &reqCode;

	written = write(fd, sendReq, 1);

	reqCode = OPC_EOL;
	sendReq = &reqCode;
	written += write(fd, sendReq, 1);

	if (written <= 0){
		//return 1;
		std::cout<< "Sending Request for Playfield Switches FAILED\n";
		return;
	};

	std::cout << "Sent Playfield Switch Request OK\n";
	return;
};

void req_cabinet(void){
	unsigned char reqCode = OPC_RQCABINET;
	int written = 0;
	unsigned char* sendReq = &reqCode;

	written = write(fd, sendReq, 1);

	reqCode = OPC_EOL;
	sendReq = &reqCode;
	written += write(fd, sendReq, 1);

	if (written <= 0){
		//return 1;
		std::cout<< "Sending request for Cabinet Switches FAILED\n";
	};

	std::cout << "Sent Cabinet Request ok\n";

	return;
};
