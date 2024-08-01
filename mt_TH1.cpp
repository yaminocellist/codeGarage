#include "TH1.h"
#include "TF1.h"
#include "Fit/BinData.h"
#include "HFitInterface.h"
#include "Fit/Fitter.h"
#include "Math/WrappedMultiTF1.h"
#include "Math/WrappedParamFunction.h"
#include "TROOT.h"
#include "TVirtualFitter.h"
#include <iostream>
#include <thread>
#include <mutex>
TH1 *h[100];
std::mutex m_mutex;
double sum;
void testFitter(int id) {
    auto func = (TF1*)gROOT->GetFunction("gaus");
    //auto func = new TF1("g","gaus",-3,3);

    for(int i = 0; i < 5; ++i) {
        func->SetParameters(1000,0,1);
        double zeros[] = {0,0,0};
        func->SetParErrors(zeros);

        h[i*(id+1)]->Fit(func,(i==0?"N":"NQ"),"",-3,3);
        auto x = func->GetParameter(1);
        auto y = func->GetParameter(2);
        // if(i==0)
        printf("%d %d %d %.18le %.18le\n", id, i, i*(id+1), x, y);
        // break;
    }
}

void testFitter_ver2 (int id) {
    auto func = (TF1*)gROOT->GetFunction("gaus");
    std::unique_lock<std::mutex> lock(m_mutex); // lock the mutex;
    for (int i = 0; i < 5; i++) {
        func -> SetParameters(1000, 0, 1);
        double zeros[] = {0, 0, 0};
        func -> SetParErrors(zeros);

        h[i + id*5] -> Fit(func, (i==0?"N":"NQ"), "", -3, 3);
        auto x = func -> GetParameter(1);
        auto y = func -> GetParameter(2);
        printf("Now: %d, %d, #%d of histograms, %.18le, %.18le\n", id, i, i + id*5, x, y);
    }
    lock.unlock();
    // sum += id;
}

int main() {
    sum = 0;
    auto gaus = static_cast<TF1*>(gROOT->GetFunction("gaus"));
    gaus->SetParameters(100,0,1);
    for(int i = 0; i < 100; ++i) {
        h[i] = new TH1D(Form("h%d", i), Form("h%d", i), 100, -5, 5);
        h[i] -> FillRandom("gaus", 10000);
    }
    TVirtualFitter::SetDefaultFitter("Minuit2");
    // for(int i = 0;i<100;++i)    std::cout<<i<<" "<<h[0]->GetBinContent(i)<<std::endl;
    ROOT::EnableThreadSafety();
    std::thread th[15],thsafe[15];
    // std::cout<<"mt safe:"<<std::endl;
    // for(int i = 0; i < 15; ++i) {
    //     th[i]= std::thread([](int id){
    //         std::unique_lock<std::mutex> lock(m_mutex);
    //         testFitter(id);
	// 	    },i);
    // }
    // for(int i = 0;i<2;++i)   th[i].join();
    std::cout<<"mt unsafe:"<<std::endl;
    for(int i = 0; i < 15; ++i)     thsafe[i]= std::thread(testFitter_ver2,i);
    for(int i = 0; i < 15; ++i)     thsafe[i].join();

    std::cout << sum << std::endl;
    // std::cout<<"serial:"<<std::endl;
    // for(int i = 0;i<2;++i)  testFitter(i);
    return 0;
}
