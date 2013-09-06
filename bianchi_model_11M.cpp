#include <cmath>
#include <string>       // for strings
#include <iostream>     // for I/O
#include <fstream>      // for file I/O
#include <iomanip>      // for setw()
#include <cstdlib>      // for exit()
#include <vector>
#include <set>
#include <sstream>

using namespace std;
/*
-Throughput is computed according to the paper "Saturation throughput analysis in error prone 802.11 wireless netwrks"
-The Bisection method is applied here
*/


double eps=0.00001;

double pL=0.0;  
double pR=1.2;
double pM=0.0001;

//double taux=0.01;


double p=0.0;

float diff=0.0;

int N =0;			//Nbre of clients covers by an AP

int m=5;		//the max nbre of backoff

double taux=0;
//double p=0;

double Ptr=0;
double Ps=0;
double Ts=0;
double Tc=0;
double throughput=0;
////////////////////////////////Parametres for 1Mps and 2Mbps///////////////////

// int CW=32;		//the min contention windo
// double SIFS=28;//e-6;	//SIFS
// double DIFS=128;//e-6;	//DIFS
// double rho=50;//e-6;	//Slot time

////////////////////////////Parametres de 802.11b/////////////////
double SIFS=10;//e-6;	//SIFS
double rho=20;//e-6;	//Slot time
double DIFS=128;//e-6;	//DIFS
int CW=32;		//the min contention windo
double br=11e+6;		//channel bit rate
double CRbr=1e6;



double delta=1e-6;	//propagation time

//double PktPld=1023*8;	//Pkt Payload en bits	==> débit de 6.26 Mbps pour 3 Mobiles 

double PktPld=1162*8;	//Pkt Payload en bits	==> débit de 6.26 Mbps pour 3 Mobiles 

double MAC_H=272;	//MAC Header bits
double PHY_H=128;	//PHY Header bits



double L=((PktPld+MAC_H)/br)*1e6;// average paket size in µsecond
 
double H=(PHY_H/CRbr)*1e6;//+MAC_H;

double ACK=(112/br+PHY_H/CRbr)*1e6;   //in µs



int main(int argc,char **argv){

N=atoi(argv[1]);


bool cont = true;
while (cont){

	 pM=(pR+pL)/2; 

	 taux=(2*(1-2*pM))/((1-2*pM)*(CW+1)+pM*CW*(1-pow((2*pM),m))); //taux is the transmission Prob 
	 
	 p=1-pow((1-taux),N-1);		// p is the collision Prob

	
	

	diff=(pM-p);
	

	if (diff >= 0){
			pR=pM;
			
			if (abs(diff) <= eps){
				cout << N <<"    "<< p << "    " << taux ;
				break;	
			}	
						
			}

	if (diff < 0){
			pL=pM;
			
			if (abs(diff) <= eps){
				cout << N <<"    "<< p <<"    "<< taux ;
				break;	
			}
			
			
			}    

	}


	
 Ptr=1-pow((1-taux),N);


 Ps=(N*taux*pow((1-taux),N-1))/(1-pow((1-taux),N));
 
 Ts=H+L+SIFS+delta+ACK+DIFS+delta;
 Tc=H+L+DIFS+delta;
 throughput=(Ps*Ptr*L)/(Ps*Ptr*Ts+Ptr*(1-Ps)*Tc+(1-Ptr)*rho);


cout <<"    "<<throughput*11<<endl;	//<< "Average throuput  %: " 

// cout <<"Ps = "<<Ps<<endl;
// cout << "Ptr =" <<Ptr<<endl;
// cout << "delta = " << delta<<endl;;
// cout << " ACK = " <<ACK<<endl;
// cout << "L = " << L <<endl;
// cout << "Tc = " << Tc <<endl;
// cout << "Ts = " << Ts <<endl;

return 0;

}


