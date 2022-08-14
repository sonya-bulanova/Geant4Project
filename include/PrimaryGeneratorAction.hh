#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4GeneralParticleSource.hh>
#include <random>

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  void GeneratePrimaries(G4Event *anEvent) override;
  ~PrimaryGeneratorAction() {}
private:
  G4ParticleGun* fParticleGun;
  G4double cos_theta_gamma;
  G4double sin_theta_gamma;
  G4double phi_gamma;
};
