#include <Fit/Fitter.h>
#include <Fit/BinData.h>
#include <Fit/Chi2FCN.h>
#include <TH1.h>
#include <Math/WrappedMultiTF1.h>
#include <HFitInterface.h>
#include <TCanvas.h>
#include <TStyle.h>

// Definitions of shared parameter background function:
int iparB[2] = {
    0,  // exp amplitude in B hist;
    2   // exp common parameter.
};
// Signal + Background function:
int iparSB[5] = {
    1,  // exp amplitude in S+B hist;
    2,  // exp common parameter;
    3,  // Gaussian amplitude
    4,  // Gaussian mean
    5   // Gaussian sigma
};

// Create the GlobalChi2 structure:
struct GlobalChi2 {
    GlobalChi2(ROOT::Math::IMultiGenFunction &f1, ROOT::Math::IMultiGenFunction &f2):fChi2_1(&f1), fChi2_2(&f2) {}
    // parameter vector: first for background (in common 1 and 2), second for signal (only in 2):
    double operator()(const double *par) const
    {
        double p1[2];
        for (int i = 0; i < 2; ++i)     p1[i] = par[iparB[i]];
        double p2[5];
        for (int i = 0; i < 5; ++i)     p2[i] = par(iparSB[i]);
        return (*fChi2_1)(p1) + (*fChi2_2)(p2);
    }
    const ROOT::Math::IMultiGenFunction *fChi2_1;
    const ROOT::Math::IMultiGenFunction *fChi2_2;
};

void combinedFit()
{
    TH1D *hB = new TH1D("hB", "hist B", 100, 0, 100);
    TH1D *hSB = new TH1D("hSB", "hist S+B", 100, 0, 100);

    TF1 *fB = new TF1("fB", "expo", 0, 100);
    fB->SetParameters(1, -0.05);
    hB->FillRandom("fB");

    TF1 *fS = new TF1("fS", "gaus", 0, 100);
    fS->SetParameters(1, 30, 5);

    fSB->FillRandom("fB", 2000);
    fSB->FillRandom("fS", 1000);

    // Now perform global fit:
    TF1 *fSB = new TF1("fSB", "expo + gaus(2)", 0, 100);

    ROOT::Math::WrappedMultiTF1 wfB(*fB, 1);
    ROOT::Math::WrappedMultiTF1 wfSB(*fSB, 1);
}