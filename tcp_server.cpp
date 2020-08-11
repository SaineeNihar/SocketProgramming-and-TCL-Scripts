#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<cstring>
#define PORT 9002
using namespace std;
int main()
{
	char server_msg[256]="you have reached to the server";
	int srv_socket=0;
	srv_socket = socket(AF_INET,SOCK_STREAM, 0);
	if (srv_socket < 0)
	{
	        printf("\n Socket creation error \n");
	        return -1;
	}
	struct sockaddr_in server_add;
	server_add.sin_family=  AF_INET;
        server_add.sin_port = htons(PORT);
        server_add.sin_addr.s_addr= INADDR_ANY;

	bind(srv_socket, (struct sockaddr *) &server_add, sizeof(server_add));
	
	listen(srv_socket, 3);

	int clnt_socket;
	
	clnt_socket=accept(srv_socket,NULL, NULL);
		if (clnt_socket < 0)
	{
	        printf("\n Error in building address \n");
	        return -1;
	}
	

	else printf("Connection accepted\n");
	char buffer[1024];
	 int sts = read( clnt_socket , buffer, 1024);
    if(sts<0){cout<<"error";}
   else{ cout<<endl<<buffer;}
/////////////////////////////////////////////////////////////////////	


string crc,msg=buffer,code=buffer;
	cout<<"Enter CRC Plynomial:= ";
	getline(cin,crc);
	
	for(int i=0;i<code.length()-crc.length()+1;)
	{
		for(int j=0;j<crc.length();j++)
		{
			code[i+j]=code[i+j]==crc[j]?'0':'1';	
		}
		for(;i<code.length() && code[i]!='1';i++);
	}
	cout<<endl<<"\t"<<code<<endl;
	string s=code.substr(code.length()-crc.length()+1);
	s[2]=1;
	for(int i =0;i<s.length();i++)
	{
		if(s[i]!='0')
		{
			cout<<"\a\a\a\a\aError in communication!!!";
			return 0;	
		}
	}
	cout<<"No Error in the msg\a\a\a";

//////////////////////////////////////////////////////////////////

//        getline(&hello,&bufsize,stdin);
	
	
	close(srv_socket);
	return 0;
}
