//read_tree.cpp

void efficiency(){
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
	TFile file17("Run_17keV.root");
	TFile file18("Run_18keV.root");
	TFile file19("Run_19keV.root");
	TFile file20("Run_20keV.root");

	Double_t energy;
  Double_t cosinus = 0.98994949; //угол определим из геометрических соображений, зная ширину окошка и расстояние до него
  Double_t peak_integr;
	Double_t omega;
	Double_t effic = 0;

  TTree * energy_dep;
	file20.GetObject("electrons", energy_dep);

  energy_dep -> SetBranchAddress("total_energy_deposit", &energy);
  TH1F * energy_deposit1 = new TH1F("energy_deposit", "Total energy deposit, E_{#gamma} = 20 keV; N; E_{#gamma}, keV", 100, 0., 25.5);

  Int_t n = energy_dep -> GetEntries();
	for (Int_t i = 0; i < n; i++){
		energy_dep -> GetEntry(i);
		energy_deposit1 -> Fill(energy);
  }

  peak_integr = energy_deposit1 -> Integral(69, 100, "");
  std::cout << peak_integr << std::endl;
	omega = 2.*3.14159*(1 - cosinus);

	effic = (omega / (4 * 3.14159)) * (peak_integr / (1e7));
	std::cout << effic << std::endl;

  TCanvas *c1 = new TCanvas ("c1", "total_energy_deposit", 1200, 800);
	c1 -> cd();
	gPad -> SetLogy();
  energy_deposit1 -> Draw();
  TBox *b1 = new TBox(energy_deposit1 -> GetBinLowEdge(69),
                     energy_deposit1 -> GetMinimum(),
                     energy_deposit1 -> GetBinWidth(69) + energy_deposit1 -> GetBinLowEdge(69),
                     energy_deposit1 -> GetBinContent(69));
  b1 -> SetFillColor(kRed);
	b1 -> Draw();

	c1 -> cd();
	c1 -> Update();
	c1 -> Modified();
	c1 -> Print("energy_deposit_gauss_20keV.png");
}
