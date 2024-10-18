#include "TH1.h"
#include "TF1.h"

void multifit () {
    const int np = 49;
    // The histogram are filled with bins defined in the array x:
    float x[np] = {1.913521,  1.953769,  2.347435,  2.883654,  3.493567,  4.047560,  4.337210,  4.364347,  4.563004,
                   5.054247,  5.194183,  5.380521,  5.303213,  5.384578,  5.563983,  5.728500,  5.685752,  5.080029,
                   4.251809,  3.372246,  2.207432,  1.227541,  0.8597788, 0.8220503, 0.8046592, 0.7684097, 0.7469761,
                   0.8019787, 0.8362375, 0.8744895, 0.9143721, 0.9462768, 0.9285364, 0.8954604, 0.8410891, 0.7853871,
                   0.7100883, 0.6938808, 0.7363682, 0.7032954, 0.6029015, 0.5600163, 0.7477068, 1.188785,  1.938228,
                   2.602717,  3.472962,  4.465014,  5.177035};
    TH1F *h = new TH1F("h", "Example of multiple fits in subranges", np, 85, 134);
    h->SetMaximum(7);
    for (int i = 0; i < np; i++) {
        h->SetBinContent(i+1, x[i]);
    }

    // Define the parameter array for the whole function:
    double par[9];
    for (int i = 0; i < 9; i++) par[i] = 100;

    // Three TF1 objects are created, one for each subrange:
    TF1 *g1 = new TF1("g1", "gaus", 85, 95);
    TF1 *g2 = new TF1("g2", "gaus", 98, 108);
    TF1 *g3 = new TF1("g3", "gaus", 110, 121);

    // The total is the sum of the three, each has three parameters:
    // TF1 *total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)", 85, 125);
    // TF1 *total = new TF1("total", "[&](double *x, double *p){ return p[0]*g1(x) + p[1]*g2(x) + p[2]*g3(x); }", 85, 125, 3);
    TF1 *total = new TF1("total", 
    [&](double *x, double *p){ 
        double g1 = p[0] * exp(-0.5 * pow((x[0] - p[1]) / p[2], 2));
        double g2 = p[3] * exp(-0.5 * pow((x[0] - p[4]) / p[5], 2));
        double g3 = p[6] * exp(-0.5 * pow((x[0] - p[7]) / p[8], 2));
        return g1 + g2 + g3;
    }, 85, 125, 9);



    total->SetLineColor(2);

    // Fit each function and add it to the list of functions.
    // By default, TH1::Fit() fits the function on the defined histogram range.
    // You can specify the "R" option in the second par of TH1::Fit() to restrict the 
    // fit to the range specified in the TF1 constructor.
    // Alternatively, you can also specify the range in the call to TH1::Fit(),
    // which we demonstrate here with the 3rd Gaussian.
    // The "+" option needs to be added to the later fits to not replace existing 
    // fitted functions in the histogram.

    h->Fit(g1, "R");
    h->Fit(g2, "R+");
    h->Fit(g3, "+", "", 110, 121);
    // Get the parameters from the fit:
    g1->GetParameters(&par[0]);
    g2->GetParameters(&par[3]);
    g3->GetParameters(&par[6]);
    // Use the parameters on the sum:
    total->SetParameters(par);
    // total->SetParameter(0, 5);  // Amplitude of the first Gaussian
    // total->SetParameter(1, 90); // Mean of the first Gaussian
    // total->SetParameter(2, 2);  // Sigma of the first Gaussian

    // total->SetParameter(3, 4);  // Amplitude of the second Gaussian
    // total->SetParameter(4, 100);// Mean of the second Gaussian
    // total->SetParameter(5, 2);  // Sigma of the second Gaussian

    // total->SetParameter(6, 3);  // Amplitude of the third Gaussian
    // total->SetParameter(7, 115);// Mean of the third Gaussian
    // total->SetParameter(8, 2);  // Sigma of the third Gaussian
    h->Fit(total, "R+");
    h->Draw();
    total->Draw("same");
}