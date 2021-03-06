if( CMAKE_SYSTEM_NAME MATCHES "Linux" )
	set( LINUX TRUE )
	add_definitions( -D_POSIX_C_SOURCE=200809L -D_SVID_SOURCE )
endif( CMAKE_SYSTEM_NAME MATCHES "Linux" )

if( CMAKE_SYSTEM_NAME MATCHES "FreeBSD" )
	set( FREEBSD TRUE )
	set( BSD TRUE )
endif( CMAKE_SYSTEM_NAME MATCHES "FreeBSD" )

if( CMAKE_SYSTEM_NAME MATCHES "OpenBSD" )
	set( OPENBSD TRUE )
	set( BSD TRUE )
endif( CMAKE_SYSTEM_NAME MATCHES "OpenBSD" )

if (CMAKE_SYSTEM_NAME MATCHES "NetBSD" )
	set( NETBSD TRUE )
	set( BSD TRUE )
endif( CMAKE_SYSTEM_NAME MATCHES "NetBSD" )

if( CMAKE_SYSTEM_NAME MATCHES "(Solaris|SunOS)" )
	set( SOLARIS TRUE )
	add_definitions( -D_POSIX_C_SOURCE=200809L -D_SVID_SOURCE )
	add_definitions( -D__EXTENSIONS__ )
endif( CMAKE_SYSTEM_NAME MATCHES "(Solaris|SunOS)" )

if( APPLE )
	check_library_exists( intl gettext "" HAVE_LIBINTL )
endif( APPLE )
