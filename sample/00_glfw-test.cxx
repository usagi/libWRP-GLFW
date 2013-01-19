#include <iostream>
#include <glog/logging.h>

#include <WonderRabbitProject/GLFW.hpp>

namespace
{
  using namespace std;
  using namespace WonderRabbitProject;

  constexpr auto name = "00_glfw-test";
  
  enum class GLOG_OUT
  {
    DEFAULT,
    STDERR
  };
  
  void glog_initialize(const GLOG_OUT out)
  {
    google::InitGoogleLogging(name);
    switch(out)
    {
    case GLOG_OUT::STDERR:
      google::LogToStderr();
    default:;
    }
    LOG(INFO) << "glog initialized";
  }
}

int main() try
{
  glog_initialize(GLOG_OUT::STDERR);
  
  using conf_type = GLFW::configurator<100, 100>;
  using glfw_type = GLFW::glfw<conf_type>;
  
  auto& glfw = glfw_type::instance();
  glfw.main([&](){
    if (glfw.key(GLFW::KEY::SPACE))
      LOG(INFO) << "SPACE!!";
  });
  glfw.invoke();
}
catch (const std::exception& e)
{ std::cerr << "exception: " << e.what(); }
catch (...)
{ std::cerr << "unknown exception"; }

