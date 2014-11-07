#pragma once
#include "Game.h"
namespace BGE{
	class Assignment :
		public Game

	{
	public:
		shared_ptr<PhysicsController> box;
		shared_ptr<PhysicsController>animatBody;
		Assignment();
		void Draw();
		bool Initialise();
		void Update();
		void createPyramidyThing();
		void createAnimat();
		
	};
}

