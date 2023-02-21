Ted's almost written manual for libevent 
========================================

libevent, is an asychronous event loop library written in C that wraps access
to the notification mechanisms built into operating systems. It provides a
uniform API regardless of the underlying notification system. Notable programs
using the library are Chromium, memcached and tmux as well as others.

OpenBSD ships with libevent version 1.4.15 plus a patchset to maintain the
library and associated documentation. The upstream version is now at 2.1.12;
OpenBSD has not, nor plans to migrate to the newer library version. Although
there have been efforts to backport at least one newer feature to the older
library.

Internally OpenBSD bundled programs rely on libevent including:

|               |               |               |
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
* Support for signals
* Event Notification
* Timers and timeouts

### So, what shouldn't I use libevent for?

libevent is not ideal for a multi-threaded program. It's core competency
is the fork/exec event loop model of concurrency rather than threading,
although it does have some support for it.

### Tell me about problems with libevent

I was a lot more enthusiastic about this library prior to writing a lot of
documentation for it. The library mechanically is sound but I think that there
is a lot of short comings in the API design, as well a thorough lack of
rigorousness in things that are easy in theory, but tedious in practice to get
right.

For starters, on the unix like ecosystems, the established mechanic for a
library to report errors is the traditional errno value. This is woefully
underused in libevent. Some errors get reported through a callback mechanism
that was literally unmentioned in the original manual page, and only became
obvious after examination. Some of these errors will hard terminate programs
by calling exit(3), others will rely on assert, and others will just return -1
and hope that the calling program catches it.

Parameters are inconsistently checked for validity. I written an enourmous
amount of "behaviour is undefined if x is NULL" language into my manuals so
far.

The documentation in *event.h* is pathetic. Often wrong, usually useless.
It needs to be nuked from orbit, developers industry wide need to stop relying
on auto generated documentation tools to hold their hands and actually do the
hard technical work of answering:

- **What problem does this function solve**
- **How must a program call this function**
- **What happens if this function receives invalid input**
- **What happens if this function fails**
- **What does the function return**

I have tried sincerely to answer that question for everything I document here.

### Where do I start?

Programs using libevent need to link to the *-levent* library and include the
*event.h* header to access the API. The library entry point is *event_init* or
*event_base_new* for programs intending to run multiple event loops. Events
can be configured using *event_set* and then scheduled for execution with
*event_add*.  You can start executing your event_loop with *event_dispatch*
and you can exit from the event loop by calling *event_loopexit*.

### Ok so how do I use this library?

That's what this manual is here to answer. Just a note, this manual is for
libevent 1.4. If someone wants to throw a few thousand dollars at me to
do the same for libevent 2.x, I'll consider that too.

For now, grab a copy of mandoc, checkout this git repo to a local directory
and start perusing the manual by default:

`mandoc <manualfile> | less`

Once things have settled down I'll post static html versions of the manual
or maybe even markdown?

The first page you will want to read thoroughly is *event_base_new.3*. From
there, open up my examples and see if you can grok them. I would like to
write some tests for young players too to see if they can wrap their heads
around the API.

## Project Status
Here is a rough breakdown of the documentation project so far.


| Function                       | Pub | Manual                     | Done |
|--------------------------------|-----|----------------------------|------|
| event_base_new                 | Yes | event_base_new.3           | Yes  |
| event_init                     | Yes | event_base_new.3           | Yes  |
| event_reinit                   | Yes | event_base_new.3           | Yes  |
| event_base_free                | Yes | event_base_new.3           | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_set_log_callback         | Yes | event_set_log_callback.3   | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_base_loop                | Yes | event_base_loop.3          | Yes  |
| event_loop                     | Yes | event_base_loop.3          | Yes  |
| event_base_dispatch            | Yes | event_base_loop.3          | Yes  |
| event_dispatch                 | Yes | event_base_loop.3          | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_set                      | Yes | event_set.3                | Yes  |
| event_base_set                 | Yes | event_set.3                | Yes  |
| event_add                      | Yes | event_set.3                | Yes  |
| event_del                      | Yes | event_set.3                | Yes  |
| event_base_once                | Yes | event_set.3                | Yes  |
| event_once                     | Yes | event_set.3                | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_active                   | Yes | event_active.3             | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_pending                  | Yes | event_pending.3            | Yes  |
| event_initialized              | Yes | event_pending.3            | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_base_get_method          | Yes | event_base_get_method.3    | Yes  |
| event_get_method               | Yes | event_base_get_method.3    | Yes  |
| event_get_version              | Yes | event_base_get_method.3    | Yes  |
|--------------------------------|-----|----------------------------|------|
| event_err                      | No  |                            |      |
| event_errx                     | No  |                            |      |
| event_warn                     | No  |                            |      |
| event_warnx                    | No  |                            |      |
| event_msgx                     | No  |                            |      |
| \_event_debugx                 | No  |                            |      |
|--------------------------------|-----|----------------------------|------|
| evutil_getenv                  | No  |                            |      |
| evutil_make_socket_nonblocking | No  |                            |      |
| evutil_snprintf                | No  |                            |      |
| evutil_socketpair              | No  |                            |      |
| evutil_strtoll                 | No  |                            |      |
| evutil_vsnprintf               | No  |                            |      |
|--------------------------------|-----|----------------------------|------|
| signal_set                     | Yes | event_set.3                | Yes  |
| signal_add                     | Yes | event_set.3                | Yes  |
| signal_del                     | Yes | event_set.3                | Yes  |
| signal_pending                 | Yes | event_set.3                | Yes  |
| signal_initialized             | Yes | event_set.3                | Yes  |
|--------------------------------|-----|----------------------------|------|
| evtimer_set                    | Yes | event_set.3                | Yes  |
| evtimer_add                    | Yes | event_set.3                | Yes  |
| evtimer_del                    | Yes | event_set.3                | Yes  |
| evtimer_pending                | Yes | event_set.3                | Yes  |
| evtimer_initialized            | Yes | event_set.3                | Yes  |
|--------------------------------|-----|----------------------------|------|
| bufferevent_base_set           | Yes |                            | No   |
| bufferevent_disable            | Yes |                            | No   |
| bufferevent_enable             | Yes |                            | No   |
| bufferevent_free               | Yes |                            | No   |
| bufferevent_new                | Yes |                            | No   |
| bufferevent_priority_set       | Yes |                            | No   |
| bufferevent_read               | Yes |                            | No   |
| bufferevent_read_pressure_cb   | Yes |                            | No   |
| bufferevent_setcb              | Yes |                            | No   |
| bufferevent_setfd              | Yes |                            | No   |
| bufferevent_settimeout         | Yes |                            | No   |
| bufferevent_setwatermark       | Yes |                            | No   |
| bufferevent_write              | Yes |                            | No   |
| bufferevent_write_buffer       | Yes |                            | No   |
|--------------------------------|-----|----------------------------|------|
| encode_int                     | Yes |                            |      |
|--------------------------------|-----|----------------------------|------|
| evbuffer_add                   | Yes |                            | No   |
| evbuffer_add_buffer            | Yes |                            | No   |
| evbuffer_add_printf            | Yes |                            | No   |
| evbuffer_add_vprintf           | Yes |                            | No   |
| evbuffer_drain                 | Yes |                            | No   |
| evbuffer_expand                | Yes |                            | No   |
| evbuffer_find                  | Yes |                            | No   |
| evbuffer_free                  | Yes |                            | No   |
| evbuffer_new                   | Yes |                            | No   |
| evbuffer_read                  | Yes |                            | No   |
| evbuffer_readline              | Yes |                            | No   |
| evbuffer_readln                | Yes |                            | No   |
| evbuffer_remove                | Yes |                            | No   |
| evbuffer_setcb                 | Yes |                            | No   |
| evbuffer_write                 | Yes |                            | No   |
|--------------------------------|-----|----------------------------|------|
| event_asr_abort                | Yes |                            | No   |
| event_asr_run                  | Yes |                            | No   |
|--------------------------------|-----|----------------------------|------|
| event_base_loopbreak           | Yes |                            | No   |
| event_base_loopexit            | Yes |                            | No   |
| event_loopbreak                | Yes |                            | No   |
| event_loopexit                 | Yes |                            | No   |
|--------------------------------|-----|----------------------------|------|
| event_priority_init            | Yes | event_base_priority_init.3 | Yes  |
| event_priority_set             | Yes | event_base_priority_init.3 | Yes  |
| event_base_priority_init       | Yes | event_base_priority_init.3 | Yes  |
|--------------------------------|-----|----------------------------|------|
| evsignal_add                   | Yes |                            | No   |
| evsignal_dealloc               | Yes |                            | No   |
| evsignal_del                   | Yes |                            | No   |
| evsignal_init                  | Yes |                            | No   |
| evsignal_process               | Yes |                            | No   |
| \_evsignal_restore_handler     | Yes |                            | No   |
| \_evsignal_set_handler         | Yes |                            | No   |
|--------------------------------|-----|----------------------------|-------
| evtag_consume                  | Yes |                            | No   |
| evtag_decode_int               | Yes |                            | No   |
| evtag_decode_tag               | Yes |                            | No   |
| evtag_encode_tag               | Yes |                            | No   |
| evtag_init                     | Yes |                            | No   |
| evtag_marshal                  | Yes |                            | No   |
| evtag_marshal_int              | Yes |                            | No   |
| evtag_marshal_string           | Yes |                            | No   |
| evtag_marshal_timeval          | Yes |                            | No   |
| evtag_payload_length           | Yes |                            | No   |
| evtag_peek                     | Yes |                            | No   |
| evtag_peek_length              | Yes |                            | No   |
| evtag_unmarshal                | Yes |                            | No   |
| evtag_unmarshal_fixed          | Yes |                            | No   |
| evtag_unmarshal_int            | Yes |                            | No   |
| evtag_unmarshal_string         | Yes |                            | No   |
| evtag_unmarshal_timeval        | Yes |                            | No   |
|--------------------------------|-----|----------------------------|------|


