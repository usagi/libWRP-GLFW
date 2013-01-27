#ifdef GL_TRUE
  #undef GL_TRUE
  #define GL_TRUE []{static_assert(false, "use `true` if you are C++er"); return true; }()
#endif
#ifdef GL_FALSE
  #undef GL_FALSE
  #define GL_FALSE []{static_assert(false, "use `false` if you are C++er"); return false; }()
#endif

