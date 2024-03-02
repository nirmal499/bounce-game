#include <iostream>

// GLAD needs to be included first
#include <glad/glad.h>

// GLFW is included next
#include <GLFW/glfw3.h>

#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"

#include <btBulletDynamicsCommon.h>

#include <chrono>

#define ASSEST_FOLDER_PATH "/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/assets"

#define SAFE_DELETE(p) \
    do { \
        if (p != nullptr) { \
            delete p; \
            p = nullptr; \
        } \
    } while (false)

Camera* camera = nullptr;
LightRenderer* light = nullptr;
MeshRenderer* sphere = nullptr;
MeshRenderer* ground = nullptr;
MeshRenderer* enemy = nullptr;

GLuint sphereTexture;
GLuint groundTexture;

GLuint flatShaderProgram;
GLuint texturedShaderProgram;

/*  This object keeps track of all the physics settings and objects in the current scene. */
btDiscreteDynamicsWorld* dynamicsWorld;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void initGame();
void renderScene();
void addRigidBodies();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);

static void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

int main(){

    glfwSetErrorCallback(&glfwError);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initGame();

    /*  
        Inorder to see the sphere moving we have to the physics bodies
        We have to use the dynamicsWorld and stepSimulation functions to update
        the simulation every frame. To do this, we have to calculate the delta time
        between the previous and current frames.
 */
    auto previousTime = std::chrono::high_resolution_clock::now();

    while(!glfwWindowShouldClose(window))
    {

        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();

        dynamicsWorld->stepSimulation(dt);

        processInput(window);

        renderScene();

        glfwSwapBuffers(window);
        glfwPollEvents();

        previousTime = currentTime;
    }

    glfwTerminate();

    SAFE_DELETE(camera);
    SAFE_DELETE(light);
    SAFE_DELETE(sphere);
    SAFE_DELETE(enemy);

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true); 
    }
}

void initGame() {
	
	// Enable the depth testing
	glEnable(GL_DEPTH_TEST); 

	ShaderLoader shader;
    TextureLoader tLoader;

    /* Globally declared */
    sphereTexture = tLoader.getTextureID(ASSEST_FOLDER_PATH "/textures/globe.jpg");
    groundTexture = tLoader.getTextureID(ASSEST_FOLDER_PATH "/textures/ground.jpg");

    /* Globally declared */
	flatShaderProgram = shader.createProgram(ASSEST_FOLDER_PATH "/shader/FlatModel.vs",ASSEST_FOLDER_PATH "/shader/FlatModel.fs");
	texturedShaderProgram = shader.createProgram(ASSEST_FOLDER_PATH "/shader/TexturedModel.vs", ASSEST_FOLDER_PATH "/shader/TexturedModel.fs");
	
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));

	light = new LightRenderer(MeshType::kTriangle, camera);
    light->setProgram(flatShaderProgram);
    light->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

    //init physics
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
    dynamicsWorld->setInternalTickCallback(myTickCallback);

    addRigidBodies();

}

void renderScene(){

    glClearColor(0.0, 0.0, 0.0, 1.0);   // sets the color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    sphere->draw();
    ground->draw();
    enemy->draw();
    // light_renderer->draw();
}

void addRigidBodies(){


    /* 
        Sphere Rigid Body
        To create a rigid body, we have to specify the shape of the object and the motion state, and
        then set the mass and inertia of the objects

        create a btSphere for creating a sphere shape and set the radius as 1.0, which is the radius of our rendered sphere as well:

        set the btDefaultMotionState, where we specify the rotation and position of the sphere, as follows:
        We set the rotation to 0 and set the position of the rigid body to a distance of
        10.0f along the y-axis. We should also set the mass and inertia and calculate the inertia of the sphereShape as follows

    */
    // Sphere Rigid Body
	btCollisionShape* sphereShape = new btSphereShape(1);
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0.5, 0)));

    btScalar mass = 13.0f;
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);

    /*  create the rigid body object by passing btRiigidBodyConstructionInfo 
        set the physical properties of the rigid body, including friction and restitution
    */
    btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);

	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	sphereRigidBody->setRestitution(0.0f);
	sphereRigidBody->setFriction(1.0f);

    sphereRigidBody->setActivationState(DISABLE_DEACTIVATION);

    /*  After these necessary parameters are set, we need to add the rigid body to the
        dynamicWorld we created as follows, using the addRigidBody function of the
        dynamicsWorld: 
    */
    dynamicsWorld->addRigidBody(sphereRigidBody);

    // Sphere Mesh
	sphere = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody, "hero");
	sphere->setProgram(texturedShaderProgram);
    sphere->setTexture(sphereTexture);
    /* We don't have to set the position, as that will be set by the rigid body */
	// sphere->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

    /*  To access the name of the rendered mesh, we can set this instance as a property of
        the rigid body by using the setUserPointer property of the RigidBody class.
        setUserPointer takes a void pointer, so any kind of data can be passed into it.
        For the sake of convenience, we are just passing the instance of the
        MeshRenderer class itself. 
    */
    sphereRigidBody->setUserPointer(sphere);

    // ------------------------------------------------------------------------------------------------------------------------------- //

    // Ground Rigid body
	btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 0.5f, 4.0f));
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1.0f, 0)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, btVector3(0, 0, 0));

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	groundRigidBody->setFriction(1.0);
	groundRigidBody->setRestitution(0.0);

	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	dynamicsWorld->addRigidBody(groundRigidBody);

    // Ground Mesh
	ground = new MeshRenderer(MeshType::kCube, camera, groundRigidBody, "ground");
	ground->setProgram(texturedShaderProgram);
	ground->setTexture(groundTexture);
	ground->setScale(glm::vec3(4.0f, 0.5f, 4.0f));

    groundRigidBody->setUserPointer(ground);

    // ------------------------------------------------------------------------------------------------------------------------------- //

    // Enemy Rigid body
    btCollisionShape* shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(18.0, 1.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo rbCI(0.0f, motionState, shape, btVector3(0.0f, 0.0f, 0.0f));

	btRigidBody* rb = new btRigidBody(rbCI);

	rb->setFriction(1.0);
	rb->setRestitution(0.0);

    /*  If we set the collisionFlag of the enemy to KINEMATIC_OBJECT, you will see
        that the enemy doesn't go through the sphere but pushes it off the ground
    */
	// rb->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	rb->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

    dynamicsWorld->addRigidBody(rb);

	// Enemy Mesh
	enemy = new MeshRenderer(MeshType::kCube, camera, rb, "enemy");
	enemy->setProgram(texturedShaderProgram);
	enemy->setTexture(groundTexture);
	enemy->setScale(glm::vec3(1.0f, 1.0f, 1.0f));


	rb->setUserPointer(enemy);

    // ------------------------------------------------------------------------------------------------------------------------------- //


    /*  
        Position of MESH
        [Right Hand Coordinate System] 
        [+z is coming out the screen]
        [+y is upward]
        [+x is right]
    */
}

/*  To update the enemy's movement, we will add a tick function that will be called by the
    rigid body world. In this tick function, we will update the position of the enemy so that the
    enemy cube moves from the right of the screen to the left. We will also check whether the
    enemy has gone beyond the left-hand side of the screen. 
*/
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep){
        
        // Get enemy transform
		btTransform t(enemy->rigidBody->getWorldTransform());


		// Set enemy position
        /* -15 in x means left of x (negative x-axis) */
		t.setOrigin(t.getOrigin() + btVector3(-15, 0, 0) * timeStep);

		// Check if offScreen
		if (t.getOrigin().x() <= -18.0f) {

            /*  When the enemy goes offscreen, it will be looped around to the right of
                the screen, as shown in the following screenshot:
            */
			t.setOrigin(btVector3(18, 1, 0));
		}

		enemy->rigidBody->setWorldTransform(t);
		enemy->rigidBody->getMotionState()->setWorldTransform(t);
}