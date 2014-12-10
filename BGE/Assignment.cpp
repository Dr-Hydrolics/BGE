#include "Assignment.h"
#include "Utils.h"
#include <vector>
std::vector<btHingeConstraint *> hinges;
std::vector<bool> dirs;



using namespace BGE;
	
	BGE::Assignment::Assignment(void)
	{

	}
	
	GameComponent GameManager;
	
	//btHingeConstraint john[10];
	
	bool BGE::Assignment::Initialise(){
		SetGround(make_shared<Ground>());
		setGravity(glm::vec3(0, 0, 0));
		physicsFactory->CreateCameraPhysics();
		physicsFactory->CreateGroundPhysics();
		GameManager = new GameComponent();
		
		//createDragon();
		/*for (int i = 0; i < 25; i += 5)
		{

			createAnimat(i);
		}
		*/
		createAnimat(5);
		//createPyramidyThing();

		return Game::Initialise();
	}
	
	void BGE::Assignment::addsound(){
		
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
	
	void BGE::Assignment::createAnimat(int a){
		
		int i,loc,size,height;
		size = 2;
		loc = 20;
		height = 30;
		animatBody = physicsFactory->CreateSphere(size, glm::vec3(loc, (height-5), a-5), glm::quat(), false, true);
		animatBody->transform->diffuse = glm::vec3((1.0f / 255)*(a*17), (1.0f / 255) * (a * 10), (1.0f / 255) * 76);
		
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
		int numofparts = 500.0f;
		float color_step, col;
		color_step = 1.0f/numofparts;
		for (i = 0; i < numofparts; i++){
		
			
			loc += (size + 1);

			bodyPart = physicsFactory->CreateSphere(size, glm::vec3(loc, height, a), glm::quat(), false, true);
			btHingeConstraint * hinge = new btHingeConstraint(*lastBodyPart->rigidBody, *bodyPart->rigidBody, btVector3((size), 0, 0), btVector3(-(size), 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1), true);
			//john[i] = *hinge;
			hinges.push_back(hinge);
			if (i%2 ==0){
				dirs.push_back(true);
				
				bodyPart->transform->diffuse = glm::vec3(col, (1 / 255)*(a),col);
			}
			else{
				dirs.push_back(false);
				bodyPart->transform->diffuse = glm::vec3(col, (1 / 255)*(a),col);
			}
			col += color_step;
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
			
		for (int i = 0; i < 10; i++){
			loc.y = loc.y - 4;
			loc.z = loc.z - 4;
			tempLeg = physicsFactory->CreateSphere(2,loc, glm::quat(), false, true);
			thisbit = tempLeg;
			btTransform thisBitstransform, lastBittransform;
			thisBitstransform.setIdentity();
			lastBittransform.setIdentity();
			thisBitstransform.setOrigin(GLToBtVector(loc));
			lastBittransform.setOrigin(GLToBtVector(loc));
			btFixedConstraint *lock = new btFixedConstraint(*thisbit->rigidBody, *lastbit->rigidBody, thisbit->rigidBody->getWorldTransform(), lastbit->rigidBody->getWorldTransform());
				//*thisbit->rigidBody, *lastbit->rigidBody, thisbit->rigidBody, lastbit->rigidBody);
			dynamicsWorld->addConstraint(lock);
			lastbit = thisbit;

		}
		loc.y = loc .y- 5;
		tempLeg = physicsFactory->CreateSphere(2, loc, glm::quat(), false, true);
		loc.y = loc.y - 5;
		tempLeg = physicsFactory->CreateBox(3, 1, 3, loc, glm::quat(), false, true);
	
	}
	bool dir = true;
	float total = 0;
	float colourtoat;


	void BGE::Assignment::Update(){
		float x;




		float adam = Time::deltaTime;
		total += adam;
		


			

			if (total > 2){

				for (int i = 0; i < hinges.size(); i++)
				{
					
					dir = dirs[i];
					if (dir == true){
						x = 100;
						dirs[i] = dir;
					}
					else
					{
						x = -100;
						dirs[i] = dir;
					}
					btHingeConstraint * hinge = hinges[i];
					hinge->enableAngularMotor(true, x, 100);
					hinges[i] = hinge;
				}
				total = 0;
			}
			if (dir == true){
				dir = false;
			}
			else{
				dir = true;

			}


			Game::Update();
		}







