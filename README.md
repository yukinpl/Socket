# Socket
Socket on Windows 10. Written by C++

__pch.h__
```cpp
#include <afxsock.h>
```
&nbsp;&nbsp;    
__App::InitInstance()__
```cpp
if( !AfxSocketInit() )
{
    //Log( _T( "AfxSocketInit FAILED" ) , true ) ;
}
```

&nbsp;&nbsp;  

__Dlg.cpp__
```cpp
BEGIN_MESSAGE_MAP( Dlg , CDialogEx )
	ON_MESSAGE( WM_TCPIP_RECEIVED , & Dlg::OnTcpipReceive ) 
	ON_MESSAGE( WM_TCPIP_CLOSED   , & Dlg::OnSocketClose   )
END_MESSAGE_MAP()
```

```cpp
LRESULT Dlg::OnTcpipReceive( WPARAM len , LPARAM socket )
{
    uint32_t length = ( uint32_t ) len ;
    Socket * sock = ( Socket * ) socket ;

    char const * pDat = sock->GetData() ;
```

```cpp
LRESULT Dlg::OnSocketClose( WPARAM uniqueId , LPARAM socket )
{
	Socket * sock = ( Socket * ) socket ;
	sock->Close() ;
```
    
```cpp
if( FALSE == m_socket.Connect( ipStr , port ) )
{
    return ;
}
```
    
```cpp
if( false == m_socket.Send( sendMsg , msgPos ) )
{
```
 
