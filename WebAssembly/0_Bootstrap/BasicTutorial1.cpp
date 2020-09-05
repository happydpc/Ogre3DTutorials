#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class BasicTutorial1: public ApplicationContext, public InputListener {
  public:
    BasicTutorial1();
    virtual ~BasicTutorial1() {}
    static void _mainLoop(void* target);

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};

BasicTutorial1::BasicTutorial1(): ApplicationContext("OgreTutorialApp") {
}

void BasicTutorial1::setup() {
  // do not forget to call the base first
  ApplicationContext::setup();
  addInputListener(this);

  // get a pointer to the already created root
  Root* root = getRoot();
  SceneManager* scnMgr = root->createSceneManager();

  // register our scene with the RTSS
  RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

  Light* light = scnMgr->createLight("MainLight");
  SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->attachObject(light);

  lightNode->setPosition(20, 80, 50);

  SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

  Camera* cam = scnMgr->createCamera("myCam");
  cam->setNearClipDistance(5); // Specifc to this sample
  cam->setAutoAspectRatio(true);
  camNode->attachObject(cam);
  camNode->setPosition(0, 0, 140);

  getRenderWindow()->addViewport(cam);

  Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");
  SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  ogreNode->attachObject(ogreEntity);

  camNode->setPosition(0, 47, 222);

  Entity* ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");
  SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
  ogreNode2->attachObject(ogreEntity2);

  Entity* ogreEntity3 = scnMgr->createEntity("ogrehead.mesh");
  SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
  ogreNode3->setPosition(0, 104, 0);
  ogreNode3->setScale(2, 1.2, 1);
  ogreNode3->attachObject(ogreEntity3);

  Entity* ogreEntity4 = scnMgr->createEntity("ogrehead.mesh");
  SceneNode* ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();
  ogreNode4->setPosition(-84, 48, 0);
  ogreNode4->roll(Degree(-90));
  ogreNode4->attachObject(ogreEntity4);
}

bool BasicTutorial1::keyPressed(const KeyboardEvent& evt) {
  if(evt.keysym.sym == SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
  }
  return true;
}

void BasicTutorial1::_mainLoop(void* target) {
  BasicTutorial1* thizz = static_cast<BasicTutorial1*>(target);
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
  BasicTutorial1 app;
  app.initApp();
  emscripten_set_main_loop_arg(BasicTutorial1::_mainLoop, &app, 0, 1);
  app.closeApp();
  return 0;
}
