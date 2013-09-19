#include "MessageHandler.h"
#include "MessageListener.h"
#include "Util.h"
#include "common.h"

MessageHandler* MessageHandler::m_Instance = NULL;
MessageHandler* MessageHandler::Instance(){
	if(m_Instance == NULL){
		m_Instance = new MessageHandler();
	}
	return m_Instance;
}
void MessageHandler::cleanUpInstance(){
	if(m_Instance != NULL){
		delete m_Instance;
		m_Instance = NULL;
	}
}

MessageHandler::MessageHandler(){
	m_Messages = new std::vector<Message*>();
	m_MessagesToDelete = new std::vector<Message*>();
}
MessageHandler::~MessageHandler(){
	SafeVectorDelete(*m_Messages);
	SafePtrRelease(m_Messages);
}
void MessageHandler::createMessage(const int& type,MessageListener* sender,MessageListener* reciever,
						void* extraInfo,const double& timeToSend){
	createMessage(type,sender,reciever,extraInfo,timeToSend,"None");
}
void MessageHandler::createMessage(const int& type,MessageListener* sender,MessageListener* reciever,
									void* extraInfo,const double& timeToSend,const std::string& name){
	Message* msg = new Message(sender,reciever,extraInfo,timeToSend,type,name);
	m_Messages->push_back(msg);
}
void MessageHandler::createMessage(const int& type,MessageListener* sender,MessageListener* recievers[],
										void* extraInfo,const double& timeToSend,const int& numOfRecievers){
	for(int i = 0;i < numOfRecievers;i++){
		createMessage(type,sender,recievers[i],extraInfo,timeToSend);
	}
}
void MessageHandler::update(){
	for(int i = 0;i < m_MessagesToDelete->size();i++){
		for(int j = 0;j < m_Messages->size();j++){
			if((*m_Messages)[j] == (*m_MessagesToDelete)[i]){
				SafePtrRelease((*m_Messages)[j]);
				m_Messages->erase(m_Messages->begin()+j);
				break;
			}
		}
	}
	m_MessagesToDelete->clear();
	for(int i = 0;i < m_Messages->size();i++){
		(*m_Messages)[i]->timeToSend -= Util::instance()->getDelta()*100;
		if((*m_Messages)[i]->timeToSend <= 0){
			sendMessage((*m_Messages)[i]);
			deleteMessage((*m_Messages)[i]);
		}
	}
}
void MessageHandler::deleteMessage(const std::string& name){
	std::vector<Message*> msgs = *m_Messages;
	for(int i = 0;i < msgs.size();i++){
		if(msgs[i]->name == name){
			deleteMessage(msgs[i]);
		}
	}
}
void MessageHandler::deleteMessage(Message* message){
	for(int i = 0;i < m_Messages->size();i++){
		if((*m_Messages)[i] == message){
			m_MessagesToDelete->push_back(message);
		}
	}
}
void MessageHandler::sendMessage(Message* msg) const{
		msg->reciever->handleMessage(*msg);
}