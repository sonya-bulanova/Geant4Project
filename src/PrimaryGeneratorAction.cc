#include <G4Alpha.hh>
#include "G4Gamma.hh"
#include <G4Electron.hh>
#include <G4DynamicParticle.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

using namespace CLHEP;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

	phi_gamma = G4UniformRand() * twopi;
	while (true){
		cos_theta_gamma = -1. + 2.0*G4UniformRand();
		if (cos_theta_gamma <= -0.98994949){
			break;
		}
	}
	sin_theta_gamma = sqrt(1 - cos_theta_gamma*cos_theta_gamma);

	fParticleGun->SetParticlePosition(G4ThreeVector(5 * cm, 0, 0));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(cos_theta_gamma, sin_theta_gamma*sin(phi_gamma), sin_theta_gamma*cos(phi_gamma)));
	fParticleGun->SetParticleEnergy(20 * keV);
	fParticleGun->SetParticleDefinition(G4Gamma::Definition());
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
}
