#include "Assignment.h"
using namespace BGE;
	
	BGE::Assignment::Assignment(void)
	{

	}

	bool BGE::Assignment::Initialise(){
		SetGround(make_shared<Ground>());
		setGravity(glm::vec3(0, -9, 0));
		physicsFactory->CreateCameraPhysics();
		physicsFactory->CreateGroundPhysics();
		createAnimat();
		return Game::Initialise();
	}

	void BGE::Assignment::Update(){
		BGE::Game::Update();
		
	}
	
	void BGE::Assignment::createPyramidyThing(){
		int i, j, k;
		int l = 50;
		for (k = 0; k < l; k += 5){
			for (j = 0; j < l; j += 5){
				for (i = 0; i < l; i += 5){

					box = physicsFactory->CreateBox(5, 5, 5, glm::vec3(i, k, j), glm::quat());

				}
			}
			l -= 5;
		}
	}
	
	void BGE::Assignment::createAnimat(){
		//animat = physicsFactory->CreateCapsule(1, 5, glm::vec3(20, 50, 25), glm::quat());
		//animat->transform->Pitch(90);
		//animat->transform->Yaw(90);
		//animat->transform->Roll(90);
		
		//animat = physicsFactory->CreateCapsuleRagdoll(glm::vec3(20, 50, 25));
		int i,loc,size;
		size = 20;
		animatBody = physicsFactory->CreateSphere(size, glm::vec3(20, 50, 25), glm::quat(), false, true);
		loc = 20;
		shared_ptr<PhysicsController>lastBodyPart,leftWing,rightWing,wingHinge;
		lastBodyPart = animatBody;
		
		
		for (i = 0; i < 5; i++){
			
			shared_ptr<PhysicsController>bodyPart;
			bodyPart = physicsFactory->CreateSphere(size, glm::vec3(loc, 50, 25), glm::quat(), false, true);
			btHingeConstraint * hinge = new btHingeConstraint(*lastBodyPart->rigidBody, *bodyPart->rigidBody, btVector3(0, 0, -1), btVector3(0, 0, 1), btVector3(1, 0, 0), btVector3(1, 0, 0), true);

			dynamicsWorld->addConstraint(hinge);
			animatBody->Attach(bodyPart);
			
			

			if (i == 3){
				
				leftWing = physicsFactory->CreateBox((7*size), (3*size), .025f, glm::vec3(loc, 50, 27), glm::quat());
				rightWing = physicsFactory->CreateBox((7 * size), (3 * size), .025f, glm::vec3(loc, 50, 23), glm::quat());
				
				btHingeConstraint * hinge = new btHingeConstraint(*bodyPart->rigidBody, *leftWing->rigidBody, btVector3(0, 0, 1), btVector3(0, 0, -1), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
				dynamicsWorld->addConstraint(hinge);
			    
				hinge = new btHingeConstraint(*bodyPart->rigidBody, *rightWing->rigidBody, btVector3(0, 0, 2.5f), btVector3(0, 0, -2.5f), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
				dynamicsWorld->addConstraint(hinge);
				
				wingHinge = bodyPart;
				
				wingHinge->Attach(leftWing);
				wingHinge->Attach(rightWing);

			}
			loc += size;
			lastBodyPart = bodyPart;

			
		}

		
		}
	

	void BGE::Assignment::Draw(){
		BGE::Game::Draw();
	}
	

