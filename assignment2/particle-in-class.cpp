// Karl Yerkes
// 2022-01-20

#include "al/app/al_App.hpp"
#include "al/app/al_GUIDomain.hpp"
#include "al/math/al_Random.hpp"
#include "al/math/al_Vec.hpp"

using namespace al;

#include <fstream>
#include <vector>
using namespace std;

Vec3f randomVec3f(float scale) {
  return Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) * scale;
}
string slurp(string fileName);  // forward declaration


class Like {
  public:
  int i, j;
  float energy;
};

class Spring {
  public:
  int i, j;
  float length;
  float stiffness;
};
class Charge {
  public:
  int i, j;
  float energy;
};

class Hunger {
  public:
  int i, j;
  float amount;
};

struct AlloApp : App {
  Parameter pointSize{"/pointSize", "", 2.0, 1.0, 10.0};
  Parameter timeStep{"/timeStep", "", 0.1, 0.01, 0.6};
  Parameter dragFactor{"/dragFactor", "", 0.1, 0.0, 0.9};
  Parameter chargeConstant{"/chargeConstant", "", 0.09, 0.00, 0.5};
  Parameter hungryParticles{"/hungryParticles", "", 0, 0, 20};
  Parameter hungerAmount{"/hungerAmount", "", 0.1, 0.0, 1.0};
  //

  ShaderProgram pointShader;

  //  simulation state
  Mesh mesh;  // position *is inside the mesh* mesh.vertices() are the positions
  vector<Vec3f> velocity;
  vector<Vec3f> force;
  vector<float> mass;

  std::vector<Spring> spring_list;
  std::vector<Like> like_list;
  std::vector<Charge> charge_list;
  std::vector<Hunger> hunger_list;

  void onInit() override {
    // set up GUI
    auto GUIdomain = GUIDomain::enableGUI(defaultWindowDomain());
    auto &gui = GUIdomain->newGUI();
    gui.add(pointSize);  // add parameter to GUI
    gui.add(timeStep);   // add parameter to GUI
    gui.add(dragFactor);   // add parameter to GUI
     gui.add(chargeConstant);   
     gui.add(hungryParticles);   
     gui.add(hungerAmount);   
    //
  }

  void onCreate() override {
    // compile shaders
    pointShader.compile(slurp("../point-vertex.glsl"),
                        slurp("../point-fragment.glsl"),
                        slurp("../point-geometry.glsl"));

    // set initial conditions of the simulation
    //

    // c++11 "lambda" function
    auto randomColor = []() { return HSV(rnd::uniform(), 1.0f, 1.0f); };

    mesh.primitive(Mesh::POINTS);
    // does 1000 work on your system? how many can you make before you get a low
    // frame rate? do you need to use <1000?
    for (int _ = 0; _ < 20; _++) {
      mesh.vertex(randomVec3f(5));
      mesh.color(randomColor());

      // float m = rnd::uniform(3.0, 0.5);
      float m = 3 + rnd::normal() / 2;
      if (m < 0.5) m = 0.5;
      mass.push_back(m);

      // using a simplified volume/size relationship
      mesh.texCoord(pow(m, 1.0f / 3), 0);  // s, t

      // separate state arrays
      velocity.push_back(randomVec3f(0.1));
      force.push_back(randomVec3f(1));
    }

    nav().pos(0, 0, 10);
  }

  bool freeze = false;
  void onAnimate(double dt) override {
    if (freeze) return;

    // for (int k = 0; k < spring_list.size(); ++k) {
    //   auto spring = spring_list[k];
    //   Vec3f a = mesh.vertices()[spring.i];
    //   Vec3f b = mesh.vertices()[spring.j];
    //   Vec3f displacement = b - a;
    //   float distance = displacement.mag();
    //   Vec3f f = displacement.normalize() * spring.stiffness * (distance - spring.length);
    //   force[spring.i] += f;
    //   force[spring.j] -= f;
    // }

    for (int k = 0; k < mesh.vertices().size(); ++k) {
      
      Vec3f a = mesh.vertices()[k];
      Vec3f origin = Vec3f(0,0,0);
      
      Vec3f displacement = origin - a;
      float distance = displacement.mag();
      Vec3f f = displacement.normalize() * (distance - 1);
      force[k] +=f;



      }
    
//for loop for calculating charge
    for (int k = 0; k < mesh.vertices().size(); ++k) {
      for (int l = 0; l < mesh.vertices().size(); l++){
      //auto charge = charge_list[k];
      
      Vec3f a = mesh.vertices()[k];
      Vec3f b = mesh.vertices()[l];
     //charge code here
     if (a != b) {

      Vec3f pointDisplacement = b - a;
      float distance = pointDisplacement.mag();
      //if (distance > 0.01f) continue; 
      Vec3f direction = pointDisplacement.normalize();
      Vec3f chargeForce =  direction * chargeConstant * (1.0f / distance );

      // std::cout << mesh.vertices()[k] << std::endl;

      std::cout << chargeForce.z << std::endl << std::flush;

      force[k] -=chargeForce;
      force[l] +=chargeForce;
     }

      }
      //char
    }

    //create hunger list 
    //hunger_list.clear();
    for (int n = 0; n < hungryParticles; ++n){
     int i = rnd::uniform(mesh.vertices().size());
    int j = rnd::uniform(mesh.vertices().size());
    while (i == j) {
        j = rnd::uniform(mesh.vertices().size());
      }
      // i and j are different particles....
      hunger_list.push_back({i, j});
    }
    //hunger calc
    for (int k = 0; k < hunger_list.size(); ++k) { //change to hungryParticles
      if (hungryParticles != 0){
      auto hunger = hunger_list[k];

      Vec3f a = mesh.vertices()[hunger.i];
      Vec3f b = mesh.vertices()[hunger.j];
      Vec3f displacement = b - a;
      Vec3f f = displacement.normalize() * (hungerAmount/100);
      force[hunger.i] += f;

      }

      //force[hunger.j] += f;
    }


    

    

    for (int k = 0; k < like_list.size(); ++k) {
      auto like = like_list[k];
      Vec3f a = mesh.vertices()[like.i];
      Vec3f b = mesh.vertices()[like.j];
      Vec3f displacement = b - a;
      Vec3f f = displacement.normalize() * like.energy;
      force[like.i] += f;
      force[like.j] += f;
    }



    // for (int k = 0; k < charge_list.size(); ++k) {
    //   auto charge = charge_list[k];
    //   Vec3f a = mesh.vertices()[charge.i];
    //   Vec3f b = mesh.vertices()[charge.j];
    //   Vec3f displacement = b - a;
    //   if (displacement < 0.1){
    //   Vec3f
    //   }
    //   Vec3f f = displacement.normalize() * charge.energy;
    //   // force[charge.i] += f;
    //   // force[charge.j] += f;
    // }
    // Calculate forces

    for (int i = 0; i < mesh.vertices().size(); ++i) {
      for (int j = i + 1; j < mesh.vertices().size(); ++j) {
        // i and j are a pair

      // auto charge = charge_list[k];
      // charge_list.push_back({i, j, 2.0, 2.0});



      }
    }

     

    // 

    // XXX you put code here that calculates gravitational forces and sets
    // accelerations These are pair-wise. Each unique pairing of two particles
    // These are equal but opposite: A exerts a force on B while B exerts that
    // same amount of force on A (but in the opposite direction!) Use a nested
    // for loop to visit each pair once The time complexity is O(n*n)
    //
    // Vec3f has lots of operations you might use...
    // • +=
    // • -=
    // • +
    // • -
    // • .normalize() ~ Vec3f points in the direction as it did, but has length 1
    // • .normalize(float scale) ~ same but length `scale`
    // • .mag() ~ length of the Vec3f
    // • .magSqr() ~ squared length of the Vec3f
    // • .dot(Vec3f f) 
    // • .cross(Vec3f f)

    // drag
    for (int i = 0; i < velocity.size(); i++) {
      force[i] += - velocity[i] * dragFactor;
    }

    // Integration
    //
    vector<Vec3f> &position(mesh.vertices());
    for (int i = 0; i < velocity.size(); i++) {
      // "semi-implicit" Euler integration
      velocity[i] += force[i] / mass[i] * timeStep;
      position[i] += velocity[i] * timeStep;
    }

    // clear all accelerations (IMPORTANT!!)
    for (auto &a : force) a.set(0);
  }

  bool onKeyDown(const Keyboard &k) override {
    if (k.key() == ' ') {
      freeze = !freeze;
    }

    if (k.key() == '1') {
      // introduce some "random" forces
      for (int i = 0; i < velocity.size(); i++) {
        // F = ma
        force[i] += randomVec3f(1);
      }
    }

    if (k.key() == '2') {
      // choose 2 particles at random
      int i = rnd::uniform(mesh.vertices().size());
      int j = rnd::uniform(mesh.vertices().size());
      while (i == j) {
        j = rnd::uniform(mesh.vertices().size());
      }
      // i and j are different particles....
      spring_list.push_back({i, j, 2.0, 2.0});
    }

    if (k.key() == '3') {
      // choose 2 particles at random
      int i = rnd::uniform(mesh.vertices().size());
      int j = rnd::uniform(mesh.vertices().size());
      while (i == j) {
        j = rnd::uniform(mesh.vertices().size());
      }
      // i and j are different particles....
      like_list.push_back({i, j, 0.1});
    }

    //need to put somewhere else 
    // if (k.key() == '5') {
    //   // choose 2 particles at random
    //   int i = rnd::uniform(mesh.vertices().size());
    //   int j = rnd::uniform(mesh.vertices().size());
    //   while (i == j) {
    //     j = rnd::uniform(mesh.vertices().size());
    //   }
    //   // i and j are different particles....
    //   hunger_list.push_back({i, j});
    // }

    // if (k.key() == '4') {
    //   // choose 2 particles at random
    //   int i = rnd::uniform(mesh.vertices().size());
    //   int j = rnd::uniform(mesh.vertices().size());
    //   while (i == j) {
    //     j = rnd::uniform(mesh.vertices().size());
    //   }
    //   // i and j are different particles....
    //   charge_list.push_back({i, j, 0.1});
    // }

    return true;
  }

  void onDraw(Graphics &g) override {
    g.clear(0);
    g.shader(pointShader);
    g.shader().uniform("pointSize", pointSize / 100);
    g.blending(true);
    g.blendTrans();
    g.depthTesting(true);
    g.draw(mesh);

    g.color(1.0, 1.0, 0.0); // resets shader....
    Mesh springs(Mesh::LINES);
    for (int k = 0; k < spring_list.size(); ++k) {
      auto spring = spring_list[k];
      Vec3f a = mesh.vertices()[spring.i];
      Vec3f b = mesh.vertices()[spring.j];
      springs.vertex(a);
      springs.vertex(b);
    }
    g.draw(springs);
  }
};

int main() {
  AlloApp app;
  app.configureAudio(48000, 512, 2, 0);
  app.start();
}

string slurp(string fileName) {
  fstream file(fileName);
  string returnValue = "";
  while (file.good()) {
    string line;
    getline(file, line);
    returnValue += line + "\n";
  }
  return returnValue;
}
