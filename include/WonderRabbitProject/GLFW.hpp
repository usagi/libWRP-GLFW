#pragma once

#include <stdexcept>
#include <thread>
#include <mutex>
#include <functional>
#include <string>

#ifdef _LOGGING_H_
  #define WRP_GLOG_ENABLED
#endif

namespace WonderRabbitProject { namespace GLFW
{
  
  namespace C
  {
    #include <GL/glfw.h>
  }

  // [TOOL] regex enum scope helper
  // pattern    : #undef GLFW_KEY_(.+)
  // replacement:     \1 = GLFW_KEY_\1,\n    \0

  enum class WINDOW_MODE : unsigned
  {
    WINDOW     = GLFW_WINDOW,
    #undef GLFW_WINDOW
    FULLSCREEN = GLFW_FULLSCREEN
    #undef GLFW_FULLSCREEN
  };

  enum class KEY : unsigned
  {
    UNKNOWN = unsigned(GLFW_KEY_UNKNOWN),
    #undef GLFW_KEY_UNKNOWN
    SPACE   = GLFW_KEY_SPACE,
    #undef GLFW_KEY_SPACE
    SPECIAL = GLFW_KEY_SPECIAL,
    //#undef GLFW_KEY_SPECIAL
    ESC     = GLFW_KEY_ESC,
    #undef GLFW_KEY_ESC
    F1      = GLFW_KEY_F1,
    #undef GLFW_KEY_F1
    F2      = GLFW_KEY_F2,
    #undef GLFW_KEY_F2
    F3      = GLFW_KEY_F3,
    #undef GLFW_KEY_F3
    F4      = GLFW_KEY_F4,
    #undef GLFW_KEY_F4
    F5      = GLFW_KEY_F5,
    #undef GLFW_KEY_F5
    F6      = GLFW_KEY_F6,
    #undef GLFW_KEY_F6
    F7      = GLFW_KEY_F7,
    #undef GLFW_KEY_F7
    F8      = GLFW_KEY_F8,
    #undef GLFW_KEY_F8
    F9      = GLFW_KEY_F9,
    #undef GLFW_KEY_F9
    F10      = GLFW_KEY_F10,
    #undef GLFW_KEY_F10
    F11      = GLFW_KEY_F11,
    #undef GLFW_KEY_F11
    F12      = GLFW_KEY_F12,
    #undef GLFW_KEY_F12
    F13      = GLFW_KEY_F13,
    #undef GLFW_KEY_F13
    F14      = GLFW_KEY_F14,
    #undef GLFW_KEY_F14
    F15      = GLFW_KEY_F15,
    #undef GLFW_KEY_F15
    F16      = GLFW_KEY_F16,
    #undef GLFW_KEY_F16
    F17      = GLFW_KEY_F17,
    #undef GLFW_KEY_F17
    F18      = GLFW_KEY_F18,
    #undef GLFW_KEY_F18
    F19      = GLFW_KEY_F19,
    #undef GLFW_KEY_F19
    F20      = GLFW_KEY_F20,
    #undef GLFW_KEY_F20
    F21      = GLFW_KEY_F21,
    #undef GLFW_KEY_F21
    F22      = GLFW_KEY_F22,
    #undef GLFW_KEY_F22
    F23      = GLFW_KEY_F23,
    #undef GLFW_KEY_F23
    F24      = GLFW_KEY_F24,
    #undef GLFW_KEY_F24
    F25      = GLFW_KEY_F25,
    #undef GLFW_KEY_F25
    UP = GLFW_KEY_UP,
    #undef GLFW_KEY_UP
    DOWN = GLFW_KEY_DOWN,
    #undef GLFW_KEY_DOWN
    LEFT = GLFW_KEY_LEFT,
    #undef GLFW_KEY_LEFT
    RIGHT = GLFW_KEY_RIGHT,
    #undef GLFW_KEY_RIGHT
    LSHIFT = GLFW_KEY_LSHIFT,
    #undef GLFW_KEY_LSHIFT
    RSHIFT = GLFW_KEY_RSHIFT,
    #undef GLFW_KEY_RSHIFT
    LCTRL = GLFW_KEY_LCTRL,
    #undef GLFW_KEY_LCTRL
    RCTRL = GLFW_KEY_RCTRL,
    #undef GLFW_KEY_RCTRL
    LALT = GLFW_KEY_LALT,
    #undef GLFW_KEY_LALT
    RALT = GLFW_KEY_RALT,
    #undef GLFW_KEY_RALT
    TAB = GLFW_KEY_TAB,
    #undef GLFW_KEY_TAB
    ENTER = GLFW_KEY_ENTER,
    #undef GLFW_KEY_ENTER
    BACKSPACE = GLFW_KEY_BACKSPACE,
    #undef GLFW_KEY_BACKSPACE
    INSERT = GLFW_KEY_INSERT,
    #undef GLFW_KEY_INSERT
    DEL = GLFW_KEY_DEL,
    #undef GLFW_KEY_DEL
    PAGEUP = GLFW_KEY_PAGEUP,
    #undef GLFW_KEY_PAGEUP
    PAGEDOWN = GLFW_KEY_PAGEDOWN,
    #undef GLFW_KEY_PAGEDOWN
    HOME = GLFW_KEY_HOME,
    #undef GLFW_KEY_HOME
    END = GLFW_KEY_END,
    #undef GLFW_KEY_END
    KP_0 = GLFW_KEY_KP_0,
    #undef GLFW_KEY_KP_0
    KP_1 = GLFW_KEY_KP_1,
    #undef GLFW_KEY_KP_1
    KP_2 = GLFW_KEY_KP_2,
    #undef GLFW_KEY_KP_2
    KP_3 = GLFW_KEY_KP_3,
    #undef GLFW_KEY_KP_3
    KP_4 = GLFW_KEY_KP_4,
    #undef GLFW_KEY_KP_4
    KP_5 = GLFW_KEY_KP_5,
    #undef GLFW_KEY_KP_5
    KP_6 = GLFW_KEY_KP_6,
    #undef GLFW_KEY_KP_6
    KP_7 = GLFW_KEY_KP_7,
    #undef GLFW_KEY_KP_7
    KP_8 = GLFW_KEY_KP_8,
    #undef GLFW_KEY_KP_8
    KP_9 = GLFW_KEY_KP_9,
    #undef GLFW_KEY_KP_9
    KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
    #undef GLFW_KEY_KP_DIVIDE
    KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
    #undef GLFW_KEY_KP_MULTIPLY
    KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
    #undef GLFW_KEY_KP_SUBTRACT
    KP_ADD = GLFW_KEY_KP_ADD,
    #undef GLFW_KEY_KP_ADD
    KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
    #undef GLFW_KEY_KP_DECIMAL
    KP_EQUAL = GLFW_KEY_KP_EQUAL,
    #undef GLFW_KEY_KP_EQUAL
    KP_ENTER = GLFW_KEY_KP_ENTER,
    #undef GLFW_KEY_KP_ENTER
    KP_NUM_LOCK = GLFW_KEY_KP_NUM_LOCK,
    #undef GLFW_KEY_KP_NUM_LOCK
    CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    #undef GLFW_KEY_CAPS_LOCK
    SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
    #undef GLFW_KEY_SCROLL_LOCK
    PAUSE = GLFW_KEY_PAUSE,
    #undef GLFW_KEY_PAUSE
    LSUPER = GLFW_KEY_LSUPER,
    #undef GLFW_KEY_LSUPER
    RSUPER = GLFW_KEY_RSUPER,
    #undef GLFW_KEY_RSUPER
    MENU = GLFW_KEY_MENU,
    //#undef GLFW_KEY_MENU
    LAST = GLFW_KEY_LAST,
    #undef GLFW_KEY_LAST
    #undef GLFW_KEY_MENU
    #undef GLFW_KEY_SPECIAL
  };

  enum class WINDOW_PARAM : unsigned
  {
    OPENED = GLFW_OPENED,
    #undef GLFW_OPENED
    ACTIVE = GLFW_ACTIVE,
    #undef GLFW_ACTIVE
    ICONIFIED = GLFW_ICONIFIED,
    #undef GLFW_ICONIFIED
    ACCELERATED = GLFW_ACCELERATED,
    #undef GLFW_ACCELERATED
    RED_BITS = GLFW_RED_BITS,
    #undef GLFW_RED_BITS
    GREEN_BITS = GLFW_GREEN_BITS,
    #undef GLFW_GREEN_BITS
    BLUE_BITS = GLFW_BLUE_BITS,
    #undef GLFW_BLUE_BITS
    ALPHA_BITS = GLFW_ALPHA_BITS,
    #undef GLFW_ALPHA_BITS
    DEPTH_BITS = GLFW_DEPTH_BITS,
    #undef GLFW_DEPTH_BITS
    STENCIL_BITS = GLFW_STENCIL_BITS
    #undef GLFW_STENCIL_BITS
  };

  template<class N = std::nullptr_t>
  std::string to_string(const KEY v)
  {
    switch(v)
    {
      case KEY::UNKNOWN: return "KEY::UNKNOWN";
      case KEY::SPACE: return "KEY::SPACE";
      case KEY::SPECIAL: return "KEY::SPECIAL";
      case KEY::ESC: return "KEY::ESC";
      case KEY::F1: return "KEY::F1";
      case KEY::F2: return "KEY::F2";
      case KEY::F3: return "KEY::F3";
      case KEY::F4: return "KEY::F4";
      case KEY::F5: return "KEY::F5";
      case KEY::F6: return "KEY::F6";
      case KEY::F7: return "KEY::F7";
      case KEY::F8: return "KEY::F8";
      case KEY::F9: return "KEY::F9";
      case KEY::F10: return "KEY::F10";
      case KEY::F11: return "KEY::F11";
      case KEY::F12: return "KEY::F12";
      case KEY::F13: return "KEY::F13";
      case KEY::F14: return "KEY::F14";
      case KEY::F15: return "KEY::F15";
      case KEY::F16: return "KEY::F16";
      case KEY::F17: return "KEY::F17";
      case KEY::F18: return "KEY::F18";
      case KEY::F19: return "KEY::F19";
      case KEY::F20: return "KEY::F20";
      case KEY::F21: return "KEY::F21";
      case KEY::F22: return "KEY::F22";
      case KEY::F23: return "KEY::F23";
      case KEY::F24: return "KEY::F24";
      case KEY::F25: return "KEY::F25";
      case KEY::UP: return "KEY::UP";
      case KEY::DOWN: return "KEY::DOWN";
      case KEY::LEFT: return "KEY::LEFT";
      case KEY::RIGHT: return "KEY::RIGHT";
      case KEY::LSHIFT: return "KEY::LSHIFT";
      case KEY::RSHIFT: return "KEY::RSHIFT";
      case KEY::LCTRL: return "KEY::LCTRL";
      case KEY::RCTRL: return "KEY::RCTRL";
      case KEY::LALT: return "KEY::LALT";
      case KEY::RALT: return "KEY::RALT";
      case KEY::TAB: return "KEY::TAB";
      case KEY::ENTER: return "KEY::ENTER";
      case KEY::BACKSPACE: return "KEY::BACKSPACE";
      case KEY::INSERT: return "KEY::INSERT";
      case KEY::DEL: return "KEY::DEL";
      case KEY::PAGEUP: return "KEY::PAGEUP";
      case KEY::PAGEDOWN: return "KEY::PAGEDOWN";
      case KEY::HOME: return "KEY::HOME";
      case KEY::END: return "KEY::END";
      case KEY::KP_0: return "KEY::KP_0";
      case KEY::KP_1: return "KEY::KP_1";
      case KEY::KP_2: return "KEY::KP_2";
      case KEY::KP_3: return "KEY::KP_3";
      case KEY::KP_4: return "KEY::KP_4";
      case KEY::KP_5: return "KEY::KP_5";
      case KEY::KP_6: return "KEY::KP_6";
      case KEY::KP_7: return "KEY::KP_7";
      case KEY::KP_8: return "KEY::KP_8";
      case KEY::KP_9: return "KEY::KP_9";
      case KEY::KP_DIVIDE: return "KEY::KP_DIVIDE";
      case KEY::KP_MULTIPLY: return "KEY::KP_MULTIPLY";
      case KEY::KP_SUBTRACT: return "KEY::KP_SUBTRACT";
      case KEY::KP_ADD: return "KEY::KP_ADD";
      case KEY::KP_DECIMAL: return "KEY::KP_DECIMAL";
      case KEY::KP_EQUAL: return "KEY::KP_EQUAL";
      case KEY::KP_ENTER: return "KEY::KP_ENTER";
      case KEY::KP_NUM_LOCK: return "KEY::KP_NUM_LOCK";
      case KEY::CAPS_LOCK: return "KEY::CAPS_LOCK";
      case KEY::SCROLL_LOCK: return "KEY::SCROLL_LOCK";
      case KEY::PAUSE: return "KEY::PAUSE";
      case KEY::LSUPER: return "KEY::LSUPER";
      case KEY::RSUPER: return "KEY::RSUPER";
      case KEY::MENU: return "KEY::MENU";
      //case KEY::LAST: return "KEY::LAST";
      default:
        #ifdef WRP_GLOG_ENABLED
          LOG(FATAL) << "unknown KEY";
        #endif
        throw std::logic_error("unkown KEY");
    }
  }
  
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
  
  template
  <
    unsigned DEFAULT_WIDTH      = 0, unsigned DEFAULT_HEIGHT       = 0,
    unsigned DEFAULT_RED_BITS   = 0, unsigned DEFAULT_GREEN_BITS   = 0,
    unsigned DEFAULT_BLUE_BITS  = 0, unsigned DEFAULT_ALPHA_BITS   = 0,
    unsigned DEFAULT_DEPTH_BITS = 0, unsigned DEFAULT_STENCIL_BITS = 0,
    unsigned DEFAULT_MODE       = unsigned(WINDOW_MODE::WINDOW),
    unsigned DEFAULT_EXIT_KEY   = unsigned(KEY::ESC)
  >
  struct configurator
  {
    static constexpr unsigned
      default_width      = DEFAULT_WIDTH     , default_height       = DEFAULT_HEIGHT      ,
      default_red_bits   = DEFAULT_RED_BITS  , default_green_bits   = DEFAULT_GREEN_BITS  ,
      default_blue_bits  = DEFAULT_BLUE_BITS , default_alpha_bits   = DEFAULT_ALPHA_BITS  ,
      default_depth_bits = DEFAULT_DEPTH_BITS, default_stencil_bits = DEFAULT_STENCIL_BITS;
    static constexpr WINDOW_MODE
      default_mode = WINDOW_MODE(DEFAULT_MODE);
    static constexpr KEY
      default_exit_key = KEY(DEFAULT_EXIT_KEY);
    unsigned
      width      = default_width     , height       = default_height      ,
      red_bits   = default_red_bits  , green_bits   = default_green_bits  ,
      blue_bits  = default_blue_bits , alpha_bits   = default_alpha_bits  ,
      depth_bits = default_depth_bits, stencil_bits = default_stencil_bits,
      ;
    WINDOW_MODE mode = WINDOW_MODE(default_mode);
    KEY exit_key = KEY(default_exit_key);
  };

  template
  <
    class TCONF = configurator<>,
    class TMAIN = std::function<void()>
  >
  struct glfw final
  {
    using configurator_type = TCONF;
    using main_type         = TMAIN;

    using this_type = glfw<configurator_type, main_type>;
    
    glfw(const this_type&) = delete;
    glfw(this_type&&)      = delete;
    this_type& operator=(const this_type&) = delete;
    this_type& operator=(this_type&&)      = delete;

    static this_type& instance()
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::instance";
      #endif
      if ( ! i )
      {
        std::lock_guard<decltype(m)> g(m);
        #ifdef WRP_GLOG_ENABLED
          LOG(INFO) << "lock_guard with mutex address is " << std::hex << &m;
        #endif
        if ( ! i ) {
          i = new this_type();
          #ifdef WRP_GLOG_ENABLED
            LOG(INFO) << "new instance; address of instance is " << std::hex << i;
          #endif
        }
      }
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "returning instance address is " << std::hex << i;
        LOG(INFO) << "<-- WRP::GLFW::glfw::instance";
      #endif
      return *i;
    }
    
    const configurator_type& conf() const
    { return conf_; }
    
    void invoke() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::invoke";
      #endif
      main_loop();
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::invoke";
      #endif
    }

    main_type main(main_type new_main)
    {
      auto old_main = main_;
      main_ = new_main;
      return std::move(old_main);
    }
    
    inline bool key(const KEY key_) const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG_EVERY_N(INFO, 60)
          << "/60 WRP::GLFW::key; with key_ is "
          << to_string(key_);
      #endif
      auto r = bool(C::glfwGetKey(int(key_)));
      #ifdef WRP_GLOG_ENABLED
        LOG_IF(INFO, r) << "key" << to_string(key_) << " is fire";
      #endif
      return r;
    }

    inline void clear(const int color_buffer_bit = GL_COLOR_BUFFER_BIT) const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG_EVERY_N(INFO, 60)
          << "/60 WRP::GLFW::clear; with color_buffer_bit is "
          << std::hex << color_buffer_bit;
      #endif
      C::glClear(color_buffer_bit);
    }
    
    inline void swap() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG_EVERY_N(INFO, 60) << "/60 WRP::GLFW::swap";
      #endif
      C::glfwSwapBuffers();
    }

    inline void exit() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "WRP::GLFW::exit";
      #endif
      quick_exit(0);
    }

    
  private:
    static this_type* i;
    static std::mutex m;
    
    glfw()
      : main_([](){})
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::ctor";
      #endif
      initialize();
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::ctor";
      #endif
    }
    
    ~glfw()
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::dtor";
        LOG(INFO) << "to quick_exit(0)";
      #endif
      quick_exit(0);
    }

    void finalize() const
    {
        #ifdef WRP_GLOG_ENABLED
          LOG(INFO) << "--> WRP::GLFW::glfw::finalize";
        #endif
        C::glfwTerminate();
        #ifdef WRP_GLOG_ENABLED
          LOG(INFO) << "glfwTerminate done";
          LOG(INFO) << "<-- WRP::GLFW::glfw::finalize";
        #endif
    }
    
    void initialize() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::initialize";
      #endif
      auto r = C::glfwInit();
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "result of glfwInit is " << r;
      #endif
      if (!r)
        throw std::runtime_error(
          std::string("glfeInit failed; code = ")
          + std::to_string(r)
        );
      window();
      at_quick_exit([]()
      {
        #ifdef WRP_GLOG_ENABLED
          LOG(INFO) << "--> at_quick_exit(WRP::GLFW::glfw::initialize::[](){})";
        #endif
        this_type::i->finalize();
        #ifdef WRP_GLOG_ENABLED
          LOG(INFO) << "<-- at_quick_exit(WRP::GLFW::glfw::initialize::[](){})";
        #endif
      });
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::initialize";
      #endif
    }
    
    void window() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::window";
        LOG(INFO) << "width       : " << configurator_type::default_width;
        LOG(INFO) << "height      : " << configurator_type::default_height;
        LOG(INFO) << "red_bits    : " << configurator_type::default_red_bits;
        LOG(INFO) << "green_bits  : " << configurator_type::default_green_bits;
        LOG(INFO) << "blue_bits   : " << configurator_type::default_blue_bits;
        LOG(INFO) << "alpha_bits  : " << configurator_type::default_alpha_bits;
        LOG(INFO) << "depth_bits  : " << configurator_type::default_depth_bits;
        LOG(INFO) << "stencil_bits: " << configurator_type::default_stencil_bits;
        LOG(INFO) << "mode        : " << to_string(configurator_type::default_mode);
      #endif
      auto r = C::glfwOpenWindow(
        static_cast<int>(configurator_type::default_width),
        static_cast<int>(configurator_type::default_height),
        static_cast<int>(configurator_type::default_red_bits),
        static_cast<int>(configurator_type::default_green_bits),
        static_cast<int>(configurator_type::default_blue_bits),
        static_cast<int>(configurator_type::default_alpha_bits),
        static_cast<int>(configurator_type::default_depth_bits),
        static_cast<int>(configurator_type::default_stencil_bits),
        static_cast<int>(configurator_type::default_mode)
      );
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "result of glfwOpenWindow is " << r;
      #endif
      if (!r)
      {
        finalize();
        throw std::runtime_error(
          std::string("glfwOpenWindow failed; code = ")
          + std::to_string(r)
        );
      }
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::window";
      #endif
    }
    
    void main_loop() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::main_loop";
      #endif
      std::lock_guard<decltype(m)> g(m);
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "lock_guard with mutex address is " << std::hex << &m;
      #endif
      while( ! key(conf_.exit_key) && C::glfwGetWindowParam(int(WINDOW_PARAM::OPENED)) )
      {
        main_();
        clear();
        swap();
      }
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::main_loop";
      #endif
    }
    
    main_type         main_;
    configurator_type conf_;
  };
  
  template<class TCONF, class TMAIN>
  std::mutex glfw<TCONF, TMAIN>::m;
  
  template<class TCONF, class TMAIN>
  glfw<TCONF, TMAIN>* glfw<TCONF, TMAIN>::i;
  
} }

#undef WRP_GLOG_ENABLED

