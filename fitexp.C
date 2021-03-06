namespace data{
  vector<double>  x;
}

void logl(int &npar, double *gin, double &f, double *par, int iflag){
  f = 0.0;
  for (int i=0;i<data::x.size();i++){
    f += log(par[0]) + data::x[i]/par[0];
  }
}

void fitexp(){

  ifstream file("exp.dat");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    data::x.push_back(x);
    h->Fill(x);
  }
  TMinuit minuit(1);
  minuit.SetFCN(logl);
  minuit.SetErrorDef(0.5);
  minuit.DefineParameter(0,"tau",1.5,0.01,0.,0.);
  
  minuit.Command("MIGRAD");
  double tau, etau;
  minuit.GetParameter(0,tau,etau);

  h->SetMarkerStyle(20);
  h->Draw("E");
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  fe->SetParameter(1,tau);
  fe->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("SAME");
}
