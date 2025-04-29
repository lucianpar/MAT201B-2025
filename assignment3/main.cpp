#include "al/app/al_App.hpp"
#include "al/app/al_GUIDomain.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/math/al_Random.hpp"
#include "al/math/al_Vec.hpp"
#include <_stdlib.h>

using namespace al;

#include <fstream>
#include <vector>
using namespace std;

Vec3f randomVec3f(float scale) {
  return Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) * scale;
}

struct AlloApp : App {
  Parameter timeStep{"/timeStep", "", 0.1, 0.01, 0.6};
  Parameter clusterMargin{"/clusterMargin", "", 4.0, 1.0, 15.0};

  Light light;
  Material material;  // Necessary for specular highlights

  Mesh mesh;
  Mesh boundary;
  Mesh bigGuyMesh;
  int numAgents = 100;
  int invertDir = 1;//key click 1
  int addForce = 0;

  // size, color, species, sex, age, etc.
  std::vector<Nav> agent;
  std::vector<Nav> bigAgent;

  void onInit() override {
    auto GUIdomain = GUIDomain::enableGUI(defaultWindowDomain());
    auto &gui = GUIdomain->newGUI();
    gui.add(timeStep);
    gui.add(clusterMargin);
  }

  void onCreate() override {
    
    addSphere(boundary, 15, 100);
    boundary.primitive((Mesh:: POINTS));
    boundary.color(1.0, 1.0, 1.0);
    // for (int i = 0; i < boundary.vertices().size(); ++i){
    //   boundary.vertices()[i].color()
    // }
    

    nav().pos(0, 0, 0);
    // addSphere(mesh);
    // mesh.translate(0, 0, -0.1);
    addSphere(mesh, 0.5, 50, 50);
    mesh.primitive(Mesh::POINTS);
    //float size= 
    //mesh.scale(0.5+rnd::uniform(1.5));
    mesh.scale(1.0,0.7,0.9);
    
     
    //add code for adding legs


    mesh.generateNormals();

    addSphere(bigGuyMesh, 2.0, 50, 50);
    bigGuyMesh.primitive(Mesh::POINTS);
    //float size= 
    //mesh.scale(0.5+rnd::uniform(1.5));
    bigGuyMesh.scale(1.0,0.7,0.9);
    light.pos(0, 10, 10);

     for (int b = 0; b < 4; ++b) {
      Nav p;
      p.pos() = randomVec3f(5);
      p.quat()
          .set(rnd::uniformS(), rnd::uniformS(), rnd::uniformS(),
               rnd::uniformS())
          .normalize();
      // p.set(randomVec3f(5), randomVec3f(1));
      bigAgent.push_back(p);
    }
  


    for (int i = 0; i < numAgents; ++i) {
      Nav p;
      p.pos() = randomVec3f(5);
      p.quat()
          .set(rnd::uniformS(), rnd::uniformS(), rnd::uniformS(),
               rnd::uniformS())
          .normalize();
      // p.set(randomVec3f(5), randomVec3f(1));
      agent.push_back(p);
    }
  }

  //Vec3f food;
  double time = 0;
  void onAnimate(double dt) override {
    if (time > 7) {
      time -= 7;
      //for spawning behavior
      //food = randomVec3f(15);
      //
      //
    }
    time += dt;

    for (int i = 0; i < agent.size(); ++i) {
      //scale(aguent[i], 1.2);
      bool in_Sphere = true;
      if (agent[i].pos().mag() >= 15.0) {in_Sphere = false;}; 
    

      
      agent[i].moveF(10+addForce);
      if (in_Sphere == false){
        //int index = rnd::uniformS();
        //switch direction if encounter boundary
         agent[i].faceToward(agent[i].uf()*-1.0, 0.1);
         //uf handles front of nav position
      }
      //std::vector<Vec3f> neighbors;
      Vec3f clusterSum;
      int nInCluster = 0;
      for (int j = 0; j < agent.size(); ++j){
    
        if ((agent[i].pos() - agent[j].pos()).mag() <= clusterMargin){
        //if ((agent[i].pos() - agent[j].pos()).mag <= 2.0 )
        //neighbors.push_back(agent[j].pos());
        clusterSum +=agent[j].pos();
        nInCluster ++;

      }
      }
      Vec3f clusterCenter = clusterSum / nInCluster;
      agent[i].faceToward(clusterCenter*invertDir, 0.03);
      agent[i].step(dt);
    }

    ///////
    // for (int i = 0; i < agent.size(); ++i) {
      
    // }
  }

  bool onKeyDown(const Keyboard &k) override {
    if (k.key() == '1') {
      invertDir = -1;
      //behavior -- go to center
    }
    else{
      invertDir = 1;
    }
    // if (k.key() == '0') {
    //   invertDir = 1;
    // }
    if (k.key() == '3') {
      addForce = 5;
    }
    else{
      addForce = 0;
    }
  }

  void onDraw(Graphics &g) override {
    g.clear(0.0, 0.2, 0.5);
    g.depthTesting(true);
    g.draw(boundary);
    g.lighting(true);
    light.globalAmbient(RGB(0.5, sin(1.0), 1.0));
    light.ambient(RGB(0.5, sin(1.0), 1.0));
    light.diffuse(RGB(1, 1, 0.5));
    g.light(light);
    material.specular(light.diffuse() * 0.9);
    material.shininess(100);
    g.material(material);
    
    

    for (int i = 0; i < agent.size(); ++i) {
      g.pushMatrix();
      g.color(1.0,0.0,0.5);
      g.translate(agent[i].pos());
      g.rotate(agent[i].quat());
      g.draw(mesh);
      g.popMatrix();
    }

    for (int b = 0; b < bigAgent.size(); ++b) {
      g.pushMatrix();
      g.color(0.0, 0.5, 1.0);
      g.translate(bigAgent[b].pos());
      g.rotate(bigAgent[b].quat());
      g.draw(bigGuyMesh);
      g.popMatrix();
    }
    ;
    //g.draw(bigGuy);


    //Mesh m;
    //food
    //addSphere(m, 0.1);
    //m.generateNormals();
    //g.translate(food);
    //g.color(0, 1, 0);
    //g.draw(m);
  }
};

int main() {
  AlloApp app;
  app.configureAudio(48000, 512, 2, 0);
  app.start();
}