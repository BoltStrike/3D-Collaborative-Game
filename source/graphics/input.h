#ifndef INPUT_H
#define INPUT_H

// Operating system dependent libraries
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string>
#include <unordered_map>

#include "../../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include "../generic/program_log.h"

namespace in {	// All of these public functions are under the "in" scope

extern double cursor_x;				// Mouse position
extern double cursor_y;				
extern double scroll_x;				// Scroll wheel position
extern double scroll_y;

// Access functions
bool btn(int);						// True if button is pressed
void get_mouse(double&, double&);	// Return mouse location
void get_scroll(double&, double&);	// Return scroll location
void poll_events();					// Polls I/O events
float get_time();					// Gets the time since program start (sec)

// Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow*, int, int, int, int);
void mouse_button_callback(GLFWwindow*, int, int, int);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Unordered maps containing paired inputs
extern std::unordered_map<int, bool> glfwinputs;		// Map GLFW ID to bool

// Constants for keyboard key IDs
constexpr static int A = GLFW_KEY_A;
constexpr static int B = GLFW_KEY_B;
constexpr static int C = GLFW_KEY_C;
constexpr static int D = GLFW_KEY_D;
constexpr static int E = GLFW_KEY_E;
constexpr static int F = GLFW_KEY_F;
constexpr static int G = GLFW_KEY_G;
constexpr static int H = GLFW_KEY_H;
constexpr static int I = GLFW_KEY_I;
constexpr static int J = GLFW_KEY_J;
constexpr static int K = GLFW_KEY_K;
constexpr static int L = GLFW_KEY_L;
constexpr static int M = GLFW_KEY_M;
constexpr static int N = GLFW_KEY_N;
constexpr static int O = GLFW_KEY_O;
constexpr static int P = GLFW_KEY_P;
constexpr static int Q = GLFW_KEY_Q;
constexpr static int R = GLFW_KEY_R;
constexpr static int S = GLFW_KEY_S;
constexpr static int T = GLFW_KEY_T;
constexpr static int U = GLFW_KEY_U;
constexpr static int V = GLFW_KEY_V;
constexpr static int W = GLFW_KEY_W;
constexpr static int X = GLFW_KEY_X;
constexpr static int Y = GLFW_KEY_Y;
constexpr static int Z = GLFW_KEY_Z;
constexpr static int SPACE = GLFW_KEY_SPACE;
constexpr static int LSHIFT = GLFW_KEY_LEFT_SHIFT;
constexpr static int ESCAPE = GLFW_KEY_ESCAPE;

// Constants for mouse button IDs
constexpr static int LMOUSE = GLFW_MOUSE_BUTTON_LEFT;
constexpr static int RMOUSE = GLFW_MOUSE_BUTTON_RIGHT;
constexpr static int MMOUSE = GLFW_MOUSE_BUTTON_MIDDLE;

} // namespace in

#endif
