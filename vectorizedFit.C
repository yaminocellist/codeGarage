#include <Math/MinimizerOptions.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1D.h>
#include <TStopwatch.h>
#include <TStyle.h>

#include <iostream>

void vectorizedFit() 
{
    gStyle -> SetOptFit(111111);

    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
    int nbins = 40000;
    auto h1 = new TH1D("h1", "h1", nbins, -3, 3);
    h1 -> FillRandom("gaus", nbins*50);
    auto c1 = new TCanvas("Fit", "Fit", 2560, 1600);
    c1 -> Divide(1, 2);
    c1 -> cd(1);
    TStopwatch w;

    std::cout << "Doing Serial Gaussian Fit" << std::endl;
    auto f1 = new TF1("f1", "gaus");
    f1 -> SetNpx(nbins*10);
    w.Start();
    h1 -> Fit(f1);
    h1 -> Fit(f1, "L+");
    w.Print();
}