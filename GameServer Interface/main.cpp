////////////////////////////////////////////////////
//	main.cpp
//	Main file for the client application
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#include <iostream>
#include "..\common\StreamSocket.h"
#include "..\common\sockglob.h"
#include "global.h"
#include "ClieFunc.h"
#include <windows.h>
#pragma comment(lib,"winmm.lib")
//////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
	
	
	//this bool to know if the Game Server Faild...
	bool GameServFaild=true;
	
	
	try {
		char buf[256];
		char StrIP[50];
		buf[0] = 0;
		int y=0,flag=0;
		
		
		cout << "Please Enter The Admin Password..."<<endl;
		cout << "> ";
		
		
		if(GetPassword()!=1)
		{
			cout<<"Wrong Password..."<<endl;
			cout<<"Press any key to exit"<<endl;
			getchar();
			exit(1);
		}
		int port;             //Port for listening.
		char *IPAdr;		  //IP addr' to connect to.
		
		IPAdr = new char[IPLEN];
		
		cout << "Game Serve Interface"<<endl;
		cout << "~~~~~~~~~~~~~~~~"<<endl;
		
		//get the port and the ip
		get_arguments(port,IPAdr,argc,argv);    //Get the port, and the ip address.
		
		cout <<endl<< "Using Port Number        : "<<port<<endl;
		cout << "Connecting to IP Address : "<<IPAdr<<endl<<endl;
		
		
		
		
		cout << "Welcome To Game Sarver Interface ..."<<endl<<endl;
		
		Reply reply;
		Login strct_login;
		StreamSocket socket;
		
		do{
			//choose one of these to register or logon....
			do{
				cout <<endl;
				cout << "Press one of these number: "<<endl;
				cout << "1) Remove User"<<endl;
				cout << "2) Report User"<<endl;
				cout << "3) List of Users"<<endl;
				cout << "4) Exit"<<endl;
				flushall();
				cin.getline(StrIP, 50, '\n');
				flag=StringToInt(StrIP);
				if (flag == 4)
					exit(1); // if presed 4 for exit
			}while(flag<1 || flag>3);
			
			// connect to Game Server
			socket.connect(IPAdr, port);
			
			itoa(flag+4,buf,10);
			//sending the option that he choose... to tell the game server what to do 
			socket.send( buf, sizeof(int));
			
			string login_users;
			int counter=1;
			
			switch (flag)
			{
			case 1:
				/////////////////////////////////////////////////////////////
				//Remove//
				/////////////////////////////////////////////////////////////
				
				//get the username and password and email for registration
				do{
					cout << "user name must be less than 13 char: "<<endl;
					cout << "Enter User Name: ";
					cin >> strct_login.username;
					cout<<endl;
				}while(strlen(strct_login.username) > 12 );
				
				//sending the registration as one package
				GameServFaild=true;
				socket.send( (char *)& strct_login, sizeof(strct_login));
				GameServFaild=false;
				//receve the answer as Reply package
				GameServFaild=true;
				socket.recv(buf,sizeof(Reply));
				GameServFaild=false;
				//convert  from char* to Reply package  
				reply = (struct Reply&) buf;
				
				//check the answer
				if(reply.status == OK)
				{
					cout<<"User "<<strct_login.username<<" removed successfuly"<<endl;
				}
				else
				{
					if(reply.status == 3)
					{
						cout << "User Name Does not Exist.."<< endl;
						break;
					}
					if(reply.status == 1)
					{
						cout << "Removing was Failed Try Again latter.."<< endl;
						cout << "The User is logon status"<< endl;
						break;
					}
				}
				break;
			case 2 :
				/////////////////////////////////////////////////////////////
				//Report//
				/////////////////////////////////////////////////////////////
				do{
					cout << "user name must be less than 13 char: "<<endl;
					cout << "Enter User Name: ";
					cin >> strct_login.username;
					cout<<endl;
				}while(strlen(strct_login.username) > 12 );
				
				GameServFaild=true;
				socket.send( (char *)&strct_login, sizeof(Login));
				GameServFaild=false;
				cout << "Cheking User Name..."<<endl;
				GameServFaild=true;
				socket.recv(buf,sizeof(Reply));
				GameServFaild=false;
				reply = (struct Reply&) buf;
				
				//cout << "Logon : " << reply.status << endl<< endl;
				
				if(reply.status == 1)
				{
					cout << "Fail To Connect to DataBase Server"<< endl;
					break;
				}
				if(reply.status == 3)
				{
					//cout << "There are no Connection with DataBase Server Try Again in few min..."<< endl;
					cout << "User Dose not Exist.."<< endl;
					break;
				}
				if(reply.status == 0)
				{
					cout<<endl;
					cout<<"User Name :"<<strct_login.username<<endl;
					cout<<"Number of Wins   :"<<reply.wins<<endl;
					cout<<"Number of Losses :"<<reply.loses<<endl;
					cout<<"Number of Equal  :"<<reply.equal<<endl;
					cout<<"Total of Games   :"<<reply.wins + reply.loses + reply.equal<<endl;
					cout<<"Rank             :"<<reply.rank<<endl;
				}
				
				break;
			case 3 :
				/////////////////////////////////////////////////////////////
				//List Of all Users//
				////////////////////////////////////////////////////////////
				
				do{
					GameServFaild=true;
					socket.recv(buf,14);
					GameServFaild=false;
		
					if(strcmp(buf,"EOF")==0)
						break;
					cout<<"User "<<counter<<"# :"<<buf<<endl;
					counter++;					
				}while(1);
				
				break;
				
			default:
				break;
				
				
				}
				cout << "Press Enter to exit"<<endl;
				flushall();
				cin.getline(StrIP, 50, '\n');
				exit(1);				
				
		}while(1);
			}catch (Socket::SocketException e) {
				cout << e.what() << std::endl;
				if(GameServFaild)
				{
					cout << "Sorry the Data Server was Failed some error was Occurred...";
					
				}
				cout << "Press Enter to exit"<<endl;;
				getchar();
			}
			return 0;
}