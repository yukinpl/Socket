#include "pch.h"
#include "Socket.h"

Socket::Socket()
	: isConnected( false ) , isCreated( false ) 
{
	//CSocket::CSocket() ;
}


bool Socket::Create( HWND const & hwnd )
{
	isCreated =
		( FALSE == CSocket::Create( 0 , SOCK_STREAM , nullptr ) ) ? false : true ;

	this->hwnd = hwnd ;

	return isCreated ;
}


bool Socket::Connect( CString const & ipStr , int32_t const & port )
{
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
	isConnected = false ;

	CSocket::Close() ;
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
	Receive( buf , MaxBufferSize ) ;

	uint32_t pos = 0 ;
	while( 0x7F != buf[ pos ] && pos < MaxBufferSize )
	{
		++pos ;
	}

	if( pos >= MaxBufferSize )
	{
		return ;
	}

	uint32_t len = pos + 1 ;

	memcpy( recvBuf , buf , len ) ;
	SendMessage( hwnd , WM_TCPIP_RECEIVED , len , ( LPARAM ) this ) ;
}


char const * Socket::GetData() const
{
	return recvBuf ;
}
