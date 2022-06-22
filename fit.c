/*
Questo programma esegue un fit gaussiani di un istogramma.
*/

#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

TH1F* ReadFillAll( const char* Filename) {
  
	ifstream f(Filename);
  TH1F *h1 = new TH1F("h1", "Spettro", 1600, 0, 1600);
  int i = 0;
	if(!f){
  		cerr <<"Error: cannot open file " <<endl;
		  exit(0);
	}
  	else{
          double var;
			    for (;;){
					
              f >> var;
              if(i < 1600) h1->SetBinContent(i,var);		
									
					    if(f.eof()){
						    cout << "End of file reached "<< endl;
						    break;
					    }
              i++;		
			      }
		}	f.close();

	return h1;
}


int main( int argc , char** argv ) {

  if ( argc < 2 ) {
    cout << "Uso del programma : " << argv[0] << " <filename> " << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file

  TH1F *h = ReadFillAll(argv[1]);
  h->Sumw2();
  TF1 * f = new TF1("f", "gaus", 1300, 1600);
  //f->SetParameter(1,1420);
  h->Draw();
  h->Draw("same");
  h->Fit("f","R");
  h->GetXaxis()->SetTitle("Numero del canale MCA");
  h->GetYaxis()->SetTitle("Conteggi per canale");
  
  
  Double_t mean = f->GetParameter(1);
  Double_t sigma = f->GetParameter(2);
  cout << "Valor medio: \t\t" << mean << endl;
  cout << "Deviazione standard: \t" << sigma << endl;
  cout << "Risoluzione: \t\t" << sigma/mean << endl;
  cout << "Integrale entro 3 sigma: \t" << h->Integral(mean-3*sigma, mean+3*sigma) << endl;
  cout << "Integrale totale: \t\t" << h->Integral() << endl;
  app.Run();
}


