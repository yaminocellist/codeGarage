#include <Math/MinimizerOptions.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1D.h>
#include <TStopwatch.h>
#include <TStyle.h>

#include <iostream>

void vectorizedFit() 
{
    TStopwatch w;
    w.Start();
    gStyle -> SetOptFit(111111);

    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
    int nbins = 40000;
    auto h1 = new TH1D("h1", "h1", nbins, -3, 3);
    h1 -> FillRandom("gaus", nbins*50);
    auto c1 = new TCanvas("Fit", "Fit", 2560, 1600);
    c1 -> Divide(1, 2);
    c1 -> cd(1);
    std::cout << "Doing Serial Gaussian Fit" << std::endl;
    auto f1 = new TF1("f1", "gaus");
    f1 -> SetNpx(nbins*10);
    h1 -> Fit(f1);
    h1 -> Fit(f1, "L+");
    w.Print();

    std::cout << "Doing Vectorized Gaussian Fit " << std::endl;
    auto f2 = new TF1("f2", "gaus", -3, 3, "VEC");
    w.Start();
    h1 -> Fit(f2);
    h1 -> Fit(f2, "L+");
    // rebin histograms and scale it back to the function
    h1 -> Rebin(nbins/100);
    h1 -> Scale(100./nbins);
    ((TF1 *)h1->GetListOfFunctions()->At(0))->SetTitle("Chi2 Fit");
    ((TF1 *)h1->GetListOfFunctions()->At(1))->SetTitle("Likelyhood Fit");
    ((TF1 *)h1->GetListOfFunctions()->At(1))->SetLineColor(kBlue);
    c1->cd(1)->BuildLegend();
    w.Print();

    // The second canvas for Polynomial fit:
    c1 -> cd(2);
    auto f3 = new TF1("f3", "[A]*x^2 + [B]*x + [C]", 0, 10);
    f3 -> SetParameters(0.5, 3, 2);
    f3 -> SetNpx(nbins*10);
    auto h2 = new TH1D("h2", "h2", nbins, 0, 10);
    h2 -> FillRandom("f3", 10*nbins);
    std::cout << "Doing Polynomial Fit" << std::endl;
    f3 -> SetParameters(2, 2, 2);
    w.Start();
    h2 -> Fit(f3);
    h2 -> Fit(f3, "L+");
    w.Print();
    // Rebin and scale it back:
    h2 -> Rebin(nbins/100);
    h2 -> Scale(100./nbins);
    ((TF1 *)h2->GetListOfFunctions()->At(0))->SetTitle("Chi2 Fit");
    ((TF1 *)h2->GetListOfFunctions()->At(1))->SetTitle("Likelihood Fit");
    ((TF1 *)h2->GetListOfFunctions()->At(1))->SetLineColor(kBlue);
}