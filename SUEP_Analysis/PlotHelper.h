#ifndef plothelper_h
#define plothelper_h

#include <map>
#include <iostream>
#include <string>
#include <cmath>
#include <TROOT.h>
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TProfile.h"
#include "TColor.h"
#include "TList.h"
#include "TF1.h"
#include "TMath.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TPaveStats.h"

using namespace std;
std::string plotdir = "Plots";



class PlotHelper {
 public:
  PlotHelper(const std::string formatString="eps") {
    setPlotStyle();
    doSumW2 = true;
    doPng = (formatString.find("png")!=std::string::npos);
    doEps = (formatString.find("eps")!=std::string::npos);
    doC = (formatString.find("C")!=std::string::npos);
  };

  static void setPlotStyle() {
      std::cout << "Using Karris Plot Style" << endl;
      TStyle* gStyle = new TStyle("gStyle","Karris Plot Style"); 
      
      gStyle->SetPalette(kBird);
 
      gROOT->SetBatch(kTRUE);
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(0);
      gStyle->SetLabelFont(42,"xyz"); // Helvetica
      gStyle->SetLabelSize(0.05,"xyz");
      gStyle->SetTitleFont(42,"xyz"); // Helvetica
      gStyle->SetTitleFont(42,"t"); // Helvetica
      gStyle->SetTitleSize(0.06,"xyz");
      gStyle->SetTitleSize(0.06,"t");

      gStyle->SetPadBottomMargin(0.14);
      gStyle->SetPadLeftMargin(0.14);

      gStyle->SetPadGridX(0);
      gStyle->SetPadGridY(0);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);

      gStyle->SetTitleOffset(1,"y");
      gStyle->SetLegendTextSize(0.04);
      gStyle->SetGridStyle(3);
      gStyle->SetGridColor(14);

      gStyle->SetMarkerSize(1.0); //large markers
      gStyle->SetHistLineWidth(2); // bold lines
      gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
      
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(0);    // Fits

      gROOT->SetStyle("gStyle");
      gROOT->ForceStyle();
    
  }

  int wide = 2;
 
  void Plot1D(const std::string name, const std::string title,
	      const float x,
	      const int nbinsx, const float xmin, const float xmax,
	      const float weight=1.) {
    //std::string fname = name;
    //std::replace(fname.begin(), fname.end(), ' ', '_');
    std::map<std::string, TH1F*>::iterator iter = histos_1d.find(name);
    if (iter==histos_1d.end()) { //cout << "Creating " << name << endl;// doesn't exist, so create histo
      TH1F *h = new TH1F(name.c_str(), title.c_str(), nbinsx, xmin, xmax);
      if (doSumW2) h->Sumw2();
      TPaveStats *stats = (TPaveStats*) h->GetListOfFunctions()->FindObject("stats");
      if (stats){
        stats->SetY2NDC(0.9);
        stats->SetY1NDC(0.7);
      }
      //h->SetTitle(name.c_str());
      h->Fill(x, weight);
      h->SetLineColor(kBlack);
      h->SetLineWidth(wide);
      h->SetStats(kTRUE);
      histos_1d.insert( std::pair<std::string, TH1F*> (name,h) );
    } else {// exists already, so just fill it
      iter->second->Fill(x,weight);
    }
  }


  void Plot2D(const std::string name, const std::string title,
	      const float x, const float y,
	      const int nbinsx, const float xmin, const float xmax,
	      const int nbinsy, const float ymin, const float ymax,
	      const float weight=1.) {
    std::string fname = name;
    std::replace(fname.begin(), fname.end(), ' ', '_');
    std::map<std::string, TH2F*>::iterator iter = histos_2d.find(fname);
    if (iter==histos_2d.end()) {// doesn't exist, so create histo
      TH2F *h = new TH2F(fname.c_str(), title.c_str(), nbinsx, xmin, xmax, nbinsy, ymin, ymax);
      if (doSumW2) h->Sumw2();
      TPaveStats *stats = (TPaveStats*) h->GetListOfFunctions()->FindObject("stats");
      if (stats){
        stats->SetY2NDC(0.9);
        stats->SetY1NDC(0.7);
      }
      //h->SetTitle(name.c_str());
      h->Fill(x, y, weight);
      //h->Write();
      h->SetStats(kTRUE);  
      histos_2d.insert( std::pair<std::string, TH2F*> (fname,h) );
    } else {// exists already, so just fill it
      iter->second->Fill(x,y,weight);
    }
  }
  void Plot3D(const std::string name, const std::string title,
        const float x, const float y, const float z,
        const int nbinsx, const float xmin, const float xmax,
        const int nbinsy, const float ymin, const float ymax,
        const int nbinsz, const float zmin, const float zmax,
        const float weight=1.) {
    std::string fname = name;
    std::replace(fname.begin(), fname.end(), ' ', '_');
    std::map<std::string, TH3F*>::iterator iter = histos_3d.find(fname);
    if (iter==histos_3d.end()) {// doesn't exist, so create histo
      TH3F *h = new TH3F(fname.c_str(), title.c_str(), nbinsx, xmin, xmax, nbinsy, ymin, ymax, nbinsz, zmin, zmax);
      if (doSumW2) h->Sumw2();
      TPaveStats *stats = (TPaveStats*) h->GetListOfFunctions()->FindObject("stats");
      if (stats){
        stats->SetY2NDC(0.9);
        stats->SetY1NDC(0.7);
      }
      //h->SetTitle(name.c_str());
      h->Fill(x, y, z, weight);
      //h->Write();
      h->SetStats(kTRUE);  
      histos_3d.insert( std::pair<std::string, TH3F*> (fname,h) );
    } else {// exists already, so just fill it
      iter->second->Fill(x,y,z,weight);
    }
  }


  void Draw1D(TCanvas *c1, TH1F *h, const int logy=0,
	      const char *const drawopt="hist", bool norm=false) {
    c1->cd();
    c1->Clear();
    h->Draw(drawopt);
    c1->SetLogy(logy);
    //deal with overflow here
    h->SetBinContent(h->GetNbinsX(), h->GetBinContent(h->GetNbinsX() + 1) + h->GetBinContent(h->GetNbinsX()));
    h->SetBinContent(h->GetNbinsX() + 1, 0);
    if(norm) h->Scale(1.0/h->Integral());
    h->SetBinContent(1, h->GetBinContent(0) + h->GetBinContent(1));
    //h->SetBinError(h->GetNbinsX(), sqrt(pow(h->GetBinError(h->GetNbinsX() + 1), 2) + pow(h->GetBinError(h->GetNbinsX()),2)));
    if(doPng)c1->Print(Form((norm ? "%s/%s_norm.png" : "%s/%s.png"), plotdir.c_str(), h->GetName()));
    if(doEps)c1->Print(Form((norm ? "%s/%s_norm.eps" : "%s/%s.eps"), plotdir.c_str(), h->GetName()));
    if(doC)  c1->Print(Form((norm ? "%s/%s_norm.C"   : "%s/%s.C"  ), plotdir.c_str(), h->GetName()));
    c1->SetLogy(0);
    h->Write();
  }

  void Draw2D(TCanvas *c1, TH2F *h, const int logy=0, const char *const drawopt="COLZ"){
    c1->cd();
    c1->Clear();
    c1->SetLogy(logy);
    //h->GetYaxis()->SetTitleOffset(1.5);
    h->Draw(drawopt);
    if(doPng)c1->Print(Form("%s/%s.png", plotdir.c_str(), h->GetName()));
    if(doEps)c1->Print(Form("%s/%s.eps", plotdir.c_str(), h->GetName()));
    if(doC)c1->Print(Form("%s/%s.C", plotdir.c_str(), h->GetName()));
    h->Write();

  }
  void Draw3D(TCanvas *c1, TH3F *h, const int logz=0, const char *const drawopt="BOX"){
    c1->cd();
    c1->Clear();
    c1->SetLogz(logz);
    //h->GetYaxis()->SetTitleOffset(1.5);
    h->Draw(drawopt);
    if(doPng)c1->Print(Form("%s/%s.png", plotdir.c_str(), h->GetName()));
    if(doEps)c1->Print(Form("%s/%s.eps", plotdir.c_str(), h->GetName()));
    if(doC)c1->Print(Form("%s/%s.C", plotdir.c_str(), h->GetName()));
    h->Write();

  }

  void DrawAll1D(TCanvas *c1, const char *const drawopt="hist") {
    std::map<std::string, TH1F*>::iterator iter = histos_1d.begin();
    for (; iter!=histos_1d.end(); ++iter) {
      Draw1D(c1, iter->second, 0, drawopt);
    }
  }
  void DrawAll2D(TCanvas *c1, const char *const drawopt="colz") {
    std::map<std::string, TH2F*>::iterator iter = histos_2d.begin();
    for (; iter!=histos_2d.end(); ++iter) {
      Draw2D(c1, iter->second, 0, drawopt);
    }
  }
  void DrawAll3D(TCanvas *c1, const char *const drawopt="BOX") {
    std::map<std::string, TH3F*>::iterator iter = histos_3d.begin();
    for (; iter!=histos_3d.end(); ++iter) {
      Draw3D(c1, iter->second, 0, drawopt);
    }
  }

  TH1F *get1D(const char *const s) {
    //return histos_1d.find(s)->second;
    std::map<std::string, TH1F*>::iterator it = histos_1d.find(s);
    if (it==histos_1d.end()) {
      return 0;
    } else {
      return it->second;
    }
  }
  TH2F *get2D(const char *const s) {
    //return histos_2d.find(s)->second;
    std::map<std::string, TH2F*>::iterator it = histos_2d.find(s);
    if (it==histos_2d.end()) {
      return 0;
    } else {
      return it->second;
    }
  }

  TH3F *get3D(const char *const s) {
    std::map<std::string, TH3F*>::iterator it = histos_3d.find(s);
    if (it==histos_3d.end()) {
      return 0;
    } else {
      return it->second;
    }
  }

  void FitSelect1D(vector<double> &lumi_fitvalue, string fitname) {
    std::map<std::string, TH1F*>::iterator iter = histos_1d.begin();
    for (; iter!=histos_1d.end(); ++iter) {
      TString itername = iter->first;
      if (itername.Contains(fitname.c_str())) {
        TH1F *iter_hist = iter->second;
        iter_hist->Fit("pol1","QM");
        TF1 *myfit = iter_hist->GetFunction("pol1");
        std::cout << iter_hist->GetName() << " fit slope " << myfit->GetParameter(1) << " fit inter " << myfit->GetParameter(0) << std::endl;
        lumi_fitvalue.push_back(myfit->GetParameter(1));
      }
    }
  }

void FitSelectGau(string fitname) {
    std::map<std::string, TH1F*>::iterator iter = histos_1d.begin();
    for (; iter!=histos_1d.end(); ++iter) {
      TString itername = iter->first;
      if (itername.Contains(fitname.c_str())) {
        TH1F *iter_hist = iter->second;
        iter_hist->Fit("gaus","QM");
        TF1 *myfit = iter_hist->GetFunction("gaus");
        std::cout << iter_hist->GetName() << " fit width " << myfit->GetParameter(1) << " fit mean " << myfit->GetParameter(0) << std::endl;
      }
    }
  }

  std::map<std::string, TH1F*> histos_1d;
  std::map<std::string, TH2F*> histos_2d;
  std::map<std::string, TH3F*> histos_3d;

  bool doSumW2;

 private:
  bool doC, doEps, doPng;
};

#endif

