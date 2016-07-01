// Déclaration des librairies standard c++
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// Déclaration des librairies propres ChannelFlow
#include "channelflow/chebyshev.h"
#include "channelflow/flowfield.h"
#include "channelflow/dns.h"
#include "channelflow/turbstats.h"
#include "channelflow/periodicfunc.h"

using namespace std;
using namespace channelflow;

int main(){
  cout << setprecision(17);

  const Real Reynolds = 400;
  const Real nu = 1.0/Reynolds;

  const Real dtmin = 0.00001;
  const Real dtmax = 0.06;
  const Real CFLmin = 0.30;
  const Real CFLmax = 0.40;
  const Real dT =1; // pas d'enregistrement de l'énergie de perturbation
  const Real T0 = 0.0;
  const Real T1 = 1000.0;

  // chargement des données
  FlowField u("gd/j/ju0.ff");
  FlowField q(u.Nx(), u.Ny(), u.Nz(), 1, u.Lx(), u.Lz(), u.a(), u.b());
  FlowField tmp(u.Nx(), u.Ny(), u.Nz(), 6, u.Lx(), u.Lz(), u.a(), u.b());

  Real a = u.a();
  Real b = u.b();
  int Ny = u.Ny();

  Vector y = chebypoints(Ny, a, b);
  ChebyTransform tran(Ny);
  DNSFlags flags;

  // Paramétrage de l'écoulement
  flags.baseflow = PlaneCouette;
  flags.timestepping = SBDF3;
  flags.initstepping = CNRK2;
  flags.nonlinearity = Rotational;
  flags.dealiasing = DealiasXZ;
  flags.constraint = BulkVelocity;
  flags.dPdx = 0.0;
  flags.Ubulk = 0.0;

  // définition pour les pas de temps variable
  TimeStep dt((dtmin + dtmax) / 2, dtmin, dtmax, dT, CFLmin, CFLmax);
  DNS dns(u, nu, dt, flags, T0);
  ChebyCoeff u00mean(u.My(), a, b, Spectral);
  Real dragmean = 0.0;
  int count = 0;
  ChebyCoeff Ubase(Ny, a, b, Physical);
  for (int ny = 0; ny < Ny; ++ny){
    Ubase[ny] = y[ny];

    TurbStats stats(Ubase, nu);
    // Affichage des informations de simulation
    cout << "Re = " << Reynolds << endl;
    cout << " Lx = " << u.Lx << endl;
    cout << " Lz = " << u.Lz << endl;
    cout << " Ly = " << u.Ly << endl;
    cout << " Nx = " << u.Nx << endl;
    cout << " Nz = " << u.Nz << endl;
    cout << " Ny = " << u.Ny << endl;


    ofstream fichier("gd/j/energie.txt", ios :: out | ios :: trunc);

    for (Real t=T0; t<=T1; t += dt){
      string time = i2s(int(t));
      fichier << t << "\t" << L2Norm(u) << "\t" << endl;
      ChebyCoeff u00 = Re(u.profile(0,0,0));
      ChebyCoeff du00dy=diff(u00);
      Real drag = nu*(du00dy.eval_a() + du00dy.eval_b());
      stats.addData(u,tmp);
      u00mean += u00;
      dragmean += drag;
      ++count;

      ChebyCoeff uv = stats.uv();
      ChebyCoeff uu = stats.uu();
      ChebyCoeff vv = stats.vv();
      ChebyCoeff ww = stats.ww();
      uv.makephysical();
      uu.makephysical();
      ww.makephysical();

      int b;
      a = t / (10 * dT);
      b = int(t/(10*dT));
      if (a==b){
        u.binarySave("gd/j/u" + time);
      }
      cout << "t = " << t << endl;
      dns.advance(u,q, dt.n());
      if (dt.adjust(dns.CFL())){
        cout << "Adaptation du pas de temps au CFL" << endl;
        dns.reset_dt(dt);
      }
    }
    u.binarySave("u_f"); // sauvegarde de l'état final
    fichier.close();
  }


}
