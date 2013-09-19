#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

//contains a method for reciving messages.
struct Message;
class MessageHandler;
class MessageListener{
	friend class MessageHandler;
protected:
	virtual void handleMessage(const Message& msg) = 0;
};
#endif