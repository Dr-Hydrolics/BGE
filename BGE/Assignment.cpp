#include "Assignment.h"
using namespace BGE;
	
	BGE::Assignment::Assignment(void)
	{

	}
	
	GameComponent GameManager;
	
	
	bool BGE::Assignment::Initialise(){
		SetGround(make_shared<Ground>());
		setGravity(glm::vec3(0, 0, 0));
		physicsFactory->CreateCameraPhysics();
		physicsFactory->CreateGroundPhysics();
		GameManager = new GameComponent();
		createDragon();
		//createAnimat();
		//createPyramidyThing();
		return Game::Initialise();
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
		
		int i,loc,size,height;
		size = 2;
		loc = 20;
		height = 30;
		animatBody = physicsFactory->CreateSphere(size, glm::vec3(loc, (height-5), 20), glm::quat(), false, true);
		shared_ptr<PhysicsController>bodyPart, lastBodyPart, wingBodyPart;
		lastBodyPart = animatBody;
		
		
		
		/*shared_ptr<PhysicsController>leftleg = physicsFactory->CreateBox(.5, 5, .5, glm::vec3(loc, (height - 2.5), 24), glm::quat(), false, true);
		btHingeConstraint * leftLegjoint = new btHingeConstraint(*animatBody->rigidBody, *leftleg->rigidBody, btVector3(0, -3,-.6), btVector3(1, 0, 0), btVector3(1, 0, 0), btVector3(3, 0, 0), true);
		dynamicsWorld->addConstraint(leftLegjoint);
		
		shared_ptr<PhysicsController>rightleg = physicsFactory->CreateBox(.5, 5, .5, glm::vec3(loc, (height - 2.5), 24), glm::quat(), false, true);
		btHingeConstraint * rightLegjoint = new btHingeConstraint(*animatBody->rigidBody, *rightleg->rigidBody, btVector3(0, -3, .6), btVector3(1, 0, 0), btVector3(1, 0, 0), btVector3(3, 0, 0), true);
		dynamicsWorld->addConstraint(rightLegjoint);*/
		
		/*glm::quat q = glm::angleAxis(45.f, glm::vec3(1, 0, 0));
		shared_ptr<PhysicsController> Leg = physicsFactory->CreateCylinder(1, 10, glm::vec3(loc, height, 25), glm::quat(), false, true);
*/
		for (i = 0; i < 10; i++){

			loc += (size + 1);

			bodyPart = physicsFactory->CreateSphere(size, glm::vec3(loc, height, 25), glm::quat(), false, true);
			btHingeConstraint * hinge = new btHingeConstraint(*lastBodyPart->rigidBody, *bodyPart->rigidBody, btVector3((size), 0, 0), btVector3(-(size), 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), true);
			if (i == 1||i==3||i==5||i==7||i==9 ){
				hinge->enableAngularMotor(true, -100, 100);
			}
			else{
				hinge->enableAngularMotor(true, 100, 100);
			}
			dynamicsWorld->addConstraint(hinge);
		
			if (i == 3){
				
			}
			lastBodyPart = bodyPart;
		}
		


		}

	void BGE::Assignment::createDragon(){
		//animatBody = physicsFactory->CreateSphere(1, glm::vec3(10, 1, 25), glm::quat(), false, true);
		glm::quat q = glm::angleAxis(90.f, glm::vec3(0, 0, 1));
		animatBody = physicsFactory->CreateCapsule(4, 4, glm::vec3(10, 20, 25), q);
		createLeg();


	}
	void BGE::Assignment::createLeg(){
		glm::vec3 loc = glm::vec3(5, 20, 19);
		
		shared_ptr<PhysicsController> legpiece = physicsFactory->CreateSphere(2,loc , glm::quat(), false, true);
		legpiece->transform->diffuse = glm::vec3(0, 0, 0);
		shared_ptr<PhysicsController> tempLeg,lastbit,thisbit;
		
			lastbit = legpiece;
			
		for (int i = 0; i < 2; i++){
			loc.y = loc.y - 3;
			loc.z = loc.z - 3;
			tempLeg = physicsFactory->CreateSphere(2,loc, glm::quat(), false, true);
			thisbit = tempLeg;
			//btFixedConstraint *lock = new btFixedConstraint(lastbit->rigidBody,thisbit->rigidBody,lastbit->transform,thisbit->transform);
		}
		loc.y = loc .y- 4;
		tempLeg = physicsFactory->CreateSphere(2, loc, glm::quat(), false, true);
		loc.y = loc.y - 4;
		tempLeg = physicsFactory->CreateBox(3, 1, 3, loc, glm::quat(), false, true);
	}


	
	

