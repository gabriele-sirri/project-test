#include "RooDataSet.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooUniform.h"
#include "TCanvas.h"

int ex_16_limite_centrale()
{
  using namespace RooFit;

  RooRealVar var0{"var0", "var0", 0, 1};
  RooRealVar var1{"var1", "var1", 0, 1};
  RooRealVar var2{"var2", "var2", 0, 1};
  RooRealVar var3{"var3", "var3", 0, 1};
  RooRealVar var4{"var4", "var4", 0, 1};
  RooRealVar var5{"var5", "var5", 0, 1};
  RooRealVar var6{"var6", "var6", 0, 1};
  RooRealVar var7{"var7", "var7", 0, 1};
  RooRealVar var8{"var8", "var8", 0, 1};
  RooRealVar var9{"var9", "var9", 0, 1};

  RooArgSet var_set{var0, var1, var2, var3, var4, var5, var6, var7, var8};
  var_set.add(var9);

  //
  RooUniform model{"model", "model", var_set};
  
  /*
  RooUniform model0{"model0", "model0", var0};
  RooUniform model1{"model1", "model1", var1};
  RooUniform model2{"model2", "model2", var2};
  RooUniform model3{"model3", "model3", var3};
  RooUniform model4{"model4", "model4", var4};
  RooUniform model5{"model5", "model5", var5};
  RooUniform model6{"model6", "model6", var6};
  RooUniform model7{"model7", "model7", var7};
  RooUniform model8{"model8", "model8", var8};
  RooUniform model9{"model9", "model9", var9};
  
  RooArgSet model_set{model0, model1, model2, model3, model4, model5, model6, model7, model8};
  model_set.add{model9};
  
  RooProdPdf model{"model", "model", model_set};
  */

  auto data = model.generate(var_set, 10000);

  // Construct formula to calculate the sum events
  RooFormulaVar f2{"f2", "@0+@1-1.", var_set};
  auto sum2 = (RooRealVar*)data->addColumn(f2);

  RooFormulaVar f3{"f3", "@0+@1+@2-1.5", var_set};
  auto sum3 = (RooRealVar*)data->addColumn(f3);

  RooFormulaVar f10{"f10", "@0+@1+@2+@3+@4+@5+@6+@7+@8+@9-5.", var_set};
  auto sum10 = static_cast<RooRealVar*>(data->addColumn(f10));

  std::cout << "\n\n" ;
  data->Print();
  
  std::cout << "\n\n" ;
  var0.Print();
  sum2->Print();
  sum3->Print();
  sum10->Print();
  
  std::cout << "n.of bins of sum10 = " << sum10->getBins() << "\n" ;
 
  RooRealVar m{"m", "m", 3, 0, 6};
  RooRealVar s{"s", "s", 2, 0.5, 5};
  RooGaussian gaus("gaus", "gaus", *sum10, m, s);
  gaus.fitTo(*data);

  // plotting
  auto plot = var0.frame(Bins(100), Title("Random variable"), Range(-5., 5.));
  data->plotOn(plot);

  auto plot2 = sum2->frame(Bins(100), Title("Sum of 2 Random variables"),
                           Range(-5., 5.));
  data->plotOn(plot2);

  auto plot3 = sum3->frame(Bins(100), Title("Sum of 3 Random variables"),
                           Range(-5., 5.));
  data->plotOn(plot3);

  auto plot10 = sum10->frame(Bins(100), Title("Sum of 10 Random variables"),
                             Range(-5., 5.));
  data->plotOn(plot10);
  gaus.plotOn(plot10);

  auto c = new TCanvas();
  c->Divide(2, 2);

  c->cd(1);
  plot->Draw();
  c->cd(2);
  plot2->Draw();
  c->cd(3);
  plot3->Draw();
  c->cd(4);
  plot10->Draw();

  return 1;
}
