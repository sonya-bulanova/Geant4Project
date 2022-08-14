//read_tree.cpp

void read_tree(){
	//TFile file2("Run_2keV.root");
	//TFile file3("Run_3keV.root");
	//TFile file4("Run_4keV.root");
	//TFile file5("Run_5keV.root");
	//TFile file6("Run_6keV.root");
	//TFile file7("Run_7keV.root");
	//TFile file8("Run_8keV.root");
	//TFile file9("Run_9keV.root");
	//TFile file10("Run_10keV.root");
	//TFile file11("Run_11keV.root");
	//TFile file12("Run_12keV.root");
	//TFile file13("Run_13keV.root");
	//TFile file14("Run_14keV.root");
	//TFile file15("Run_15keV.root");
	//TFile file16("Run_16keV.root");
	//TFile file17("Run_17keV.root");
	//TFile file18("Run_18keV.root");
	//TFile file19("Run_19keV.root");
	TFile file20("Run_20keV.root");

  Double_t energy = 0;
  Double_t cosinus = 0.99884949;
  Double_t peak_integr;

  TTree * energy_dep;
  file20.GetObject("electrons", energy_dep);

  energy_dep -> SetBranchAddress("total_energy_deposit", &energy);
  TH1F * energy_deposit = new TH1F("energy_deposit", "Total energy deposit, E_{#gamma} = 20 keV; E_{#gamma}, keV; N", 100, 0., 25.);

  Int_t n = energy_dep -> GetEntries();
	for (Int_t i = 0; i < n; i++){
		energy_dep -> GetEntry(i);
		energy_deposit -> Fill(energy);
  }

  TCanvas *c1 = new TCanvas ("c1", "total_energy_deposit", 1200, 800);
	c1 -> cd();
	gPad -> SetLogy();

  energy_deposit -> SetStats(0);
  energy_deposit -> SetLineColor(29);
  energy_deposit -> SetFillColor(29);
  energy_deposit -> Draw();

  TBox *b1 = new TBox(energy_deposit -> GetBinLowEdge(70),
                     energy_deposit -> GetMinimum(),
                     energy_deposit -> GetBinWidth(70) + energy_deposit -> GetBinLowEdge(70),
                     energy_deposit -> GetBinContent(70));
  b1 -> SetFillColor(kBlue - 9);

  for (Int_t i = 70; i < 100; i++){
    TBox *b = new TBox(energy_deposit -> GetBinLowEdge(i),
                       energy_deposit -> GetMinimum(),
                       energy_deposit -> GetBinWidth(i) + energy_deposit -> GetBinLowEdge(i),
                       energy_deposit -> GetBinContent(i));
    b -> SetFillColor(kBlue - 9);
    b -> Draw();
  }

	auto legend = new TLegend(0.5, 0.9, 0.1, 0.7);
	legend -> SetHeader("Total energy deposit, E_{#gamma} = 20 keV","C");
	legend -> AddEntry(energy_deposit, "Copmton scattering","f");
  legend -> AddEntry(b1, "Peak of total absorption","f");
	legend -> Draw();

	//energy_deposit -> Fit("gaus", "", "", 3.5, 8.5);
	//c1 -> cd();
	c1 -> Update();
	c1 -> Modified();
	c1 -> Print("energy_deposit_gauss_20keV.png");
}
