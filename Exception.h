#ifndef ERRNO_EX_H
#define ERRNO_EX_H

#include <errno.h>

class Exception {
public:
	const int code;
	Exception(int c = 0) : code(c) {}
	virtual const char *what() const = 0;
};

class Eunknown : public Exception {
public:
	const char * what() const throw() {
		return "Unknown error.";
	}
};

class E2big : public Exception {
public:
	E2big() : Exception(E2BIG) {}
	const char * what() const throw() {
		return "Argument list too long.";
	}
};

class Eacces : public Exception {
public:
	Eacces() : Exception(EACCES) {}
	const char * what() const throw() {
		return "Permission denied.";
	}
};

class Eaddrinuse : public Exception {
public:
	Eaddrinuse() : Exception(EADDRINUSE) {}
	const char * what() const throw() {
		return "Address in use.";
	}
};

class Eaddrnotavail : public Exception {
public:
	Eaddrnotavail() : Exception(EADDRNOTAVAIL) {}
	const char * what() const throw() {
		return "Address not available";
	}
};

class Eafnosupport : public Exception {
public:
	Eafnosupport() : Exception(EAFNOSUPPORT) {}
	const char * what() const throw() {
		return "Address family not supported.";
	}
};

class Eagain : public Exception {
public:
	Eagain() : Exception(EAGAIN) {}
	const char * what() const throw() {
		return "Resource unavailable, try again.";
	}
};

class Ealready : public Exception {
public:
	Ealready() : Exception(EALREADY) {}
	const char * what() const throw() {
		return "Connection already in progress.";
	}
};

class Ebadf : public Exception {
public:
	Ebadf() : Exception(EBADF) {}
	const char * what() const throw() {
		return "Bad file descriptor.";
	}
};

class Ebadmsg : public Exception {
public:
	Ebadmsg() : Exception(EBADMSG) {}
	const char * what() const throw() {
		return "Bad message.";
	}
};

class Ebusy : public Exception {
public:
	Ebusy() : Exception(EBUSY) {}
	const char * what() const throw() {
		return "Device or resource busy.";
	}
};

class Ecanceled : public Exception {
public:
	Ecanceled() : Exception(ECANCELED) {}
	const char * what() const throw() {
		return "Operation canceled.";
	}
};

class Echild : public Exception {
public:
	Echild() : Exception(ECHILD) {}
	const char * what() const throw() {
		return "No child processes.";
	}
};

class Econnaborted : public Exception {
public:
	Econnaborted() : Exception(ECONNABORTED) {}
	const char * what() const throw() {
		return "Connection aborted.";
	}
};

class Econnrefused : public Exception {
public:
	Econnrefused() : Exception(ECONNREFUSED) {}
	const char * what() const throw() {
		return "Connection refused.";
	}
};

class Econnreset : public Exception {
public:
	Econnreset() : Exception(ECONNRESET) {}
	const char * what() const throw() {
		return "Connection reset.";
	}
};

class Edeadlk : public Exception {
public:
	Edeadlk() : Exception(EDEADLK) {}
	const char * what() const throw() {
		return "Resource deadlock would occur.";
	}
};

class Edestaddrreq : public Exception {
public:
	Edestaddrreq() : Exception(EDESTADDRREQ) {}
	const char * what() const throw() {
		return "Destination address required.";
	}
};

class Edom : public Exception {
public:
	Edom() : Exception(EDOM) {}
	const char * what() const throw() {
		return "Mathematics argument out of domain of function.";
	}
};

class Eexist : public Exception {
public:
	Eexist() : Exception(EEXIST) {}
	const char * what() const throw() {
		return "File exists.";
	}
};

class Efault : public Exception {
public:
	Efault() : Exception(EFAULT) {}
	const char * what() const throw() {
		return "Bad address.";
	}
};

class Efbig : public Exception {
public:
	Efbig() : Exception(EFBIG) {}
	const char * what() const throw() {
		return "File too large.";
	}
};

class Ehostunreach : public Exception {
public:
	Ehostunreach() : Exception(EHOSTUNREACH) {}
	const char * what() const throw() {
		return "Host is unreachable.";
	}
};

class Eidrm : public Exception {
public:
	Eidrm() : Exception(EIDRM) {}
	const char * what() const throw() {
		return "Identifier removed.";
	}
};

class Eilseq : public Exception {
public:
	Eilseq() : Exception(EILSEQ) {}
	const char * what() const throw() {
		return "Illegal byte sequence.";
	}
};

class Einprogress : public Exception {
public:
	Einprogress() : Exception(EINPROGRESS) {}
	const char * what() const throw() {
		return "Operation in progress.";
	}
};

class Eintr : public Exception {
public:
	Eintr() : Exception(EINTR) {}
	const char * what() const throw() {
		return "Interrupted function.";
	}
};

class Einval : public Exception {
public:
	Einval() : Exception(EINVAL) {}
	const char * what() const throw() {
		return "Invalid argument.";
	}
};

class Eio : public Exception {
public:
	Eio() : Exception(EIO) {}
	const char * what() const throw() {
		return "I/O error.";
	}
};

class Eisconn : public Exception {
public:
	Eisconn() : Exception(EISCONN) {}
	const char * what() const throw() {
		return "Socket is connected.";
	}
};

class Eisdir : public Exception {
public:
	Eisdir() : Exception(EISDIR) {}
	const char * what() const throw() {
		return "Is a directory.";
	}
};

class Eloop : public Exception {
public:
	Eloop() : Exception(ELOOP) {}
	const char * what() const throw() {
		return "Too many levels of symbolic links.";
	}
};

class Emfile : public Exception {
public:
	Emfile() : Exception(EMFILE) {}
	const char * what() const throw() {
		return "Too many open files.";
	}
};

class Emlink : public Exception {
public:
	Emlink() : Exception(EMLINK) {}
	const char * what() const throw() {
		return "Too many links.";
	}
};

class Emsgsize : public Exception {
public:
	Emsgsize() : Exception(EMSGSIZE) {}
	const char * what() const throw() {
		return "Message too large.";
	}
};

class Enametoolong : public Exception {
public:
	Enametoolong() : Exception(ENAMETOOLONG) {}
	const char * what() const throw() {
		return "Filename too long.";
	}
};

class Enetdown : public Exception {
public:
	Enetdown() : Exception(ENETDOWN) {}
	const char * what() const throw() {
		return "Network is down.";
	}
};

class Enetreset : public Exception {
public:
	Enetreset() : Exception(ENETRESET) {}
	const char * what() const throw() {
		return "Connection aborted by network.";
	}
};

class Enetunreach : public Exception {
public:
	Enetunreach() : Exception(ENETUNREACH) {}
	const char * what() const throw() {
		return "Network unreachable.";
	}
};

class Enfile : public Exception {
public:
	Enfile() : Exception(ENFILE) {}
	const char * what() const throw() {
		return "Too many files open in system.";
	}
};

class Enobufs : public Exception {
public:
	Enobufs() : Exception(ENOBUFS) {}
	const char * what() const throw() {
		return "No buffer space available.";
	}
};

class Enodata : public Exception {
public:
	Enodata() : Exception(ENODATA) {}
	const char * what() const throw() {
		return "No data available.";
	}
};

class Enodev : public Exception {
public:
	Enodev() : Exception(ENODEV) {}
	const char * what() const throw() {
		return "No such device.";
	}
};

class Enoent : public Exception {
public:
	Enoent() : Exception(ENOENT) {}
	const char * what() const throw() {
		return "No such file or directory.";
	}
};

class Enoexec : public Exception {
public:
	Enoexec() : Exception(ENOEXEC) {}
	const char * what() const throw() {
		return "Executable file format error.";
	}
};

class Enolck : public Exception {
public:
	Enolck() : Exception(ENOLCK) {}
	const char * what() const throw() {
		return "No locks available.";
	}
};

class Enomem : public Exception {
public:
	Enomem() : Exception(ENOMEM) {}
	const char * what() const throw() {
		return "Not enough space.";
	}
};

class Enomsg : public Exception {
public:
	Enomsg() : Exception(ENOMSG) {}
	const char * what() const throw() {
		return "No message of the desired type.";
	}
};

class Enoprotoopt : public Exception {
public:
	Enoprotoopt() : Exception(ENOPROTOOPT) {}
	const char * what() const throw() {
		return "Protocol not available.";
	}
};

class Enospc : public Exception {
public:
	Enospc() : Exception(ENOSPC) {}
	const char * what() const throw() {
		return "No space left on device.";
	}
};

class Enosr : public Exception {
public:
	Enosr() : Exception(ENOSR) {}
	const char * what() const throw() {
		return "No STREAM resources.";
	}
};

class Enostr : public Exception {
public:
	Enostr() : Exception(ENOSTR) {}
	const char * what() const throw() {
		return "Not a STREAM.";
	}
};

class Enosys : public Exception {
public:
	Enosys() : Exception(ENOSYS) {}
	const char * what() const throw() {
		return "Function not supported.";
	}
};

class Enotconn : public Exception {
public:
	Enotconn() : Exception(ENOTCONN) {}
	const char * what() const throw() {
		return "The socket is not connected.";
	}
};

class Enotdir : public Exception {
public:
	Enotdir() : Exception(ENOTDIR) {}
	const char * what() const throw() {
		return "Not a directory.";
	}
};

class Enotempty : public Exception {
public:
	Enotempty() : Exception(ENOTEMPTY) {}
	const char * what() const throw() {
		return "Directory not empty.";
	}
};

class Enotsock : public Exception {
public:
	Enotsock() : Exception(ENOTSOCK) {}
	const char * what() const throw() {
		return "Not a socket.";
	}
};

class Enotsup : public Exception {
public:
	Enotsup() : Exception(ENOTSUP) {}
	const char * what() const throw() {
		return "Not supported.";
	}
};

class Enotty : public Exception {
public:
	Enotty() : Exception(ENOTTY) {}
	const char * what() const throw() {
		return "Inappropriate I/O control operation.";
	}
};

class Enxio : public Exception {
public:
	Enxio() : Exception(ENXIO) {}
	const char * what() const throw() {
		return "No such device or address.";
	}
};

class Eopnotsupp : public Exception {
public:
	Eopnotsupp() : Exception(EOPNOTSUPP) {}
	const char * what() const throw() {
		return "Operation not suported on socket.";
	}
};

class Eoverflow : public Exception {
public:
	Eoverflow() : Exception(EOVERFLOW) {}
	const char * what() const throw() {
		return "Value too large to be stored in data type.";
	}
};

class Eperm : public Exception {
public:
	Eperm() : Exception(EPERM) {}
	const char * what() const throw() {
		return "Operation not permitted.";
	}
};

class Epipe : public Exception {
public:
	Epipe() : Exception(EPIPE) {}
	const char * what() const throw() {
		return "Broken pipe.";
	}
};

class Eproto : public Exception {
public:
	Eproto() : Exception(EPROTO) {}
	const char * what() const throw() {
		return "Protocol error.";
	}
};

class Eprotonosupport : public Exception {
public:
	Eprotonosupport() : Exception(EPROTONOSUPPORT) {}
	const char * what() const throw() {
		return "Protocol not supported.";
	}
};

class Eprototype : public Exception {
public:
	Eprototype() : Exception(EPROTOTYPE) {}
	const char * what() const throw() {
		return "Protocol wrong type for socket.";
	}
};

class Erange : public Exception {
public:
	Erange() : Exception(ERANGE) {}
	const char * what() const throw() {
		return "Result too large.";
	}
};

class Erofs : public Exception {
public:
	Erofs() : Exception(EROFS) {}
	const char * what() const throw() {
		return "Read-only file system.";
	}
};

class Espipe : public Exception {
public:
	Espipe() : Exception(ESPIPE) {}
	const char * what() const throw() {
		return "Invalid seek.";
	}
};

class Esrch : public Exception {
public:
	Esrch() : Exception(ESRCH) {}
	const char * what() const throw() {
		return "No such process.";
	}
};

class Etime : public Exception {
public:
	Etime() : Exception(ETIME) {}
	const char * what() const throw() {
		return "Stream timeout.";
	}
};

class Etimedout : public Exception {
public:
	Etimedout() : Exception(ETIMEDOUT) {}
	const char * what() const throw() {
		return "Connection timed out.";
	}
};

class Etxtbsy : public Exception {
public:
	Etxtbsy() : Exception(ETXTBSY) {}
	const char * what() const throw() {
		return "Text file busy.";
	}
};

class Ewouldblock : public Exception {
public:
	Ewouldblock() : Exception(EWOULDBLOCK) {}
	const char * what() const throw() {
		return "Operation would block.";
	}
};

class Exdev : public Exception {
public:
	Exdev() : Exception(EXDEV) {}
	const char * what() const throw() {
		return "Cross-device link.";
	}
};

inline void throw_errno() {
	switch (errno) {
	case E2BIG: throw E2big();
	case EACCES: throw Eacces();
	case EADDRINUSE: throw Eaddrinuse();
	case EADDRNOTAVAIL: throw Eaddrnotavail();
	case EAFNOSUPPORT: throw Eafnosupport();
	case EAGAIN: throw Eagain();
	case EALREADY: throw Ealready();
	case EBADF: throw Ebadf();
	case EBADMSG: throw Ebadmsg();
	case EBUSY: throw Ebusy();
	case ECANCELED: throw Ecanceled();
	case ECHILD: throw Echild();
	case ECONNABORTED: throw Econnaborted();
	case ECONNREFUSED: throw Econnrefused();
	case ECONNRESET: throw Econnreset();
	case EDEADLK: throw Edeadlk();
	case EDESTADDRREQ: throw Edestaddrreq();
	case EDOM: throw Edom();
	case EEXIST: throw Eexist();
	case EFAULT: throw Efault();
	case EFBIG: throw Efbig();
	case EHOSTUNREACH: throw Ehostunreach();
	case EIDRM: throw Eidrm();
	case EILSEQ: throw Eilseq();
	case EINPROGRESS: throw Einprogress();
	case EINTR: throw Eintr();
	case EINVAL: throw Einval();
	case EIO: throw Eio();
	case EISCONN: throw Eisconn();
	case EISDIR: throw Eisdir();
	case ELOOP: throw Eloop();
	case EMFILE: throw Emfile();
	case EMLINK: throw Emlink();
	case EMSGSIZE: throw Emsgsize();
	case ENAMETOOLONG: throw Enametoolong();
	case ENETDOWN: throw Enetdown();
	case ENETRESET: throw Enetreset();
	case ENETUNREACH: throw Enetunreach();
	case ENFILE: throw Enfile();
	case ENOBUFS: throw Enobufs();
	case ENODATA: throw Enodata();
	case ENODEV: throw Enodev();
	case ENOENT: throw Enoent();
	case ENOEXEC: throw Enoexec();
	case ENOLCK: throw Enolck();
	case ENOMEM: throw Enomem();
	case ENOMSG: throw Enomsg();
	case ENOPROTOOPT: throw Enoprotoopt();
	case ENOSPC: throw Enospc();
	case ENOSR: throw Enosr();
	case ENOSTR: throw Enostr();
	case ENOSYS: throw Enosys();
	case ENOTCONN: throw Enotconn();
	case ENOTDIR: throw Enotdir();
	case ENOTEMPTY: throw Enotempty();
	case ENOTSOCK: throw Enotsock();
	case ENOTSUP: throw Enotsup();
	case ENOTTY: throw Enotty();
	//case ENOXIO: throw Enxio();
	//case EOPNOTSUPP: throw Eopnotsupp();
	case EOVERFLOW: throw Eoverflow();
	case EPERM: throw Eperm();
	case EPIPE: throw Epipe();
	case EPROTO: throw Eproto();
	case EPROTONOSUPPORT: throw Eprotonosupport();
	case EPROTOTYPE: throw Eprototype();
	case ERANGE: throw Erange();
	case EROFS: throw Erofs();
	case ESPIPE: throw Espipe();
	case ESRCH: throw Esrch();
	case ETIME: throw Etime();
	case ETIMEDOUT: throw Etimedout();
	case ETXTBSY: throw Etxtbsy();
	//case EWOULDBLOCK: throw EWOULDBLOCK();
	case EXDEV: throw Exdev();
	default: throw Eunknown();
	}
}
#endif
