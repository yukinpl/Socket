#pragma once

#include <afxsock.h>
#include <string>
#include <memory>


#define WM_TCPIP_RECEIVED   ( WM_USER + 3 ) 
#define WM_TCPIP_CLOSED     ( WM_USER + 4 )
#define WM_TCPIP_ACCEPTED   ( WM_USER + 5 )

class Socket : public CSocket
{

public :
	enum class Type
	{
		Server = 0 ,
		Client = 1 ,
	} ;

public :
	static const int MaxBufferSize = 8192 ;

private :
	bool isConnected ;
	bool isCreated   ;
	bool isListened  ;

private :
	HWND hwnd ;

	char recvBuf[ MaxBufferSize ] ;

private :
	int32_t uniqueId ;

	Type type ;

	std::shared_ptr< Socket > pSocket ;

private :
	void SetHWND( HWND const & hwnd ) ;

public :

	Socket() ;

	bool CreateServer( HWND const & hwnd , int32_t const & port , int32_t const & uniqueId = 0 ) ;
	bool CreateClient( HWND const & hwnd , int32_t const & uniqueId = 0 ) ;

	bool Connect( CString const & ipStr , int32_t const & port ) ;
	bool Send( uint8_t const * data , int32_t const & len ) ;

	bool const & IsConnected() const ;
	bool const & IsCreated() const ;

	void Close() ;

	void Wait( DWORD dwMillisecond ) const ;

	void OnReceive( int32_t errorCode ) ;
	void OnClose( int32_t errorCode ) ;
	void OnAccept( int32_t errorcode ) ;

	char const * GetData() const ;

	int32_t const & GetUniqueId() const ;
} ;