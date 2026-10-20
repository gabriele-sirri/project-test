// from $ROOTSYS/include/tmva/mvaeff.h
//
// namespace TMVA{
//
//    void mvaeffs(TString dataset, TString fin = "TMVA.root",
//                Bool_t useTMVAStyle = kTRUE, TString formula="S/sqrt(S+B)" );
//
//   // this macro plots the signal and background efficiencies
//   // as a function of the MVA cut.
//
//   ...
//
//   }
//
//  Note: given that a TFormula object is created with the formula,
//        take care of the domain where the formula is properly defined
//        otherwise the significance will not be correctly drawn
//        
//        you can exploit C++ Conditional ? : operator
//        see: https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm
//
//        example: "sqrt(2.*((S+B)*log(1.+S/B)-S))"   requires  B != 0 
//
//           ==> "(B == 0) ? 0 : sqrt(2.*((S+B)*log(1.+S/B)-S))"


void my_mvaeffs()
{
  TMVA::mvaeffs("dataset", "TMVAOutputCV.root", kTRUE,
                "(B == 0 || (S+B)*log(1.+S/B)-S < 0) ? 0 : sqrt(2.*((S+B)*log(1.+S/B)-S))");
}
