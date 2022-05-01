#pragma once

#define MSG_UNDEFINED			0
#define MSG_UPDATE				1
#define MSG_DRAW				2
//Mouse messages
#define MSG_MOUSEMOTION			3
#define MSG_MOUSEBUTTONDOWN		4
#define MSG_MOUSEBUTTONUP		5
#define MSG_MOUSEWHEEL			6
#define MSG_MOUSEENTER			7
#define MSG_MOUSELEAVE			8
#define MSG_MOUSECLICK			9
//Keyboard messages
#define MSG_KEYDOWN				10
#define MSG_KEYUP				11
//Control messages
#define MSG_BUTTON_CLICKED		100
#define MSG_TOOLWINDOW_CLOSED	200
#define MSG_CHECKBOX_CLICKED	300

//#define MSG_RESULT_UNPROCESSED	0
//#define MSG_RESULT_CONSUMED		1

class Message
{
public:
	int				type;
	SDL_Event*		sdlEvent;
	void*			sender;
	int				param1;
	int				param2;
};