#pragma once

// CChatSocket ÃüÁîÄ¿±ê

class CChatSocket : public CAsyncSocket
{
public:
	CChatSocket();
	virtual ~CChatSocket();
	virtual void OnReceive(int nErrorCode);
};


