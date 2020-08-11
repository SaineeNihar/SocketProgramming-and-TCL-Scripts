#include<iostream>
using namespace std;
#define blk 64

void keygen(int key[],int k[])
{
	int permute1[]= {56,48,40,32,24,16,8,0,57,49,41,33,25,17,
							9,1,58,50,42,34,26,18,10,2,59,51,43,35,
							62,54,46,38,30,22,14,6,61,53,45,37,29,21,
							13,5,60,52,44,36,28,20,12,4,27,19,11,3};
	for(int i=0;i<56;i++)
		k[i]=key[permute1[i]];

}
void keyshift(int k[],int kout[],int c)
{
/////Key Bit Shift////////////////////	
	while(c--)
	{	int temp=k[0],i;
		for(i=0;i<27;i++)
			k[i]=k[i+1];
		k[i]=temp;
		temp=k[28];
		for(i=28;i<55;i++)
			k[i]=k[i+1];	
		k[i]=temp;
	}
	int permute2[]= {13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,
					3,25,7,15,6,26,19,12,1,40,51,30,36,46,
					54,29,39,50,44,32,47,43,48,38,55,33,52,
					45,41,49,35,28,31};
	for(int i=0;i<48;i++)
		kout[i]=k[permute2[i]];	
}
/////////////////////Feistal Structure/////////////////////////
void feistal(int pt[],int kout[]) 
{
////////Expanstion
	int m=blk/2;
	int le[m],re[m];
	for(int i=0;i<blk;i++)
	{
		if(i<m)
		le[i]=pt[i];
		else	
		re[i%m]=pt[i];
	}
	int exp[48];
	 int ep[48]={ 32,1,2,3,4,5,4,5, 
			        6,7,8,9,8,9,10,11, 
        			12,13,12,13,14,15,16,17, 
			        16,17,18,19,20,21,20,21, 
        			22,23,24,25,24,25,26,27, 
        			28,29,28,29,30,31,32,1 
    			}; 
    for(int i=0;i<48;i++)
		exp[i]=re[ep[i]-1];
////////////////////////////////////////////	
	for(int i=0;i<48;i++)
		exp[i]=kout[i]^exp[i];		
///////////////////////////////////////////
	int s[8][4][16]= 
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
  
  
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }}; 
	int rout[32];	
	for(int i=47,j=7,k=31;i>=0;)
	{
					
		int row=2*exp[i-5]+exp[i];				
		int col=8*exp[i-4]+4*exp[i-3]+2*exp[i-2]+exp[i-1];	
		int temp=s[j][row][col];	
		int c=0;
		while(c<4)
		{
			rout[k--]=temp%2;	
			temp/=2;
			c++;
		}	
		i=i-6;
		j--;//sbox;
   	}
	int p[]={15,6,19,20,28,11,27,16,0,14,22,25,4,17,30,9,1,7,23,13,31,26,2,8,18,12,29,5,21,10,3,24};
	int rout1[32];
	for(int i=0;i<32;i++)
		rout1[i]=rout[p[i]];
		
	for(int i=0;i<32;i++)
		rout1[i]=rout1[i]^le[i];

	for(int i=0;i<64;i++)
	{
		if(i<32)
			pt[i]=re[i];
		else
			pt[i]=rout1[i%32];
	}
	
}
/////////////////////////
void dfeistal(int pt[],int kout[]) 
{
////////Expanstion
	int m=blk/2;
	int le[m],re[m];
	for(int i=0;i<blk;i++)
	{
		if(i<m)
		re[i]=pt[i];
		else	
		le[i%m]=pt[i];
	}
	int exp[48];
	 int ep[48]={ 32,1,2,3,4,5,4,5, 
			        6,7,8,9,8,9,10,11, 
        			12,13,12,13,14,15,16,17, 
			        16,17,18,19,20,21,20,21, 
        			22,23,24,25,24,25,26,27, 
        			28,29,28,29,30,31,32,1 
    			}; 
    for(int i=0;i<48;i++)
		exp[i]=re[ep[i]-1];
////////////////////////////////////////////	
	for(int i=0;i<48;i++)
		exp[i]=kout[i]^exp[i];		
///////////////////////////////////////////
	int s[8][4][16]= 
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
  
  
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }}; 
	int rout[32];	
	for(int i=47,j=7,k=31;i>=0;)
	{
					
		int row=2*exp[i-5]+exp[i];				
		int col=8*exp[i-4]+4*exp[i-3]+2*exp[i-2]+exp[i-1];	
		int temp=s[j][row][col];	
		int c=0;
		while(c<4)
		{
			rout[k--]=temp%2;	
			temp/=2;
			c++;
		}	
		i=i-6;
		j--;//sbox;
   	}
	int p[]={15,6,19,20,28,11,27,16,0,14,22,25,4,17,30,9,1,7,23,13,31,26,2,8,18,12,29,5,21,10,3,24};
	int rout1[32];
	for(int i=0;i<32;i++)
		rout1[i]=rout[p[i]];
		
	for(int i=0;i<32;i++)
		le[i]=rout1[i]^le[i];

	for(int i=0;i<64;i++)
	{
		if(i<32)
			pt[i]=le[i];
		else
			pt[i]=re[i%32];
	}
	
}

///////////////////////////

int main()
{

	int pt1[]={0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,1,1,0};
int key[]={1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1};
	int pt[64];
	int ip[64]=  
    {   58,50,42,34,26,18,10,2, 
        60,52,44,36,28,20,12,4, 
        62,54,46,38,30,22,14,6, 
        64,56,48,40,32,24,16,8, 
        57,49,41,33,25,17,9,1, 
        59,51,43,35,27,19,11,3, 
        61,53,45,37,29,21,13,5, 
        63,55,47,39,31,23,15,7 
    }; 
     int fp[64]=  
    {   40,8,48,16,56,24,64,32, 
        39,7,47,15,55,23,63,31, 
        38,6,46,14,54,22,62,30, 
        37,5,45,13,53,21,61,29, 
        36,4,44,12,52,20,60,28, 
        35,3,43,11,51,19,59,27, 
        34,2,42,10,50,18,58,26, 
        33,1,41,9,49,17,57,25 
    }; 
    cout<<"Plain Text\n";
    for(int i=0;i<64;i++)
		cout<<pt1[i];  
	cout<<"\nkey\n";
	for(int i=0;i<64;i++)
		cout<<key[i];   
	for(int i=0;i<64;i++)
		pt[i]=pt1[ip[i]-1];
	int k[56],kout[48];
	int kout1[48],kout2[48],kout3[48],kout4[48],kout5[48],kout6[48],kout7[48],kout8[48];
	int kout9[48],kout10[48],kout11[48],kout12[48],kout13[48],kout14[48],kout15[48],kout16[48];
	keygen(key,k);
////////////Round 1////////////////
	keyshift(k,kout,1);
	for(int i=0;i<48;i++)
	kout1[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 1 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout1[i];
	}	
	cout<<endl;
////////////Round 2////////////////
	keyshift(k,kout,1);
	for(int i=0;i<48;i++)
		kout2[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 2 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout2[i];
	}	
	cout<<endl;
////////////Round 3////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
	kout3[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 3 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout3[i];
	}	
	cout<<endl;
////////////Round 4////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
		kout4[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 4 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout4[i];
	}	
	cout<<endl;
////////////Round 5////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
	kout5[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 5 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout5[i];
	}	
	cout<<endl;

////////////Round 6////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
		kout6[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 6 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout6[i];
	}	
	cout<<endl;
////////////Round 7////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
	kout7[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 7 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout7[i];
	}	
	cout<<endl;
////////////Round 8////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
		kout8[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 8 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout8[i];
	}	
	cout<<endl;
////////////Round 9////////////////
	keyshift(k,kout,1);
	for(int i=0;i<48;i++)
	kout9[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 9 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout9[i];
	}	
	cout<<endl;
////////////Round 10////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
		kout10[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 10 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout10[i];
	}	
	cout<<endl;
////////////Round 11////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
	kout11[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 11 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout11[i];
	}	
	cout<<endl;
////////////Round 12////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
		kout12[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 12 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout12[i];
	}	
	cout<<endl;
////////////Round 13////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
	kout13[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 13 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout13[i];
	}	
	cout<<endl;
////////////Round 14////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
		kout14[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 14 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout14[i];
	}	
	cout<<endl;
////////////Round 15////////////////
	keyshift(k,kout,2);
	for(int i=0;i<48;i++)
	kout15[i]=kout[i];
	feistal(pt,kout);
	cout<<"\nRound 15 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout15[i];
	}	
	cout<<endl;
////////////Round 16////////////////
	keyshift(k,kout,1);
	for(int i=0;i<48;i++)
		kout16[i]=kout[i];
	feistal(pt,kout); 
	cout<<"\nRound 16 output and Key"<<endl;
	for(int i=0;i<blk;i++)
	{	
		cout<<pt[i]<<"";
	}	
	cout<<"\t";
	for(int i=0;i<48;i++)
	{	
		cout<<kout16[i];
	}	
	cout<<endl;
	int pf[blk];
	dfeistal(pt,kout16);
	dfeistal(pt,kout15);
	dfeistal(pt,kout14);
	dfeistal(pt,kout13);
	dfeistal(pt,kout12);
	dfeistal(pt,kout11);
	dfeistal(pt,kout10);
	dfeistal(pt,kout9);
	dfeistal(pt,kout8);
	dfeistal(pt,kout7);
	dfeistal(pt,kout6);
	dfeistal(pt,kout5);
	dfeistal(pt,kout4);
	dfeistal(pt,kout3);
	dfeistal(pt,kout2);
	dfeistal(pt,kout1);
	cout<<"\nplaintext1"<<endl;
	for(int i=0;i<64;i++)
	{
		pt1[ip[i]-1]=pt[i];
		cout<<pt1[i];	
	}
	cout<<endl;	
///////////////////////////////////	
	
	cout<<endl;
return 0;
}
