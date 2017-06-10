#include <iostream>
#include "GL/gl3w.h"
#include "SDL.h"
#include "imgui/imgui.h"
#include "imgui_impl_sdl_gl3.h"

int main(int, char**)
{
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
   {
      printf("Error: %s\n", SDL_GetError());
      return -1;
   }

    // Setup window
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                       SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
   
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                       SDL_GL_CONTEXT_PROFILE_CORE);
   
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   
   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
   
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
   
   SDL_DisplayMode current;
   
   SDL_GetCurrentDisplayMode(0, &current);
   
   SDL_Window* window = SDL_CreateWindow("ImGui App",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         1280,
                                         720,
                                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
   
   SDL_GLContext glcontext = SDL_GL_CreateContext(window);
   
   gl3wInit();

   ImGui_ImplSdlGL3_Init(window);

   ImVec4 clear_color = ImColor(114, 114, 154);

   bool done = false;
   while (!done)
   {
      SDL_Event event;

      while (SDL_PollEvent(&event))
      {
         ImGui_ImplSdlGL3_ProcessEvent(&event);

         if (event.type == SDL_QUIT)
         {
            done = true;
         }
      }

      ImGui_ImplSdlGL3_NewFrame(window);

      {
         static float f = 0.0f;

         ImGui::Text("Hello world!");
         ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
         ImGui::ColorEdit3("clear color", (float*)&clear_color);
      }

      glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui::Render();
      SDL_GL_SwapWindow(window);
   }

   SDL_GL_DeleteContext(glcontext);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
}
