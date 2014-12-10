#pragma once
#include "Game.h"
#include <memory>
#include "PhysicsController.h"
#include "GameComponent.h"
namespace BGE{
	class Assignment :
		public Game{
	public:
		shared_ptr<PhysicsController> box;
		shared_ptr<PhysicsController>animatBody;
		Assignment();
		
		bool Initialise();
		void createPyramidyThing();
		void createAnimat(int a);	
		void createDragon();
		void createLeg();
		void addsound();
		void Update();
	};
}

