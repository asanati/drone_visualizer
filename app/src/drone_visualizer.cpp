#include "drone_visualizer.h"

// Specify app name
MyTestApp::MyTestApp() : OgreBites::ApplicationContext{"OgreTutorialApp"} {}

// Close window when esc key pressed
bool MyTestApp::keyPressed(OgreBites::KeyboardEvent const &evt) {
  if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
    return true;
  } else
    return false; // key not processed
}

void MyTestApp::setup() {
  OgreBites::ApplicationContext::setup();
  addInputListener(this); // register for input events

  SceneManager *scene = getRoot()->createSceneManager();
  scene->setAmbientLight(ColourValue{0.5, 0.5, 0.5});

  // register our scene with the RTSS
  RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scene);

  SceneNode *root_node = scene->getRootSceneNode();

//   // without light we would just get a black screen
//   // Light *light = scene->createLight("MainLight");
//   // SceneNode *light_node = root_node->createChildSceneNode();
//   // light_node->setPosition(20, 80, 50);
//   // light_node->attachObject(light);

//   // create camera so we can observe scene
  Camera *camera = scene->createCamera("MainCamera");
  camera->setNearClipDistance(5); // specific to this sample
  camera->setAutoAspectRatio(true);
  SceneNode *camera_node = root_node->createChildSceneNode();
  camera_node->setPosition(200, 300, 400);
  camera_node->lookAt(Vector3{0, 0, -1}, Node::TS_PARENT);
  camera_node->attachObject(camera);

  Viewport* vp = getRenderWindow()->addViewport(camera); // render into the main window

  vp->setBackgroundColour(ColourValue(0, 0, 0));
  camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

  // Create entities [ogre keeps only one copy of mesh in memory, so two objects
  // of same mesh ok]
  // Entity *obj_1 = scene->createEntity("ogrehead.mesh");
  // Entity *obj_2 = scene->createEntity("ogrehead.mesh");
  // Entity *obj_3 = scene->createEntity("ogrehead.mesh");

  // // Attace entities to scene
  // SceneNode *node_1 = root_node->createChildSceneNode(Vector3(10,10,10));
  // SceneNode *node_2 = node_1->createChildSceneNode(Vector3(-10,-10,-10));

  // //node_1->attachObject(obj_1);
  // node_2->setScale(2, 1.2, 1);
  // node_2->attachObject(obj_2);

  Entity* ninjaEntity = scene->createEntity("ninja.mesh");
  ninjaEntity->setCastShadows(true);
  SceneNode *node = root_node->createChildSceneNode();
  node->attachObject(ninjaEntity);

  // Create plane
  Plane plane(Vector3::UNIT_Y, 0);

  MeshManager::getSingleton().createPlane(
    "ground", RGN_DEFAULT,
    plane,
    1500, 1500, 20, 20,
    true,
    1, 5, 5,
    Vector3::UNIT_Z
  );

  Entity* groundEntity = scene->createEntity("ground");
  SceneNode* groundNode = root_node->createChildSceneNode();
  groundNode->attachObject(groundEntity);

  // Ground doesn't cast shadows
  groundEntity->setCastShadows(false);
  groundEntity->setMaterialName("Examples/Rockwall");

  scene->setAmbientLight(ColourValue(0,0,0));
  scene->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);


  Light* spotLight = scene->createLight("spotlight");
  spotLight->setDiffuseColour(0,0,1.0);
  spotLight->setSpecularColour(0,0,1.0);

  spotLight->setType(Light::LT_SPOTLIGHT);

  SceneNode* spotLightNode = root_node->createChildSceneNode();
  spotLightNode->attachObject(spotLight);
  spotLightNode->setDirection(-1, -1, 0);
  spotLightNode->setPosition(Vector3(200, 200 , 0));

  spotLight->setSpotlightRange(Degree(35), Degree(50));

  Light* directionalLight = scene->createLight("DirectionalLight");
  directionalLight->setType(Light::LT_DIRECTIONAL);

  directionalLight->setDiffuseColour(ColourValue(1, 1, 1));
  directionalLight->setSpecularColour(ColourValue(1, 1, 1));

  SceneNode* directionalLightNode = root_node->createChildSceneNode();
  directionalLightNode->attachObject(directionalLight);
  directionalLightNode->setDirection(Vector3(0,-1,1));

  Light* pointLight = scene->createLight("PointLight");
  pointLight->setType(Light::LT_POINT);

  pointLight->setDiffuseColour(0.3,0.3,0.3);
  pointLight->setSpecularColour(0.3,0.3,0.3);

  SceneNode* pointLightNode = root_node->createChildSceneNode();
  pointLightNode->attachObject(pointLight);
  pointLightNode->setPosition(Vector3(0, 150, 250));
}