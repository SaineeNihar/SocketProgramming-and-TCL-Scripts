#include<iostream>
#include<omp.h>
#include<string.h>
using namespace std;

int strlen(unsigned char m[])
{
	int n=0;
	while(m[n++]!='\0');
	return n;
}
void ksa(char k[],int s[])
{
	int i;

	for(i=0;i<256;i++)
		s[i]=i;
	int j=0,it;


	for(it=0;it<256;it++)
	{
		j=(j+s[it]+k[it%strlen(k)])%256;
		int temp=s[it];
		s[it]=s[j];
		s[j]=temp;
	}
	
}
void prg(int s[],unsigned char msg[],unsigned char c[])
{
	int i=0,j=0,key=-1;
	int size=strlen(msg);
	for(int k=0;k<size;k++)
	{
		i=(i+1)%256;
		j=(j + s[i])%256;	
		int temp=s[i];
		s[i]=s[j];
		s[j]=temp;
		key=s[(s[i] + s[j])%256];
		c[k]=key^(int)msg[k];	
	}
	cout<<endl;
}
int main()
{
	int s[256];
	char k[256];
	cout<<"Enter Key\n";
	cin>>k;	
	ksa(k,s);
	cout<<"\nEnter msg\n";
	unsigned char msg[1000];
	cin>>msg;
	int len=strlen(msg);
////Encryption/////////////////////////
	unsigned char c[len];
	prg(s,msg,c);
	cout<<"\ncipher is\n";
	for(int i=0;i<len;i++)
	cout<<(int)c[i]<<" ";
	cout<<endl;
////Decryption is//////////////
	ksa(k,s);
	prg(s,c,msg);
	cout<<"Decoded msg is\n";
	cout<<msg;
	cout<<endl;
	return 0;
}	
