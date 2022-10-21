#pragma once

#include <afxsock.h>


#define WM_TCPIP_RECEIVED   ( WM_USER + 3 ) 

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

public:

	Socket() ;

	bool Create( HWND const & hwnd ) ;
	bool Connect( CString const & ipStr , int32_t const & port ) ;
	bool Send( uint8_t const * data , int32_t const & len ) ;

	bool const & IsConnected() const ;
	bool const & IsCreated() const ;

	void Close() ;

	void Wait( DWORD dwMillisecond ) const ;

	void OnReceive( int32_t errorCode ) ;

	char const * GetData() const ;
} ;
