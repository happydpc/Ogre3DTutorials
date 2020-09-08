#include <exception>
#include <iostream>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

using namespace Ogre;
using namespace OgreBites;

class TutorialApplication: public ApplicationContext, public InputListener {
  public:
    TutorialApplication();
    virtual ~TutorialApplication();
    static void _mainLoop(void* target);

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};

TutorialApplication::TutorialApplication(): ApplicationContext("OgreTutorialApp") {

}

TutorialApplication::~TutorialApplication(){

}

void TutorialApplication::setup() {
  //Do not forget to call the base first
  ApplicationContext::setup();
  addInputListener(this);

  //Get a pointer to the already created root
  Root* root = getRoot();
  SceneManager* scnMgr = root->createSceneManager();

  //Register our scene with the RTSS
  RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  Camera* cam = scnMgr->createCamera("myCam");

  camNode->setPosition(200, 300, 400);
  camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);

  cam->setNearClipDistance(5);
  camNode->attachObject(cam);

  Viewport* vp = getRenderWindow()->addViewport(cam);

  vp->setBackgroundColour(ColourValue(0, 0, 0));

  cam->setAspectRatio(Real(vp->getActualWidth() / Real(vp->getActualHeight())));

  scnMgr->setAmbientLight(ColourValue(0, 0, 0));
  scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);

  Entity* ninjaEntity = scnMgr->createEntity("ninja.mesh");
  ninjaEntity->setCastShadows(true);

  scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEntity);

  Plane plane(Vector3::UNIT_Y, 0);

  MeshManager::getSingleton().createPlane(
    "ground", RGN_DEFAULT,
    plane,
    1500, 1500, 20, 20,
    true,
    1, 5, 5,
    Vector3::UNIT_Z);

  Entity* groundEntity = scnMgr->createEntity("ground");
  scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

  groundEntity->setCastShadows(false);

  groundEntity->setMaterialName("Examples/Rockwall");

  Light* spotLight = scnMgr->createLight("SpotLight");

  spotLight->setDiffuseColour(0, 0, 1.0);
  spotLight->setSpecularColour(0, 0, 1.0);

  spotLight->setType(Light::LT_SPOTLIGHT);

  SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  spotLightNode->attachObject(spotLight);
  spotLightNode->setDirection(-1, -1, 0);
  spotLightNode->setPosition(Vector3(200, 200, 0));

  spotLight->setSpotlightRange(Degree(35), Degree(50));

  Light* directionalLight = scnMgr->createLight("DirectionalLight");
  directionalLight->setType(Light::LT_DIRECTIONAL);

  directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
  directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));

  SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  directionalLightNode->attachObject(directionalLight);
  directionalLightNode->setDirection(Vector3(0, -1, 1));

  Light* pointLight = scnMgr->createLight("PointLight");
  pointLight->setType(Light::LT_POINT);

  pointLight->setDiffuseColour(0.3, 0.3, 0.3);
  pointLight->setSpecularColour(0.3, 0.3, 0.3);

  SceneNode* pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  pointLightNode->attachObject(pointLight);
  pointLightNode->setPosition(Vector3(0, 150, 250));

}

bool TutorialApplication::keyPressed(const KeyboardEvent& evt) {
  if(evt.keysym.sym == SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
  }
  return true;
}

void TutorialApplication::_mainLoop(void* target) {
  TutorialApplication* thizz = static_cast<TutorialApplication*>(target);
  if (thizz->mRoot->endRenderingQueued()) {
    emscripten_cancel_main_loop();
  } else {
    try{
      if(!thizz->mRoot->renderOneFrame()) {
        emscripten_cancel_main_loop();
      }
    } catch (Ogre::Exception& e) {
      size_t length = emscripten_get_callstack(EM_LOG_C_STACK | EM_LOG_DEMANGLE | EM_LOG_NO_PATHS | EM_LOG_FUNC_PARAMS,0,0) + 50;
      std::vector<char> buffer(length);
      emscripten_get_callstack(EM_LOG_C_STACK | EM_LOG_DEMANGLE | EM_LOG_NO_PATHS | EM_LOG_FUNC_PARAMS, buffer.data(), length);
      Ogre::LogManager::getSingleton().logMessage(buffer.data());
      emscripten_pause_main_loop();
    }
  }
}


int main(int argc, char *argv[]) {
  TutorialApplication app;
  app.initApp();
  emscripten_set_main_loop_arg(TutorialApplication::_mainLoop, &app, 0, 1);
  app.closeApp();
  return 0;
}