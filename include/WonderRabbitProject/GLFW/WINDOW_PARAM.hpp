enum class WINDOW_PARAM : unsigned
{
  OPENED = GLFW_OPENED,
  ACTIVE = GLFW_ACTIVE,
  ICONIFIED = GLFW_ICONIFIED,
  ACCELERATED = GLFW_ACCELERATED,
  RED_BITS = GLFW_RED_BITS,
  GREEN_BITS = GLFW_GREEN_BITS,
  BLUE_BITS = GLFW_BLUE_BITS,
  ALPHA_BITS = GLFW_ALPHA_BITS,
  DEPTH_BITS = GLFW_DEPTH_BITS,
  STENCIL_BITS = GLFW_STENCIL_BITS
};

#ifndef WRP_GLFW_NOT_UNDEF
  #undef GLFW_OPENED
  #undef GLFW_ACTIVE
  #undef GLFW_ICONIFIED
  #undef GLFW_ACCELERATED
  #undef GLFW_RED_BITS
  #undef GLFW_GREEN_BITS
  #undef GLFW_BLUE_BITS
  #undef GLFW_ALPHA_BITS
  #undef GLFW_DEPTH_BITS
  #undef GLFW_STENCIL_BITS
#endif

