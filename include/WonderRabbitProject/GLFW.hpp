#pragma once

#include <memory>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <functional>
#include <string>

#ifdef _LOGGING_H_
  #define WRP_GLOG_ENABLED
#endif

#define WRP_GLEW
namespace WonderRabbitProject { namespace GLEW {
  namespace C
  {
    #include <GL/glew.h>
  }
} }

#define WRP_GLFW
namespace WonderRabbitProject { namespace GLFW {
  
  namespace C
  {
    #define GLFW_NO_GLU
    #include <GL/glfw.h>
    #undef  GLFW_NO_GLU
  }

  // [TOOL] regex enum scope helper
  // pattern    : #undef GLFW_KEY_(.+)
  // replacement:     \1 = GLFW_KEY_\1,\n    \0

  #include "./GLFW/WINDOW_MODE.hpp"
  #include "./GLFW/KEY.hpp"
  #include "./GLFW/WINDOW_PARAM.hpp"
  #include "./GLFW/OPEN_WINDOW_HINT_TARGET.hpp"

  #include "./GLFW/BOOL.hpp"
  #include "./GLFW/CLEAR_BUFFER_BIT.hpp"

  template
  < unsigned DEFAULT_WIDTH      = 0, unsigned DEFAULT_HEIGHT       = 0
  , unsigned DEFAULT_RED_BITS   = 0, unsigned DEFAULT_GREEN_BITS   = 0
  , unsigned DEFAULT_BLUE_BITS  = 0, unsigned DEFAULT_ALPHA_BITS   = 0
  , unsigned DEFAULT_DEPTH_BITS = 0, unsigned DEFAULT_STENCIL_BITS = 0
  , unsigned DEFAULT_MODE       = unsigned(WINDOW_MODE::WINDOW)
  , unsigned DEFAULT_EXIT_KEY   = unsigned(KEY::ESC)
  , unsigned DEFAULT_SWAP_INTERVAL = 1
  , int DEFAULT_CLEAR_BUFFER_BIT = int(CLEAR_BUFFER_BIT::ALL)
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
    static constexpr unsigned
      default_swap_interval = DEFAULT_SWAP_INTERVAL;
    static constexpr CLEAR_BUFFER_BIT
      default_clear_buffer_bit = CLEAR_BUFFER_BIT(DEFAULT_CLEAR_BUFFER_BIT);
    unsigned
      width      = default_width     , height       = default_height      ,
      red_bits   = default_red_bits  , green_bits   = default_green_bits  ,
      blue_bits  = default_blue_bits , alpha_bits   = default_alpha_bits  ,
      depth_bits = default_depth_bits, stencil_bits = default_stencil_bits,
      ;
    WINDOW_MODE mode = WINDOW_MODE(default_mode);
    KEY exit_key = KEY(default_exit_key);
    int swap_interval = default_swap_interval;
    CLEAR_BUFFER_BIT clear_buffer_bit = CLEAR_BUFFER_BIT(default_clear_buffer_bit);
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

    ~glfw()
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "--> WRP::GLFW::glfw::dtor";
        LOG(INFO) << "to quick_exit(0)";
      #endif
      quick_exit(0);
    }

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
          i.reset( new this_type() );
          #ifdef WRP_GLOG_ENABLED
            LOG(INFO) << "new instance; address of instance is " << std::hex << i.get();
          #endif
        }
      }
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "returning instance address is " << std::hex << i.get();
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
      //#ifdef WRP_GLOG_ENABLED
      //  LOG_EVERY_N(INFO, 60)
      //    << "/60 WRP::GLFW::key; with key_ is "
      //    << to_string(key_);
      //#endif
      auto r = bool(C::glfwGetKey(int(key_)));
      #ifdef WRP_GLOG_ENABLED
        LOG_IF(INFO, r) << "key" << to_string(key_) << " is fire";
      #endif
      return r;
    }

    inline void auto_clear(bool f = true)
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "WRP::GLFW::auto_clear : " << std::boolalpha << f;
      #endif
      clear_ = f
        ? [this]{ this->clear(); }
        : []{}
        ;
    }

    inline void auto_swap(bool f = true)
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "WRP::GLFW::auto_swap : " << std::boolalpha << f;
      #endif
      swap_ = f
        ? [this]{ this->swap(); }
        : []{}
        ;
    }

    inline void clear(
      const CLEAR_BUFFER_BIT color_buffer_bit
        = configurator_type::default_clear_buffer_bit
    ) const
    {
      //#ifdef WRP_GLOG_ENABLED
      //  LOG_EVERY_N(INFO, 60)
      //    << "/60 WRP::GLFW::clear; with color_buffer_bit is "
      //    << std::hex << color_buffer_bit;
      //#endif
      #ifdef WRP_GLEW
      WonderRabbitProject::GLEW::
      #endif
      C::glClear(int(color_buffer_bit));
    }
    
    inline void swap() const
    {
      //#ifdef WRP_GLOG_ENABLED
      //  LOG_EVERY_N(INFO, 60) << "/60 WRP::GLFW::swap";
      //#endif
      C::glfwSwapBuffers();
    }

    inline void exit() const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "WRP::GLFW::exit";
      #endif
      quick_exit(0);
    }
    
    inline void swap_interval(unsigned n)
    {
      conf_.swap_interval = n;
      swap_interval_(n);
    }

    inline void window_title(std::string&& v) const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "WRP::GLFW::window_title; " << v;
      #endif
      C::glfwSetWindowTitle(v.data());
    }

    template<class TINT>
    inline void hint(HINT t, TINT value) const
    {
      #ifdef WRP_GLOG_ENABLED
        using std::to_string;
        LOG(INFO)
          << "WRP::GLFW::open_window_hint : "
          << to_string(t) << " = " << to_string(value);
      #endif
      C::glfwOpenWindowHint(int(t), int(value));
    }

    template<class TINT>
    inline void hint(std::tuple<HINT, TINT>&& p) const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "open_window_hint(tuple)";
      #endif
      hint(std::get<0>(p), std::get<1>(p));
    }

    template<class T, class ... TS>
    inline void hints(T&& p ,TS ... ts) const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "open_window_hint<...>";
      #endif
      hint(std::move(p));
      hints(ts ...);
    }

  private:
    static std::unique_ptr<this_type> i;
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
    
    inline void hints() const {}
    
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
    
    void initialize()
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
      auto_clear();
      auto_swap();
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
      swap_interval_(conf_.swap_interval);
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::window";
      #endif
    }
    
    inline void swap_interval_(unsigned n) const
    {
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "WRP::GLFW::swap_interval; " << n;
      #endif
      C::glfwSwapInterval(int(n));
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
        clear_();
        main_();
        swap_();
      }
      #ifdef WRP_GLOG_ENABLED
        LOG(INFO) << "<-- WRP::GLFW::glfw::main_loop";
      #endif
    }
    
    main_type         main_;
    configurator_type conf_;
    
    std::function<void()>
      clear_,
      swap_;
  };
  
  template<class TCONF, class TMAIN>
  std::mutex glfw<TCONF, TMAIN>::m;
  
  template<class TCONF, class TMAIN>
  std::unique_ptr<glfw<TCONF, TMAIN>> glfw<TCONF, TMAIN>::i;
  
} }

#undef WRP_GLOG_ENABLED

