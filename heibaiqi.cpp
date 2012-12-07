#include<iostream>
#include "common.h"

using namespace std;

Chess qipan[8][8]={};
char hang,lie;

void printqizi()
{
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			switch(qipan[i][j])
			{
				case NUL:
					cout<<"  ";
					break;
				case BLACK:
					cout<<"�� ";
					break;
				case WHITE:
					cout<<"�� ";
					break;
			}
		}
		cout << endl;
	}
}

void printqipan()
{
	cout<<"    1   2   3   4   5   6   7   8  "<<endl;
	cout<<"  �X �T �j �T �j �T �j �T �j �T �j �T �j �T �j �T �["<<endl;
	//	for(int i=0;i<8;i++)
	cout<<" A�U   �U   �U   �U   �U   �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" B�U   �U   �U   �U   �U   �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" C�U   �U   �U   �U   �U   �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" D�U   �U   �U   �U �� �U �� �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" E�U   �U   �U   �U �� �U �� �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" F�U   �U   �U   �U   �U   �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" G�U   �U   �U   �U   �U   �U   �U   �U   �U"<<endl;
	cout<<"  �d �T �p �T �p �T �p �T �p �T �p �T �p �T �p �T �g"<<endl;
	cout<<" H�U   �U   �U   �U   �U   �U   �U   �U   �U"<<endl;
	cout<<"  �^ �T �m �T �m �T �m �T �m �T �m �T �m �T �m �T �a"<<endl;
}

void shuruzuobiao()
{
	while (1){
		cin>>hang>>lie;
		if(hang>='A'&&hang<='H'&&lie>='1'&&lie<='8')
		{
			cout<<"zhengque"<<endl;
			return;
		}
		else{ 
			cout<<"����������Ч�����������룺";
		}
	}
}

int main ()
{
	qipan[3][3]=BLACK;
	qipan[3][4]=WHITE;
	qipan[4][3]=BLACK;
	qipan[4][4]=WHITE;
	printqipan();
	Chess thischess=BLACK;
	while (1){
		shuruzuobiao();
		reverse(qipan,qipan,hang-'A',lie-'1',thischess);
		thischess=-thischess;
		printqizi();
	}
	return 0;
}

