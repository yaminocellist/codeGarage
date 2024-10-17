#include <TBinomialEfficiencyFitter.h>
#include <TVirtualFitter.h>
#include <TH1.h>
#include <TRandom3.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TGraphErrors.h>
#include <TObjArray.h>
#include <HFitInterface.h>
#include <Fit/BinData.h>
#include <Math/IntegratorOptions.h>

#include <cassert>
#include <iostream>

void TestBinomial (int nloop = 100, int nevts = 100, bool plot = false, bool debug = false, int seed = 111) {
    gStyle -> SetMarkerStyle(20);
    gStyle -> SetLineWidth(2.);
    gStyle -> SetOptStat(11);

    TObjArray hbiasNorm;
    hbiasNorm.Add(new TH1D("h0Norm", "Bias Histogram Fit", 100, -5, 5));
    hbiasNorm.Add(new TH1D("h1Norm", "Bias Binomial Fit", 100, -5, 5));
    TObjArray hbiasThreshold;
    hbiasThreshold.Add(new TH1D("h0Threshold", "Bias Histogram Fit", 100, -5, 5));
    hbiasThreshold.Add(new TH1D("h1Threshold", "Bias Binomial Fit", 100, -5, 5));
    TObjArray hbiasWidth;
    hbiasWidth.Add(new TH1D("h0Width", "Bias Histogram Fit", 100, -5, 5));
    hbiasWidth.Add(new TH1D("h1Width", "Bias Binomial Fit", 100, -5, 5));
    TH1D *hChisquared = new TH1D("hChisquared", "#chi^{2} probability (Baker-Cousins)", 200, 0.0, 1.);

    TVirtualFitter::SetDefaultFitter("Minui2");
    ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("Gauss");

    double xmin = 10, xmax = 100;
    TH1D *hM2D = new TH1D("hM2D", "x^(-2) denominator distribution", 45, xmin, xmax);
    TH1D *hM2N = new TH1D("hM2N", "x^(-2) numerator distribution", 45, xmin, xmax);
    TH1D *hM2E = new TH1D("hM2E", "x^(-2) efficiency", 45, xmin, xmax);

    TF1 *fM2D = new TF1("fM2D", "(1-[0]/(1+exp(([1]-x)/[2])))/(x*x)", xmin, xmax);
    TF1 *fM2N = new TF1("fM2N", "[0]/(1+exp(([1]-x)/[2]))/(x*x)", xmin, xmax);
    TF1 *fM2Fit = new TF1("fM2Fit", "[0]/(1+exp(([1]-x)/[2]))", xmin, xmax);
    TF1 *fM2Fit2 = nullptr;

    TRandom3 rb(seed);

    double normalization = 0.80;
    double threshold = 25.0;
    double width = 5.0;

    fM2D -> SetParameters(0, normalization);
    fM2D -> SetParameters(1, threshold);
    fM2D -> SetParameters(2, width);
    fM2N -> SetParameters(0, normalization);
    fM2N -> SetParameters(1, threshold);
    fM2N -> SetParameters(2, width);
    double integralN = fM2N->Integral(xmin, xmax);
    double integralD = fM2D->Integral(xmin, xmax);
    double fracN     = integralN/(integralN + integralD);
    int nevtsN       = rb.Binomial(nevts, fracN);
    int nevtsD       = nevts - nevtsN;
    std::cout << nevtsN << "  " << nevtsD << std::endl;

    gStyle -> SetOptFit(1111);

    for (int iloop = 0; iloop < nloop; ++iloop) {
        hM2D -> Reset();
        hM2N -> Reset();
        hM2D -> FillRandom(fM2D->GetName(), nevtsD);
        hM2N -> FillRandom(fM2N->GetName(), nevtsN);
        hM2D -> Add(hM2N);

        hM2N->Sumw2();
        hM2E->Divide(hM2N, hM2D, 1, 1, "b");

        // Fit twice, using the same fit function;
        // In the first (standard) fit, initialize to (arbitrary) value;
        // In the second fit, use the results from the first fit, which makes it easier for the fit,
        // but the purpose is not to show how easy it is to obtain results,
        // but whether the CORRECT results are obtained or not.
        fM2Fit->SetParameters(0, 0.5);
        fM2Fit->SetParameters(1, 15.);
        fM2Fit->SetParameters(2, 2.);
        fM2Fit->SetParError(0, 0.1);
        fM2Fit->SetParError(1, 1.);
        fM2Fit->SetParError(2, 0.2);
        TH1 *hf = fM2Fit->GetHistogram();
        std::cout << "Function values " << std::endl;
        for (int i = 1; i <= hf->GetNbinsX(); ++i) {
            std::cout << hf->GetBinContent(i) << " ";
        }
        std::cout << std::endl;

        TCanvas *cEvt;
        if (plot) {
            cEvt = new TCanvas(Form("cEnv%d", iloop), Form("plots for experiment %d", iloop), 1000, 600);
            cEvt->Divide(1,2);
            cEvt->cd(1);
            hM2D->DrawCopy("HIST");
            hM2N->SetLineColor(kRed);
            hM2N->DrawCopy("HIST SAME");
            cEvt->cd(2);
        }
        for (int fit = 0; fit < 2; ++fit) {
            int status = 0;
            switch (fit) {
                case 0:
                {
                    TString optFit = "RN";
                    if (debug) optFit += TString("SV");
                    TFitResultPtr res = hM2E->Fit(fM2Fit, optFit);
                    if (plot) {
                        hM2E->DrawCopy("E");
                        fM2Fit->SetLineColor(kBlue);
                        fM2Fit->DrawCopy("SAME");
                    }
                    if (debug) res->Print();
                    status = res;
                    break;
                }
                case 1: {
                    fM2Fit2 = fM2Fit;
                    if (fM2Fit2->GetParameter(0) >= 1.0)
                    fM2Fit2->SetParameter(0, 0.95);
                    fM2Fit2->SetParLimits(0, 0.0, 1.0);
                }
            }
        }
    }
}