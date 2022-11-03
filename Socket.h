#pragma once

#include <afxsock.h>
#include <string>


#define WM_TCPIP_RECEIVED   ( WM_USER + 3 ) 
#define WM_TCPIP_CLOSED     ( WM_USER + 4 )

class Socket : public CSocket
{

public:
	static const int MaxBufferSize = 8192 ;

private:
	bool isConnected ;
	bool isCreated ;

private:
	HWND hwnd ;

	char recvBuf[ MaxBufferSize ] ;

private:
	std::string ip ;
	int32_t port ;

	int32_t uniqueId ;

public:

	Socket() ;

	bool Create( HWND const & hwnd , int32_t const & uniqueId = 0 ) ;
	bool Connect( CString const & ipStr , int32_t const & port ) ;
	bool Send( uint8_t const * data , int32_t const & len ) ;

	bool const & IsConnected() const ;
	bool const & IsCreated() const ;

	void Close() ;

	void Wait( DWORD dwMillisecond ) const ;

	void OnReceive( int32_t errorCode ) ;
	void OnClose( int32_t errorCode ) ;

	char const * GetData() const ;

	std::string GetIp() const ;
	int32_t GetPort() const ;

	int32_t const & GetUniqueId() const ;
} ;