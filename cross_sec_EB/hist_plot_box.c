#include "TBox.h"

void Hist::plot_box(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
		    Double_t* y, Double_t* ye_down, Double_t* ye_up)
{
  vector<TBox> boxes;
  for(int i=0; i<n; i++) {
    TBox *t = new TBox(x[i]-xe_left[i], y[i]-ye_down[i], x[i]+xe_right[i], y[i]+ye_up[i]);
    t->SetFillStyle(0);
    t->SetLineWidth(1);
    t->SetLineColor(kBlack);
    t->DrawClone("SAME");
    //    t->SetFillStyle(3325);
    //    t->SetFillColor(kBlack);
    t->DrawClone("SAME");
    cout << "drawing box " << t->GetX1() << " < x < " << t->GetX2() 
	 << ", " << t->GetY1() << " < y < " << t->GetY2() << endl;
  }
}

void Hist::plot_box_posele(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
			   Double_t* y_ele, Double_t* ye_ele_down, Double_t* ye_ele_up,
			   Double_t* y_pos, Double_t* ye_pos_down, Double_t* ye_pos_up)
{
  for(Int_t i=0; i<n; i++) {
    Double_t x1 = x[i] - xe_left[i];
    Double_t x2 = x[i] + xe_right[i];
    Double_t yc = (y_ele[i]*(lumi_data[0]+lumi_data[1]) + y_pos[i]*lumi_data[2])/total_luminosity_data;
    Double_t yl = ((y_ele[i]-ye_ele_down[i])*(lumi_data[0]+lumi_data[1]) +
		   (y_pos[i]-ye_pos_down[i])*lumi_data[2])/total_luminosity_data;
    Double_t yh = ((y_ele[i]+ye_ele_up[i])*(lumi_data[0]+lumi_data[1]) +
		   (y_pos[i]+ye_pos_up[i])*lumi_data[2])/total_luminosity_data;
    TBox *t = new TBox(x1, yl, x2, yh);
    t->SetFillStyle(0);
    t->SetLineWidth(1);
    t->SetLineColor(kBlack);
    t->DrawClone("SAME");
    t->SetFillStyle(3345);
    t->SetFillColor(kBlack);
    t->DrawClone("SAME");
    cout << "lumi_data[0] = " << lumi_data[0] << endl;
    cout << "lumi_data[1] = " << lumi_data[1] << endl;
    cout << "lumi_data[2] = " << lumi_data[2] << endl;
    cout << "lumi_data[012] = " << total_luminosity_data << endl;
    cout << "drawing box " << t->GetX1() << " < x < " << t->GetX2() 
	 << ", " << t->GetY1() << " < y < " << t->GetY2() << endl;
  }
}


void Hist::plot_box_posele_ra(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
			   Double_t* y_ele, Double_t* ye_ele_down, Double_t* ye_ele_up,
			      Double_t* y_pos, Double_t* ye_pos_down, Double_t* ye_pos_up)
{
  for(Int_t i=0; i<n; i++) {
    Double_t x1 = x[i] - xe_left[i];
    Double_t x2 = x[i] + xe_right[i];
    Double_t yc = (y_ele[i]*(lumi_data[0]+lumi_data[1]) + y_pos[i]*lumi_data[2])/total_luminosity_data;
    Double_t yl = ((y_ele[i]-ye_ele_down[i])*(lumi_data[0]+lumi_data[1]) +
		   (y_pos[i]-ye_pos_down[i])*lumi_data[2])/total_luminosity_data;
    Double_t yh = ((y_ele[i]+ye_ele_up[i])*(lumi_data[0]+lumi_data[1]) +
		   (y_pos[i]+ye_pos_up[i])*lumi_data[2])/total_luminosity_data;
    TBox *t = new TBox(x1, yl, x2, yh);
    t->SetFillStyle(0);
    t->SetLineWidth(2);
    t->SetLineColor(kRed);
    t->DrawClone("SAME");
    t->SetFillStyle(3345);
    t->SetFillColor(kRed);
    t->DrawClone("SAME");
    cout << "lumi_data[0] = " << lumi_data[0] << endl;
    cout << "lumi_data[1] = " << lumi_data[1] << endl;
    cout << "lumi_data[2] = " << lumi_data[2] << endl;
    cout << "lumi_data[012] = " << total_luminosity_data << endl;
    cout << "drawing box " << t->GetX1() << " < x < " << t->GetX2() 
	 << ", " << t->GetY1() << " < y < " << t->GetY2() << endl;
  }
}

void Hist::plot_box_posele_ra(Int_t n, Double_t* x, Double_t* xe_left, Double_t* xe_right,
			   Double_t* y_ele, Double_t* ye_ele_down, Double_t* ye_ele_up,
			      Double_t* y_pos, Double_t* ye_pos_down, Double_t* ye_pos_up, Int_t Color)
{
  for(Int_t i=0; i<n; i++) {
    Double_t x1 = x[i] - xe_left[i];
    Double_t x2 = x[i] + xe_right[i];
    Double_t yc = (y_ele[i]*(lumi_data[0]+lumi_data[1]) + y_pos[i]*lumi_data[2])/total_luminosity_data;
    Double_t yl = ((y_ele[i]-ye_ele_down[i])*(lumi_data[0]+lumi_data[1]) +
		   (y_pos[i]-ye_pos_down[i])*lumi_data[2])/total_luminosity_data;
    Double_t yh = ((y_ele[i]+ye_ele_up[i])*(lumi_data[0]+lumi_data[1]) +
		   (y_pos[i]+ye_pos_up[i])*lumi_data[2])/total_luminosity_data;
    TBox *t = new TBox(x1, yl, x2, yh);
    t->SetFillStyle(0);
    t->SetLineWidth(1);
    t->SetLineStyle(3);
    t->SetLineColor(Color);
    t->DrawClone("SAME");
    t->SetFillStyle(3345);
    t->SetFillColor(Color);
    t->DrawClone("SAME");
    cout << "lumi_data[0] = " << lumi_data[0] << endl;
    cout << "lumi_data[1] = " << lumi_data[1] << endl;
    cout << "lumi_data[2] = " << lumi_data[2] << endl;
    cout << "lumi_data[012] = " << total_luminosity_data << endl;
    cout << "drawing box " << t->GetX1() << " < x < " << t->GetX2() 
	 << ", " << t->GetY1() << " < y < " << t->GetY2() << endl;
  }
}
