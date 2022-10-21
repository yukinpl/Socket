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
  
```cpp
BEGIN_MESSAGE_MAP( Dlg , CDialogEx )
	ON_MESSAGE( WM_TCPIP_RECEIVED , & Dlg::OnTcpipReceive ) 
END_MESSAGE_MAP()
```
&nbsp;&nbsp;  

__Dlg.cpp__
```cpp
if( FALSE == m_socket.Connect( ipStr , port ) )
{
    //Log( _T( "Fail to connect on " + ipStr + ":" + portStr ) , true ) ;
    return ;
}
```
  
```cpp
LRESULT Dlg::OnTcpipReceive( WPARAM len , LPARAM socket )
{
    uint32_t length = ( uint32_t ) len ;
    Socket * sock = ( Socket * ) socket ;

    char const * pDat = sock->GetData() ;
```
    
```cpp
if( false == m_socket.Send( sendMsg , msgPos ) )
{
```
