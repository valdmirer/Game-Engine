#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>
#include <glm/glm.hpp> // Required header for glm::vec2

// Renderer

// Audio System
// Input System
class InputSystem {
public:
	using KeyCallback = std::function<void(int key, int action)>;

	void init(GLFWwindow* window);
	void update();

	bool isKeyDown(int key) const;
	bool isKeyJustPressed(int key) const;
	bool isKeyJustReleased(int key) const;

	glm::vec2 getMousePos() const { return m_mousePos; }
	glm::vec2 getMouseDelta() const { return m_mouseDelta; }
	bool isMouseButtonDown(int button) const;

	void onKey(int key, int scancode, int action, int mods);
	void onMouseButton(int button, int action, int mods);
	void onMouseMove(double x, double y);

private:
	static InputSystem* s_instance;

	std::unordered_map<int, bool> m_currentKeys;
	std::unordered_map<int, bool> m_previousKeys;
	std::unordered_map<int, bool> m_mouseButtons;

	glm::vec2 m_mousePos{ 0.f };
	glm::vec2 m_mouseDelta{ 0.f };
	glm::vec2 m_lastMousePos{ 0.f };

};

InputSystem* InputSystem::s_instance = nullptr;

void InputSystem::init(GLFWwindow* window) {
	s_instance = this;

	glfwSetKeyCallback(window, [](GLFWwindow*, int key, int scancode, int action, int mods) {
		s_instance->onKey(key, scancode, action, mods);
		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow*, int button, int action, int mods) {
		s_instance->onMouseButton(button, action, mods);
		});
	glfwSetCursorPosCallback(window, [](GLFWwindow*, double x, double y) {
		s_instance->onMouseMove(x, y);
		});

}

void InputSystem::update() {
	m_previousKeys = m_currentKeys;
	m_mouseDelta = m_mousePos - m_lastMousePos;
	m_lastMousePos = m_mousePos;

}
void InputSystem::onKey(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)   m_currentKeys[key] = true;
	if (action == GLFW_RELEASE) m_currentKeys[key] = false;
}

void InputSystem::onMouseButton(int button, int action, int) {
	m_mouseButtons[button] = (action == GLFW_PRESS);
}

void InputSystem::onMouseMove(double x, double y) {
	m_mousePos = { (float)x, (float)y };
}

bool InputSystem::isKeyDown(int key) const {
	auto it = m_currentKeys.find(key);
	return it != m_currentKeys.end() && it->second;
}
bool InputSystem::isKeyJustPressed(int key) const {
	auto cur = m_currentKeys.find(key);
	auto prev = m_previousKeys.find(key);
	bool nowDown = cur != m_currentKeys.end() && cur->second;
	bool wasDown = prev != m_previousKeys.end() && prev->second;
	return nowDown && !wasDown;
}

bool InputSystem::isKeyJustReleased(int key) const {
	auto cur = m_currentKeys.find(key);
	auto prev = m_previousKeys.find(key);
	bool nowDown = cur != m_currentKeys.end() && cur->second;
	bool wasDown = prev != m_previousKeys.end() && prev->second;
	return !nowDown && wasDown;
}

bool InputSystem::isMouseButtonDown(int button) const {
	auto it = m_mouseButtons.find(button);
	return it != m_mouseButtons.end() && it->second;
}

// UI
