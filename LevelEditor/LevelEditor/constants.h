#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdio.h>
#include <string>

const enum inputEvent{
	KEY_PRESSED,
	KEY_RELEASED,
	MOUSE_MOVED,
	MOUSE_RB_PRESSED,
	MOUSE_LB_PRESSED,
	MOUSE_RB_RELEASED,
	MOUSE_LB_RELEASED
};

const enum keyType{
	A,B,C,D,E,F,G,H,
	I,J,K,L,M,N,O,P,
	Q,R,S,T,U,V,W,X,
	Y,Z,NUM0,NUM1,NUM2,
	NUM3,NUM4,NUM5,NUM6,
	NUM7,NUM8,NUM9,F1,F2,
	F3,F4,F5,F6,F7,F8,F9,
	F10,F11,F12Escape,       
	LControl,LShift,LAlt,LSystem,      
	RControl,RShift,RAlt,RSystem,      
	Menu,LBracket,RBracket,SemiColon,    
	Comma,Period,Quote,Slash,BackSlash,
	Tilde,Equal,Dash,Space,Return,Back,         
	Tab,PageUp,PageDown,End,Home,Insert,       
	Delete,Add,Subtract,Multiply,Divide,       
	Left,Right,Up,Down,Numpad0,Numpad1,      
	Numpad2,Numpad3,Numpad4,Numpad5,      
	Numpad6,Numpad7,Numpad8,Numpad9,
	none,
};

extern const int CAMERA_SPEED;
extern const int FRAMES_PER_SECOND;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const std::string WINDOW_NAME;

#define TEXT_ENTERED 9
#endif
