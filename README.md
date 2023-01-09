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

|               |               |              |
|---------------|---------------|---------------|
| ldap          | httpd         | relayd        |
| snmpd         | identd        | vmd           |
| dhcpleased    | ifstated      | ripd          |
| iked          | inetd         | unbound       |
| resolvd       | iscsid        | traceroute    |
| slaacd        | lpd           | hostapd       |
| unwind        | npppd         | ftp-proxy     |
| cu            | nsd           | radiusd       |
| tmux          | ospf6d        | eigrpd        |
| dvmrpd        | rad           |               |

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

Programs using libevent need to link to the *-levent* library and include the
*event.h* header to access the API. The library entry point is *event_init* or
*event_base_new* for programs intending to run multiple event loops. Events
can be configured using *event_set* and then scheduled for execution with
*event_add*.  You can start executing your event_loop with *event_dispatch*
and you can exit from the event loop by calling *event_loopexit*.

### Ok so how do I use this library?

That's what this manual is here to answer. Todo is colour by numbers all of
the various man pages and write out some further documentation.