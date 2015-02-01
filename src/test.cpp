#include "bandit/bandit.h"
using namespace bandit;

#include "opengl/camera.h"


go_bandit([](){

describe("a camera", [](){
  NkCamera kamera;

  it("set position", [&](){
       // rotate
    AssertThat(kamera.getX(), Equals(0));
  });
  kamera.translate(glm::vec3(10,10,10));
  it("translate", [&](){
    AssertThat(kamera.getX(), Equals(10));
  });
});
});

int main(int argc, char* argv[])
{
  return bandit::run(argc, argv);
}
