////////////////////////////////////////////////////
//	The NC functions implementation.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#include "..\common\StreamSocket.h"
//#include "SocketException.h"
#include "..\common\sockglob.h"

//This func' gets the initial arguments that contain the self port/ip adress.
bool get_arguments(int& port, char *IPAdr, int argc, char** argv){
	switch (argc){
	case 1:
		cout<<endl<<"Using DEFAULT Parametrs"<<endl<<"Usage : Client [PortNum] [IPAddress]"<<endl<<endl;
		port=DEFAULTSERVERPORT;
		strcpy(IPAdr,DEFAULTIP);
		break;
	case 2:
		port=atoi(argv[1]);
		strcpy(IPAdr,DEFAULTIP);
		break;
	case 3:
		port=atoi(argv[1]);
		strcpy(IPAdr,argv[2]);
		break;
	}
	return true;
}
