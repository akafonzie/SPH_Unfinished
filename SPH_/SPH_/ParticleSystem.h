#ifndef ParticleSystem_h
#define ParticleSystem_h
#include "Particle.h"
#include "Container.h"
#include "modelLoader.h"
#include "KDTree.h"
#include "OctTree.h"
#include <vector>
#include<random>

using namespace std;

#define MAX_PARTICLES 3000 
#define GRAVITY 0.1f
#define SEARCH_RADIUS 0.3f

enum Dist{
	inBB,
	DamBreak,
	Random
};


class ParticleSystem{
private:
	//	Methods
	void NeighbourSearch(Particle*);
	std::vector<Particle> NSVec(Particle*);
	void PColCheck(Particle*, std::vector<Particle>*);
	void UpdateNeighbours();
	void UpdatePressure();
	void UpdateAcceleration();
	void UpdateVecs();
	void BoundaryCheck(Particle*);
	void MovePFromBounds(Particle*);
	void MoveOutOfCollision(Particle*);
	void LoadModel();
	void BuildKD();
	void SetDistribution(int);
	void BuildOT();
	void QueryOTNN(Particle*);





	//	Variables
	vector<Particle>	Particles;
	Container			container;
	BB					dim;
	model*				p_Model;
	
	bool				simPause;
	float				xc, yc, zc, px, py, pz;
	std::vector<glm::vec4> i_Positions;
	std::vector<glm::mat4> i_Models;
	std::vector<glm::vec3> i_Color;
	KDTree *pTree;
	kdtree *aTree;
	kdIter *aIter;

	OcTree* ot;

public:
	modelLoader			m_Loader;
	
	//	Methods/Functions
	ParticleSystem();
	~ParticleSystem();
	void GenParticles();
	void Run(float);
	
	void DoThisTing();
	//	Getters
	vector<Particle>*	getParticles(){return &Particles;}
	const int			getParticleCount(){return Particles.size();}
	vector<Particle>*	GetContainer(){return &Particles;}
	Particle			getParticle(int i){return Particles[i];}
	bool				GetPauseState(){return simPause;}
	model*				GetModel(){return p_Model;}
	vector<glm::vec4>*  GetIPosVec(){return &i_Positions;}
	vector<glm::mat4>*	GetIModVec(){return &i_Models;}
	vector<glm::vec3>*	GetIColVec(){return &i_Color;}
	//	Setters
	void				SetPause(bool b){simPause = b;}
};
#endif