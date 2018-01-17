#include "window.h"


namespace sparky {  namespace graphics {
		
		void window_size(GLFWwindow *window, int width, int height);

		Window::Window(const char * title, int width, int height)
		{
			m_Title = title;
			m_Height = height;
			m_Width = width;
			if (!init()) {
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::update() 
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OPENGL ERROR " << error << std::endl;
			glfwPollEvents();
			glfwSwapBuffers(m_Window); 

		}

		bool Window::closed() const
				{
					return glfwWindowShouldClose(m_Window) == 1;
				}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			// TO DO: Log this and the next
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[keycode];
		}

		void Window::getMousePostion(double & x, double & y) const
		{
			x = mx;
			y = my;
		}

		bool Window::init()
		{
			if (!glfwInit()) { 
				std::cout << "glfw failed" << std::endl;
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) 
			{
				glfwTerminate();
				std::cout << "glfw window was not created" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window ,window_size);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			if (glewInit() != GLEW_OK) {
				std::cout << "glew did not initialise" << std::endl;
				return false;
			}
			std::cout << "OpenGl version " << glGetString(GL_VERSION) << std::endl;
			return true;

		}

		void window_size(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
		}
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int modes) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow * window, int button, int action, int modes)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

	}}