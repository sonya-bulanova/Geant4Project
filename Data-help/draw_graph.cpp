//draw_graph.cpp
void draw_graph(){
  Double_t energy[] = {2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20.};
  Double_t eff[] = {0.029, 0.207, 0.301, 0.39, 0.427, 0.426, 0.40, 0.36, 0.317, 0.274, 0.235, 0.201, 0.172, 0.147, 0.127, 0.109, 0.095, 0.0827, 0.0723};
  Double_t x, y;
  TGraph *efficiency = new TGraph();
  TCanvas *c1 = new TCanvas ("c1", "efficiency", 1200, 1200);
  for (int i = 0; i < 19; i++){
		efficiency -> SetPoint(i, energy[i], eff[i]);
  }
  c1 -> cd();
  efficiency -> SetMarkerStyle(8);
  efficiency -> SetLineColor(kRed);
  efficiency -> SetLineWidth(4);
	efficiency -> SetTitle("Efficiency of proportional counter");
  efficiency -> GetXaxis() -> SetTitle("Energy, keV");
  efficiency -> GetYaxis() -> SetTitle("Efficiency, %");
	efficiency -> Draw("APC");

	c1->Update();
	c1 -> Modified();
	c1 -> Print("efficiency.png");
}
