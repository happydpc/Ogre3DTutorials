#include "Ogre.h"
#include "OgreApplicationContext.h"

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
  MyTestApp();
  void setup();
  bool keyPressed(const OgreBites::KeyboardEvent& evt);

};


MyTestApp::MyTestApp() : OgreBites::ApplicationContext("OgreTutorialApp") {
}


bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent& evt) {
  if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
  }
  return true;
}

void MyTestApp::setup(void) {
  // Do not forget to call the base first
  OgreBites::ApplicationContext::setup();

  // Register for input events
  addInputListener(this);

  // Get a pointer to the already created root
  Ogre::Root* root = getRoot();
  Ogre::SceneManager* scnMgr = root->createSceneManager();

  // Register our scene with the RTSS
  Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  // Without light we would just get a black screen
  Ogre::Light* light = scnMgr->createLight("MainLight");
  Ogre::SceneNode* ligthNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  ligthNode->setPosition(0, 10, 15);
  ligthNode->attachObject(light);

  // Also need to tell where we are
  Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(0, 0, 15);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

  // Create the camera
  Ogre::Camera* cam = scnMgr->createCamera("myCam");
  cam->setNearClipDistance(5); // Specific to this sample
  cam->setAutoAspectRatio(true);
  camNode->attachObject(cam);

  // And tell it to render into the main window
  getRenderWindow()->addViewport(cam);

  // Finally somthing to render
  Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
  Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
  node->attachObject(ent);
}

int main(int argc, char *argv[]) {
  MyTestApp app;
  app.initApp();
  app.getRoot()->startRendering();
  app.closeApp();
  return 0;
}