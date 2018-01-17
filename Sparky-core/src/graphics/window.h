#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace sparky { namespace graphics {

		class Window
		{
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double mx, my;


		public:
			Window(const char *name, int m_Width, int m_Height);
			~Window();

			void update();
			void clear() const;
			bool closed() const;

			inline int getwidth() const { return m_Width; }
			inline int getheight() const { return m_Height;  }

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int keycode) const;
			void getMousePostion(double& x, double& y) const;

		private:
			bool init();
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int modes);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int modes);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};

	}}