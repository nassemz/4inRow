///////////////////////////////////////////////////
//	main.cpp
//	Main file for the client application
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#include <iostream>
#include "..\common\StreamSocket.h"
#include "..\common\sockglob.h"
#include "Game.h"
#include "ClieFunc.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
//////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
	
	int port;             //Port for listening.
	char *IPAdr;		  //IP addr' to connect to.
	
	IPAdr = new char[IPLEN];
	
	cout << "Client Interface"<<endl;
	cout << "~~~~~~~~~~~~~~~~"<<endl;
	
	//get the port and the ip
	get_arguments(port,IPAdr,argc,argv);    //Get the port, and the ip address.
	
	cout <<endl<< "Using Port Number        : "<<port<<endl;
	cout << "Connecting to IP Address : "<<IPAdr<<endl<<endl;

	//this bool to know if the Game Server Faild...
	bool GameServFaild=true;
	
	
	try {
		char buf[256];
		char StrIP[50];
		buf[0] = 0;
		int y=0,flag=0;

		cout << "Welcome To '4 in Row' Game To join us Only Register with us then logon ..."<<endl<<endl;

		Reply reply;
		Login strct_login;
		StreamSocket socket;
		
		do{
			//choose one of these to register or logon....
			do{
				cout <<endl;
				cout << "Press one of these number: "<<endl;
				cout << "1) Registration"<<endl;
				cout << "2) Login"<<endl;
				cout << "3) Report"<<endl;
				cout << "4) Exit"<<endl;
				cout << "> ";
				flushall();
				cin.getline(StrIP, 50, '\n');
				flag=StringToInt(StrIP);
				if (flag == 4)
					exit(1); // if presed 4 for exit
			}while(flag<1 || flag>3);
			
			// connect to Game Server
			socket.connect(IPAdr, port);
			
			itoa(flag,buf,10);
			//sending the option that he choose... to tell the game server what to do 
			socket.send( buf, sizeof(int));
			
			switch (flag)
			{
			case 1:
				/////////////////////////////////////////////////////////////
				//Registration//
				/////////////////////////////////////////////////////////////
				Registration strct_player;
				
				//get the username and password and email for registration
				do{
					cout << "user name must be less than 13 char: "<<endl;
					cout << "Enter User Name: ";
					cin >> strct_player.username;
					cout<<endl;
					if(strcmp(strct_player.username,"EOF")==0)
						cout<<"Name EOF illigal Name plz type some one else..."<<endl<<endl;

				}while(strlen(strct_player.username) > 12 || strcmp(strct_player.username,"EOF")==0 );
				//get the password
				do{
					cout << "password name must be less than 13 char: "<<endl;
					cout << "Enter Password: ";
					cin >> strct_player.password;
					cout<<endl;
				}while(strlen(strct_player.password) > 12 );
				//get the email
				do{
					cout << "email name must be less than 31 char: "<<endl;
					cout << "Enter Your Email: ";
					cin >> strct_player.email;
					cout<<endl;
				}while(strlen(strct_player.email) > 30 );
				
				//sending the registration as one package
				GameServFaild=true;
				socket.send( (char *)& strct_player, sizeof(strct_player));
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
					cout<<"User Registration Success"<<endl;
					cout<<"User : "<<strct_player.username<<endl;
					cout<<"Password : "<<strct_player.password<<endl;
					cout<<"Email : "<<strct_player.email<<endl;
					cout<<"Wins : "<<reply.wins<<endl;
					cout<<"Loses : "<<reply.loses<<endl;
					cout<<"Equal : "<<0<<endl;
					cout<<"Rank : "<<reply.rank<<endl;
				}
				else
				{
					if(reply.status == 2)
					{
						//cout << "There are no Connection with DataBase Server Try Again in few min..."<< endl;
						cout << "User Name Already Exist.."<< endl;
						break;
					}
					if(reply.status == 1)
					{
						//cout << "There are no Connection with DataBase Server Try Again in few min..."<< endl;
						cout << "Registration was Failed Try Again latter.."<< endl;
						break;
					}
				}
				break;
				/////////////////////////////////////////////////////////////
				//Logon//
				/////////////////////////////////////////////////////////////
			case 2:
				//get the username and password for login
				do{
					cout << "user name must be less than 13 char: "<<endl;
					cout << "Enter User Name: ";
					cin >> strct_login.username;
					cout<<endl;
				}while(strlen(strct_login.username) > 12 );
				
				do{
					cout << "password name must be less than 13 char: "<<endl;
					cout << "Enter Password: ";
					cin >> strct_login.password;
					cout<<endl;
				}while(strlen(strct_login.password) > 12 );
				



				//sending the login as one package
				socket.send( (char *)&strct_login, sizeof(Login));
				cout << "Cheking User Name & Password..."<<endl;
				//receve the answer as Reply package
				socket.recv(buf,sizeof(Reply));
				//convert  from char* to Reply package  
				reply = (struct Reply&) buf;
								
				if(reply.status == 4)//Invalid Password
				{
					cout << "Invalid Password"<< endl;
					break;
				}
				if(reply.status == 1)//Fail
				{
					cout << "Fail To Connect to DataBase Server"<< endl;
					break;
				}
				if(reply.status == 3)//User Dose not Exist
				{
					cout << "User Dose not Exist.."<< endl;
					break;
				}
				//OK but his status on logon
				if((reply.status == 0) && (reply.stonoff == YES) )
				{
					cout<<endl;
					cout<<"You are logon right now"<<endl;
					exit(1);
				}
				if(reply.status == 0 && (reply.stonoff == NO) )//OK
				{
					
					cout << "Waiting For Connecting to another user.."<< endl;
					Game Gam_m;

					GameServFaild=true;
					socket.recv(buf, 4);
					GameServFaild=false;
					Gam_m.SetFirst_Type(buf[0]);
					
					GameServFaild=true;
					socket.recv(buf, 4);
					GameServFaild=false;
					Gam_m.SetSecond_Type(buf[0]);

					cout<< "Welcome To -- Game ..."<<endl<<endl;
					Gam_m.PrintGame();
					char buffer[10];
					while (1)
					{
						flushall();

						//receving msg one of these..
						//1) "go" to begin 
						//2) "win"or "los" or "eql" finishing game and telling client that hee win or loss or eqaul
						//3) number to insert to the array from the second player
						GameServFaild=true;
						socket.recv(buf, 4);
						GameServFaild=false;

						if(strcmp(buf,"go")!=0 && strcmp(buf,"win")!=0 && strcmp(buf,"los")!=0 && strcmp(buf,"eql")!=0)
						{
							Gam_m.Insert(StringToInt(buf),2);
							PlaySound("C:\\WINDOWS\\MEDIA\\Windows XP Balloon.wav", NULL, SND_SYNC);
						}
						
						if(strcmp(buf,"win")==0)
						{
							cout<<endl<<"Congratiolations you Won..."<<endl;
							PlaySound("C:\\WINDOWS\\MEDIA\\tada.wav", NULL, SND_SYNC);
    						Sleep(50);
							cout << "Press any Enter to exit";
							flushall();
							cin.getline(StrIP, 50, '\n');
							exit(1);
							
						}
						if(strcmp(buf,"los")==0)
						{
							socket.recv(buf, 4);
							Gam_m.Insert(StringToInt(buf),2);
							cout<<endl<<"Sorry you Loss Try Again..."<<endl;
							PlaySound("C:\\WINDOWS\\MEDIA\\tada.wav", NULL, SND_SYNC);
							Sleep(50);
							cout << "Press any Enter to exit";
							flushall();
							cin.getline(StrIP, 50, '\n');
							exit(1);
						}
						if(strcmp(buf,"eql")==0)
						{
							socket.recv(buf, 4);
							Gam_m.Insert(StringToInt(buf),2);
							cout<<endl<<"You got a Teko..."<<endl;
							PlaySound("C:\\WINDOWS\\MEDIA\\tada.wav", NULL, SND_SYNC);
							Sleep(50);
							cout << "Press any Enter to exit";
							flushall();
							cin.getline(StrIP, 50, '\n');
							exit(1);
						}
						do{
							do{
								
								cout << "Insert Column:";
								flushall();
								cin.getline(StrIP, 50 , '\n' );
								flushall();
								y=StringToInt(StrIP);
								
								
							}while(y<1 || y>Col);			//getline
							
						}while(Gam_m.Insert(y,1)==false);
						PlaySound("C:\\WINDOWS\\MEDIA\\Windows XP Balloon.wav", NULL, SND_SYNC);
						itoa (y,buffer,10);
						GameServFaild=true;
						socket.send( buffer , 4 );
						GameServFaild=false;
					}					
				}
				
				break;
				/////////////////////////////////////////////////////////////
				//Report//
				/////////////////////////////////////////////////////////////
			case 3:
				do{
					cout << "user name must be less than 13 char: "<<endl;
					cout << "Enter User Name: ";
					cin >> strct_login.username;
					cout<<endl;
				}while(strlen(strct_login.username) > 12 );
				
				do{
					cout << "password name must be less than 13 char: "<<endl;
					cout << "Enter Password: ";
					cin >> strct_login.password;
					cout<<endl;
				}while(strlen(strct_login.password) > 12 );
				
				GameServFaild=true;
				socket.send( (char *)&strct_login, sizeof(Login));
				GameServFaild=false;
				cout << "Cheking User Name & Password..."<<endl;
				GameServFaild=true;
				socket.recv(buf,sizeof(Reply));
				GameServFaild=false;
				reply = (struct Reply&) buf;
				
				//cout << "Logon : " << reply.status << endl<< endl;
				
				if(reply.status == 4)
				{
					cout << "Invalid Password"<< endl;
					break;
				}
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
					cout << "Sorry the Game-Server was Failed some error was Occurred...";
					cout<<endl<<"You got a Teko..."<<endl;
					
				}
				cout << "Press Enter to exit"<<endl;;
				getchar();
			}
			return 0;
}