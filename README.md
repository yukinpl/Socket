# Socket
Socket on Windows 10. Written by C++

pch.h
```cpp
#include <afxsock.h>
```
    
App::InitInstance()
```cpp
if( !AfxSocketInit() )
{
    //Log( _T( "AfxSocketInit FAILED" ) , true ) ;
}
```
  
```cpp
BEGIN_MESSAGE_MAP( CAmpDlg , CDialogEx )
	ON_MESSAGE( WM_TCPIP_RECEIVED , & CAmpDlg::OnTcpipReceive ) 
END_MESSAGE_MAP()
```

```cpp
if( FALSE == m_socket.Connect( ipStr , port ) )
{
    //Log( _T( "Fail to connect on " + ipStr + ":" + portStr ) , true ) ;
    return ;
}
```
