#include "al/app/al_App.hpp"
#include "al/graphics/al_Image.hpp" 
#include "al/app/al_GUIDomain.hpp"
#include "al/math/al_Random.hpp"
#include <cstdio>
using namespace al;
#include <fstream> // for slurp()
#include <string> // for slurp()

Vec3f rvec() { return Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()); }
RGB rcolor() { return RGB(rnd::uniform(), rnd::uniform(), rnd::uniform()); }

std::string slurp(std::string fileName); // only a declaration

//llm helped me undertand hsv converion 

        Vec3f rgbToHsv(float r, float g, float b) {
    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float h = 0.0f, s = 0.0f, v = max;

    float d = max - min;
    s = max == 0.0f ? 0.0f : d / max;

    if (max == min) {
        h = 0.0f;  // undefined
    } else {
        if (max == r) {
            h = fmodf((g - b) / d + (g < b ? 6.0f : 0.0f), 6.0f);
        } else if (max == g) {
            h = (b - r) / d + 2.0f;
        } else if (max == b) {
            h = (r - g) / d + 4.0f;
        }
        h /= 6.0f;
    }

    return Vec3f(h, s, v);  // hue [0–1], saturation [0–1], value [0–1]
}
Vec3f hsvToCylinder(float h, float s, float v) {
    float angle = h * 2.0f * M_PI;  // convert hue to radians
    float x = s * cos(angle);      // x = radius * cos(hue)
    float z = s * sin(angle);      // z = radius * sin(hue)
    float y = v;                   // value as height
    return Vec3f(x, y, z);
}

        //end of llm help
class MyApp : public App {
    Mesh grid, rgb, hsl, mine;
    Mesh mesh1;
    Mesh mesh2;
    Mesh currentMesh;
    Mesh targetMesh;
    Mesh mesh3;
    Mesh mesh4;
    int stepCounter = 0;

    int meshSize;

    ShaderProgram shader;
    Parameter pointSize{"pointSize", 0.004, 0.0005, 0.015};





    void onInit() override {
        auto GUIdomain = GUIDomain::enableGUI(defaultWindowDomain());
        auto &gui = GUIdomain->newGUI();
        gui.add(pointSize);  // add parameter to GUI
    }

    void onCreate() override {


        
        auto image = Image("../testIMG.jpeg");
        if (image.width() == 0) {
            std::cout << "Image not found" << std::endl;
            exit(1);
        }

        mesh1.primitive(Mesh::POINTS); //og
        mesh2.primitive(Mesh::POINTS); //rgb
        mesh3.primitive(Mesh::POINTS); //hsv
        mesh4.primitive(Mesh::POINTS); //sculptural
        currentMesh.primitive(Mesh::POINTS);
        targetMesh.primitive(Mesh::POINTS);

        //for mesh1 - maybe make this into a function
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                auto pixel = image.at(x, y);
                mesh1.vertex(float(x) / image.width(), float(y) / image.width(), 0);
                mesh1.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                mesh1.texCoord(0.1, 0);

                mesh2.vertex(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                //std::cout << pixel.r << std::endl;
                mesh2.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                mesh2.texCoord(0.1, 0);

                Vec3f hsv = rgbToHsv(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                Vec3f hsvPos = hsvToCylinder(hsv.x, hsv.y, hsv.z);

                mesh3.vertex(hsvPos);
                // << hsvPos << std::endl;
                mesh3.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                mesh3.texCoord(0.1, 0);


                stepCounter ++;
                // all for mesh 4, setting up spiral like params
                float angle = stepCounter * 0.01;
                float radius = 1 + stepCounter * 0.00002;

                float mX = radius * cos(angle);
                float mZ= radius * sin(angle);
                float mY = stepCounter * 0.0001f;

                mesh4.vertex(mX, mY, mZ);
                // << hsvPos << std::endl;
                mesh4.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                mesh4.texCoord(0.1, 0);

                //current mesh
                
                // currentMesh.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
                // currentMesh.texCoord(0.1, 0);


                // fill in rgb, mine, and hsl meshes
            }
        }
        HSV
        currentMesh = mesh2;
        meshSize = mesh1.vertices().size();
        targetMesh = mesh2;
        //std::cout << meshSize << std::endl;

        if (currentMesh.vertices()[1].x == mesh2.vertices()[1].x){
            std::cout << "mesh vertices copied" << std::endl;
        }
        else {
             std::cout << "no" << std::endl;
        }

        

        nav().pos(0, 0, 5);

    
        if (! shader.compile(slurp("../point-vertex.glsl"), slurp("../point-fragment.glsl"), slurp("../point-geometry.glsl"))) {
            printf("Shader failed to compile\n");
            exit(1);
        }



    }

    double time = 0;
    Vec3f delta;
    //bool interp = true;

    void onAnimate(double dt) override {
        //time += dt;
        time = 100;
        //targetMesh = mesh4;

        //updatedMesh = CurrentMesh;
        // if (currentMesh.vertices()[1].x == targetMesh.vertices()[1].x) {interp = true;}
        // else{
        //     interp = false;
        // }
        if (currentMesh.vertices()[1].x != targetMesh.vertices()[1].x){
            for (int i = 0; i < meshSize; i++){
                delta = currentMesh.vertices()[i] - targetMesh.vertices()[i];
                currentMesh.vertices()[i] -=(delta/time);

             //std::cout << delta << std::endl;
        }
        }
       








        if (time < 3) {

        }


    // clear and regenerate the mesh
    // OR
    // update mesh as a linear combination of other meshes
    
    // iterate over mesh, changing its vertices. 
    }


    void onDraw(Graphics& g) override {
        g.clear(0.1);
        g.shader(shader);
        g.shader().uniform("pointSize", pointSize);
        g.blending(true);
        g.blendTrans();
        g.depthTesting(true);
        g.draw(currentMesh);
    }

    bool onKeyDown(const Keyboard& k) override {
        if (k.key() == 'q') {
            std::cout << "Exiting..." << std::endl;
            quit();
        }

        if (k.key() == ' ') {
            mesh1.reset(); // deletes all vertices and colors
            for (int i = 0; i < 100; ++i) {
                mesh1.vertex(rvec());
                mesh1.color(rcolor());
                mesh1.texCoord(0.1, 0);
            }
        }

        if (k.key() == '1') {
            targetMesh = mesh1;
        }
        if (k.key() == '2') {
            targetMesh = mesh2;
        }
        if (k.key() == '3') {
            targetMesh = mesh3;
        }
        if (k.key() == '4') {
            targetMesh = mesh4;
        }

        return true;
    }
};
int main() { MyApp().start(); }


std::string slurp(std::string fileName) {
    std::fstream file(fileName);
    std::string returnValue = "";
    while (file.good()) {
      std::string line;
      getline(file, line);
      returnValue += line + "\n";
    }
    return returnValue;
  }