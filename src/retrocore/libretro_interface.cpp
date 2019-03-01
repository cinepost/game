#include <cstring>

//#include "libretro-common/glsym/glsym_gl.cl.h"
#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#include "libretro.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
static struct retro_hw_render_callback hw_render;

#if defined(HAVE_PSGL)
#define RARCH_GL_FRAMEBUFFER GL_FRAMEBUFFER_OES
#define RARCH_GL_FRAMEBUFFER_COMPLETE GL_FRAMEBUFFER_COMPLETE_OES
#define RARCH_GL_COLOR_ATTACHMENT0 GL_COLOR_ATTACHMENT0_EXT
#elif defined(OSX_PPC)
#define RARCH_GL_FRAMEBUFFER GL_FRAMEBUFFER_EXT
#define RARCH_GL_FRAMEBUFFER_COMPLETE GL_FRAMEBUFFER_COMPLETE_EXT
#define RARCH_GL_COLOR_ATTACHMENT0 GL_COLOR_ATTACHMENT0_EXT
#else
#define RARCH_GL_FRAMEBUFFER GL_FRAMEBUFFER
#define RARCH_GL_FRAMEBUFFER_COMPLETE GL_FRAMEBUFFER_COMPLETE
#define RARCH_GL_COLOR_ATTACHMENT0 GL_COLOR_ATTACHMENT0
#endif

#define BASE_WIDTH 480
#define BASE_HEIGHT 272
#ifdef HAVE_OPENGLES
#define MAX_WIDTH 1024
#define MAX_HEIGHT 1024
#else
#define MAX_WIDTH 2048
#define MAX_HEIGHT 2048
#endif

static unsigned width  = BASE_WIDTH;
static unsigned height = BASE_HEIGHT;

// Callbacks
static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static retro_environment_t environ_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;

#include "svq/app.h"
svq::App app(true); // libretro version

unsigned retro_api_version(void)
{
    return RETRO_API_VERSION;
}

void retro_cheat_reset(void)
{

}

void retro_cheat_set(unsigned index, bool enabled, const char *code) {

}

bool retro_load_game(const struct retro_game_info *info) {
    return true;
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
    return false;
}

void retro_unload_game(void) {

}

unsigned retro_get_region(void) {
    return RETRO_REGION_NTSC;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {

}

void *retro_get_memory_data(unsigned id) {
    return NULL;
}

size_t retro_get_memory_size(unsigned id) {
    return 0;
}

size_t retro_serialize_size(void) {
    return 0;
}

bool retro_serialize(void *data, size_t size) {
    return false;
}

bool retro_unserialize(const void *data, size_t size) {
    return false;
}

void retro_deinit(void) {
}

void retro_set_environment(retro_environment_t cb) {
   environ_cb = cb;

   struct retro_variable variables[] = {
      {
         "testgl_resolution",
#ifdef HAVE_OPENGLES
         "Internal resolution; 320x240|360x480|480x272|512x384|512x512|640x240|640x448|640x480|720x576|800x600|960x720|1024x768",
#else
         "Internal resolution; 320x240|360x480|480x272|512x384|512x512|640x240|640x448|640x480|720x576|800x600|960x720|1024x768|1024x1024|1280x720|1280x960|1600x1200|1920x1080|1920x1440|1920x1600|2048x2048",
#endif
      },
#ifdef CORE
      { "testgl_multisample", "Multisampling; 1x|2x|4x" },
#endif
      { NULL, NULL },
   };

   bool no_rom = true;
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);
   cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }


void retro_init(void) {
    //app.init();
}

void retro_get_system_info(struct retro_system_info *info) {
    memset(info, 0, sizeof(*info));
    info->library_name = "SOVOQ";
    info->library_version = "0.1";
    info->need_fullpath = false;
    info->valid_extensions = "npgd"; // looks like Narrow Packed Game Data , but ... ha ha ! It's "Nu Pogodi !"
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
    int pixel_format = RETRO_PIXEL_FORMAT_XRGB8888;

    memset(info, 0, sizeof(*info));
    info->timing.fps            = 60.0f;
    info->timing.sample_rate    = 22050;
    info->geometry.base_width   = width;
    info->geometry.base_height  = height;
    info->geometry.max_width    = width;
    info->geometry.max_height   = height;
    info->geometry.aspect_ratio = (float)width / (float)height;

    environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixel_format);
}

void retro_reset(void) { }

static void update_variables(void)
{
   struct retro_variable var = {
      .key = "testgl_resolution",
   };

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      char *pch;
      char str[100];
      snprintf(str, sizeof(str), "%s", var.value);
      
      pch = strtok(str, "x");
      if (pch)
         width = strtoul(pch, NULL, 0);
      pch = strtok(NULL, "x");
      if (pch)
         height = strtoul(pch, NULL, 0);

      fprintf(stderr, "[libretro-test]: Got size: %u x %u.\n", width, height);
   }

#ifdef CORE
   var.key = "testgl_multisample";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      switch (*var.value)
      {
         case '1':
            init_multisample(1);
            break;

         case '2':
            init_multisample(2);
            break;

         case '4':
            init_multisample(4);
            break;
      }
   }
#endif
}

static unsigned frame_count;

void retro_run(void) {
    bool updated = false;
    //if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
    //    update_variables();

    input_poll_cb();

    //glBindFramebuffer(RARCH_GL_FRAMEBUFFER, hw_render.get_current_framebuffer());
    //app.onRender();

    video_cb(RETRO_HW_FRAME_BUFFER_VALID, width, height, 0);
}

static void context_reset(void)
{
   fprintf(stderr, "Context reset!\n");
   //rglgen_resolve_symbols(hw_render.get_proc_address);
}
