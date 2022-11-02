#pragma once

#include <Core/GLCore.h>


enum class EventType
{
    NONE = 0,
    WINDOW_RESIZE,
    KEYBOARD,
    MOUSE_CLICK,
    MOUSE_SCROLL
};

struct EventData
{
    GLFWwindow* GLFW_Window;
    int Event_Action;

    float Window_Height;
    float Window_Width;
    
    int Keyboad_Key;
    
    int Mouse_Button;
    double Scroll_XOffset;
    double Scroll_YOffset;
};





//#include <sstream>
//
//enum class EventType
//{
//	None = 0,
//	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
//	AppTick, AppUpdate, AppRender,
//	KeyPressed, KeyReleased, KeyTyped,
//	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
//};
//
//#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
//								virtual EventType GetEventType() const override { return GetStaticType(); }\
//								virtual const char* GetName() const override { return #type; }
//
//class Event
//{
//public:
//	virtual ~Event() = default;
//
//	bool Handled = false;
//
//	virtual EventType GetEventType() const = 0;
//	virtual const char* GetName() const = 0;
//
//};
//
//
//class MouseButtonEvent : public Event
//{
//public:
//	int GetMouseButton() const { return m_Button; }
//	virtual const char* GetName() const = 0; 
//	virtual std::string ToString() const { return GetName(); }
//
//protected:
//	MouseButtonEvent(const int button)
//		: m_Button(button) {}
//
//	int m_Button;
//};
//
//
//class MouseButtonPressedEvent : public MouseButtonEvent
//{
//public:
//	MouseButtonPressedEvent(const int button)
//		: MouseButtonEvent(button) {}
//
//	std::string ToString() const override
//	{
//		std::stringstream ss;
//		ss << "MouseButtonPressedEvent: " << m_Button;
//		return ss.str();
//	}
//
//	EVENT_CLASS_TYPE(MouseButtonPressed)
//};