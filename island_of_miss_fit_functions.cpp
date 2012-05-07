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

void videokiller(void){
	App.Display();
	sf::Event Event;
	while (App.GetEvent(Event))
	{
	    // Window closed
	    if (Event.Type == sf::Event::Closed){
	        App.Close();
	    };
	    // Escape key pressed
	    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
	    	App.Close();
	    };
	};
};

void load_fonts(void){
	if (!mono.LoadFromFile("/home/teamheck/exec/media/font/mono.ttf")){
	    std::cout << "Failed to load mono font\n";
	};

	if (!trek.LoadFromFile("/home/teamheck/exec/media/font/StarNext.ttf")){
	    std::cout << "Failed to load Star Trek font.\n";
	};
};

tReadSwitch.Terminate();

playfieldText.SetText(sswitches);
cabinetText.SetText(scabinet);
App.Draw(sBackground);
App.Draw(playfieldText);
App.Draw(cabinetText);

sf::Thread tReadSwitch(&read_switches_thread);

sf::Image background;

background.LoadFromFile("/home/teamheck/exec/media/image/background.png");
sBackground.SetImage(background);
sBackground.SetPosition(0.f, 0.f);
App.Draw(sBackground);


tReadSwitch.Launch();
