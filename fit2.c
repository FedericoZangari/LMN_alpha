/*
Questo programma esegue 3 fit gaussiani di un istogramma con 3 picchi. Il programma prende in ingresso il file di dati dell'istogramma e
i canali di inizio e di fine delle 3 regioni in cui si vuole eseguire il fit.
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
  TH1F *h1 = new TH1F("h1", "Spettro", 2000, 0, 2000);
  int i = 0;
	if(!f){
  		cerr <<"Error: cannot open file " <<endl;
		  exit(0);
	}
  	else{
          double var;
			    for (;;){
					
              f >> var;
              if(i < 2000) h1->SetBinContent(i,var);		
									
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

  if ( argc < 8 ) {
    cout << "Uso del programma : " << argv[0] << " <filename> <bin_min_1> <bin_max_1> <bin_min_2> <bin_max_2> <bin_min_3> <bin_max_3>" << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file

  TH1F *h = ReadFillAll(argv[1]);
  h->Sumw2();
  TH1F * h2 = (TH1F*)(h->Clone("h2"));
  //h->Rebin(10);
  TCanvas *c=new TCanvas();
  h->Draw();
  h->GetXaxis()->SetTitle("Numero del canale MCA");
  h->GetYaxis()->SetTitle("Conteggi per canale");
  h->SetTitle("Fit gaussiano per calibrazione");
  //h->GetXaxis()->SetRangeUser(1250,1550);
  TF1 *f1 = new TF1("f1", "gaus", atoi(argv[2]),atoi(argv[3]));
  TF1 *f2 = new TF1("f2", "gaus", atoi(argv[4]),atoi(argv[5]));
  TF1 *f3 = new TF1("f3", "gaus", atoi(argv[6]),atoi(argv[7]));
  h->Fit(f1,"RW");
  h->Fit(f2,"RW");
  h->Fit(f3,"RW");
  f1->Draw("same");
  f2->Draw("same");
  f3->Draw("same");
  //c->SaveAs("fit_gaussiano_calib.png");
  /*
  Double_t mean = f->GetParameter(1);
  Double_t sigma = f->GetParameter(2);
  cout << "Valor medio: \t\t" << mean << endl;
  cout << "Deviazione standard: \t" << sigma << endl;
  cout << "Risoluzione: \t\t" << sigma/mean << endl;
  cout << "Integrale entro 3 sigma: \t" << h2->Integral(mean-3*sigma, mean+3*sigma) << endl;
  cout << "Integrale totale: \t\t" << h2->Integral() << endl;*/
  app.Run();
}


