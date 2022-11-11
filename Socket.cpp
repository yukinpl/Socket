#include "pch.h"
#include "Socket.h"

#include <exception>


Socket::Socket()
	: isConnected( false ) , isCreated( false ) , type( Type::Client )
{
	//CSocket::CSocket() ;
}


bool Socket::CreateServer( HWND const & hwnd , int32_t const & port , int32_t const & uniqueId )
{
	try
	{
		isCreated =
			( FALSE == CSocket::Create( port , SOCK_STREAM , nullptr ) ) ? false : true ;
	}
	catch( std::exception )
	{
		return isCreated ;
	}

	this->hwnd     = hwnd ;
	this->uniqueId = uniqueId ;
	this->type     = Type::Server ;

	try
	{
		isListened = ( FALSE == CSocket::Listen() ) ? false : true ;
	}
	catch( std::exception )
	{
		return isListened ;
	}

	return isListened ;
}


bool Socket::CreateClient( HWND const & hwnd , int32_t const & uniqueId )
{
	try
	{
		isCreated =
			( FALSE == CSocket::Create( 0 , SOCK_STREAM , nullptr ) ) ? false : true ;
	}
	catch( std::exception )
	{
		return isCreated ;
	}

	this->hwnd     = hwnd ;
	this->uniqueId = uniqueId ;
	this->type     = Type::Client ;

	return isCreated ;
}


bool Socket::Connect( CString const & ipStr , int32_t const & port )
{
	if( Type::Server == type )
	{
		return false ;
	}

	isConnected = ( FALSE == CSocket::Connect( ipStr , port ) ) ? false : true ;

	return FALSE == isConnected ? false : true ;
}


bool Socket::Send( uint8_t const * data , int32_t const & len )
{
	BOOL isSent
		= CSocket::Send( ( const void * ) data , len ) ;

	return FALSE == isSent ? false : true ;
}


bool const & Socket::IsConnected() const
{
	return isConnected ;
}


bool const & Socket::IsCreated() const
{
	return isCreated ;
}


void Socket::Close()
{
	if( true == isConnected || true == isCreated )
	{
		isConnected = false ;
		isCreated   = false ;

		CSocket::Close() ;
	}
	else if( true == isListened )
	{
		isListened = false ;

		CSocket::Close() ;
	}
}


void Socket::Wait( DWORD dwMillisecond ) const
{
	MSG msg ;
	ULONGLONG dwStart ;
	dwStart = GetTickCount64() ;

	while( GetTickCount64() - dwStart < dwMillisecond )
	{
		while( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) )
		{
			TranslateMessage( &msg ) ;
			DispatchMessage( &msg ) ;
		}
	}
}


void Socket::OnReceive( int32_t errorCode )
{
	uint8_t buf[ MaxBufferSize ] ;

	DWORD length ;
	IOCtl( FIONREAD , & length ) ;

	if( length > MaxBufferSize )
	{
		length = MaxBufferSize ;
	}

	Receive( buf , length ) ;

	memcpy( recvBuf , buf , length ) ;

	SendMessage( hwnd , WM_TCPIP_RECEIVED , length , ( LPARAM ) this ) ;
}


void Socket::OnClose( int32_t errorCode )
{
	SendMessage( hwnd , WM_TCPIP_CLOSED , uniqueId , ( LPARAM ) this ) ;
}


char const * Socket::GetData() const
{
	return recvBuf ;
}


int32_t const & Socket::GetUniqueId() const
{
	return uniqueId ;
}


void Socket::OnAccept( int32_t errorcode )
{
	pSocket = std::make_shared< Socket >() ;

	bool isAccepted = ( FALSE == Accept( * pSocket ) ) ? false : true ;

	CSocket::OnAccept( errorcode ) ;

	if( true == isAccepted )
	{
		pSocket->SetHWND( hwnd ) ;
		SendMessage( hwnd , WM_TCPIP_ACCEPTED , uniqueId , ( LPARAM ) pSocket.get() ) ;
	}
}


void Socket::SetHWND( HWND const & _hwnd )
{
	hwnd = _hwnd ;
}