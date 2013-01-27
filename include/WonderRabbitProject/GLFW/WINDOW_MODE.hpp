enum class WINDOW_MODE : unsigned
{
  WINDOW     = GLFW_WINDOW,
  FULLSCREEN = GLFW_FULLSCREEN
};

#ifndef WRP_GLFW_NOT_UNDEF
  #undef GLFW_WINDOW
  #undef GLFW_FULLSCREEN
#endif

template<class N = std::nullptr_t>
std::string to_string(const WINDOW_MODE v)
{
  switch(v)
  {
    case WINDOW_MODE::WINDOW    : return "WINDOW_MODE::WINDOW";
    case WINDOW_MODE::FULLSCREEN: return "WINDOW_MODE::FULLSCREEN";
    default:
      #ifdef WRP_GLOG_ENABLED
        LOG(FATAL) << "unknown WINDOW_MODE";
      #endif
      throw std::logic_error("unkown WINDOW_MODE");
  }
}

