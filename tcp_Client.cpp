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
string strcvt(int i)
{
	string bits;
		for(int c=6;c>=0;c--)
		{
			int k=i>>c;
			if(k&1)
			{	bits+='1'; }
			else {bits+='0'; }	
		}
	return bits;
}
int main()
{

	int nw_socket;
	nw_socket=0;
	nw_socket = socket(AF_INET,SOCK_STREAM, 0);
	
	if (nw_socket < 0)
	{
	        printf("\n Socket creation error \n");
	        return -1;
	}

	struct sockaddr_in server_add;
	server_add.sin_family=  AF_INET;
    server_add.sin_port = htons(PORT);
    server_add.sin_addr.s_addr= INADDR_ANY;

	int sts= connect(nw_socket, (struct sockaddr *) &server_add, sizeof(server_add));
	if (sts<0)
	{ printf("\n Error in Making connection \n");}
	
/////////+++++Calculate CRC+++++/////////////////////
	string crc,msg;
	string code;

	cout<<"Enter CRC Plynomial:= ";
	getline(cin,crc);
	cout<<"\nEnter msg:= ";
	getline(cin,msg);
	cout<<"ASCII value";
	int len=msg.length(),crc_len=crc.length();
		string x;
		for(int i=0;i<msg.length();i++)
    	{ 
    		int ascii=int(msg[i]);
    		cout<<ascii<<endl;
			x+=strcvt(ascii);
			cout<<endl<<x<<endl;

    	}
	cout<<"Code is"<<x<<endl;
	code=x;
	//Appand N-1 Zeros
	for(int i=0;i<crc_len-1;i++)
	code+='0';
	cout<<"append code "<<code<<endl;
	for(int i=0;i<code.length()-crc_len+1;)
	{
		for(int j=0;j<crc_len;j++)
		{
			code[i+j]=code[i+j]==crc[j]?'0':'1';	
		}
		for(;i<code.length() && code[i]!='1';i++);
	}
	cout<<endl<<"\t"<<code<<endl;
	string c=code.substr(code.length()-crc_len+1);
	x+=c;
	cout<<"\nMessage to be send is := "<<x<<endl;
	
	
	
	
	
////////////////////


int leng=x.length();
	send(nw_socket , x.c_str() , leng , 0 );

	printf("msg sent successfully"); 
	close(nw_socket); 
	return 0;
}
