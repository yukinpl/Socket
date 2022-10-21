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
