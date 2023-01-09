Ted's almost written manual for libevent 
========================================

libevent, is an asychronous event loop library written in C that wraps access
to the notification mechanisms built into operating systems. It provides a
uniform API regardless of the underlying notification system. Notable programs
using the API are Google Chrome, memcached and tmux as well as others.

OpenBSD ships with libevent version 1.4.13 plus a patchset to maintain the
library and associated documentation. The upstream version is now at 2.1.12;
OpenBSD has not, nor plans to migrate to the newer library version.

Internally OpenBSD bundled programs rely on libevent including:

| Left columns  | Right columns |
| ------------- |:-------------:|
| ldap          | httpd         |
| snmpd         | identd        |
| dhcpleased    | ifstated      |
| iked          | inetd         |
| resolvd       | iscsid        |
| slaacd        | lpd           |
| unwind        | npppd         |
| cu            | nsd           |
| tmux          | ospf6d        |
| dvmrpd        | rad           |
| eigrpd        | radiusd       |
| ftp-proxy     | relayd        |
| hostapd       | ripd          |
| traceroute    | unbound       |
| vmd           |               |

Clearly with such robust usage, the library is core and important to the
operating system. This manual attempts to improve documentation for libevent.

### So, what's libevent good for?

Implenting the core event loop for your application, it's useful for writing 
portable programs that need to handle asynchronous nonblocking IO. The library
is handy for writing software that needs:

* Asynchronous IO
* Buffered IO
* Support for sockets
* Event Notification
* Timers and timeouts

### So, what shouldn't I use libevent for?

libevent is not inherently threadsafe, though it can be made to work by using
one _event_base_ instance per thread or by locked access to a shared
_event_base_ instance.

### Where do I start?

The library entry point is event_init or event_base_new