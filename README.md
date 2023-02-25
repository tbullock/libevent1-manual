Ted's almost written manual for libevent 
========================================

The libevent documentation shipping with OpenBSD is unusable.

This project works to provide an mdoc manual for the library, and submit it
to the OpenBSD devs for review.

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


# Worktable

This table charts the progress of the project from exported library symbols.
It includes reviews, OKs and what remains to be done. If a function has been
assigned to a manual.3 file, that means it's been documented.

The rest of the columns follow this legend:

*LEGEND:*
```
Pub: Yes; continue to export this function
     No; this should not be exported

Done: Yes; Reviewers signed off, it's ready for commit
      No; Work still to do

Ingo/Jason/Nick:  OK; typical ready to commit
                  NW; Needs work, refer to email chain and note
                  RA; Significant changes made, review again

Ted: TTD; has internal list of things to adjust
     RDY; review this for being committed
```

| Function                       | Pub | Manual                     | Done | Ingo | Jason | Nick | Ted | Notes                                   |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_base_new                 | Yes | event_base_new.3           | No   |      | OK    | Ok   | TTD | Don't document DEBUG messages           |
| event_init                     | Yes | event_base_new.3           | No   |      | OK    | Ok   | TTD |                                         |
| event_reinit                   | Yes | event_base_new.3           | No   |      | OK    | Ok   | TTD |                                         |
| event_base_free                | Yes | event_base_new.3           | No   |      | OK    | Ok   | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_set_log_callback         | Yes | event_set_log_callback.3   | No   |      | OK    | OK   | RDY |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_base_loop                | Yes | event_base_loop.3          | No   |      |       |      | TTD | Rewrite History                         |
| event_loop                     | Yes | event_base_loop.3          | No   |      |       |      | TTD |                                         |
| event_base_dispatch            | Yes | event_base_loop.3          | No   |      |       |      | TTD |                                         |
| event_dispatch                 | Yes | event_base_loop.3          | No   |      |       |      | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_set                      | Yes | event_set.3                | No   |      | OK    | OK   | TTD | Rewrite History                         |
| event_base_set                 | Yes | event_set.3                | No   |      | OK    | OK   | TTD |                                         |
| event_add                      | Yes | event_set.3                | No   |      | OK    | OK   | TTD |                                         |
| event_del                      | Yes | event_set.3                | No   |      | OK    | OK   | TTD |                                         |
| event_base_once                | Yes | event_set.3                | No   |      | OK    | OK   | TTD |                                         |
| event_once                     | Yes | event_set.3                | No   |      | OK    | OK   | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_active                   | Yes | event_active.3             | No   |      |       |      | TTD | Rewrite History                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_pending                  | Yes | event_pending.3            | No   |      |       |      | TTD | Rewrite History                         |
| event_initialized              | Yes | event_pending.3            | No   |      |       |      | TTD | Rewrite History                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_base_get_method          | Yes | event_base_get_method.3    | No   |      |       |      | TTD | Rewrite History                         |
| event_get_method               | Yes | event_base_get_method.3    | No   |      |       |      | TTD |                                         |
| event_get_version              | Yes | event_base_get_method.3    | No   |      |       |      | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_err                      | No  |                            |      |      |       |      |     |                                         |
| event_errx                     | No  |                            |      |      |       |      |     |                                         |
| event_warn                     | No  |                            |      |      |       |      |     |                                         |
| event_warnx                    | No  |                            |      |      |       |      |     |                                         |
| event_msgx                     | No  |                            |      |      |       |      |     |                                         |
| \_event_debugx                 | No  |                            |      |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| evutil_getenv                  | No  |                            |      |      |       |      |     |                                         |
| evutil_make_socket_nonblocking | No  |                            |      |      |       |      |     |                                         |
| evutil_snprintf                | No  |                            |      |      |       |      |     |                                         |
| evutil_socketpair              | No  |                            |      |      |       |      |     |                                         |
| evutil_strtoll                 | No  |                            |      |      |       |      |     |                                         |
| evutil_vsnprintf               | No  |                            |      |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| signal_set                     | Yes | event_set.3                | No   |      |       |      | TTD |                                         |
| signal_add                     | Yes | event_set.3                | No   |      |       |      | TTD |                                         |
| signal_del                     | Yes | event_set.3                | No   |      |       |      | TTD |                                         |
| signal_pending                 | Yes | event_pending.3            | No   |      |       |      | TTD |                                         |
| signal_initialized             | Yes | event_pending.3            | No   |      |       |      | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| evtimer_set                    | Yes | event_set.3                | No   |      |       |      | TTD |                                         |
| evtimer_add                    | Yes | event_set.3                | No   |      |       |      | TTD |                                         |
| evtimer_del                    | Yes | event_set.3                | No   |      |       |      | TTD |                                         |
| evtimer_pending                | Yes | event_pending.3            | No   |      |       |      | TTD |                                         |
| evtimer_initialized            | Yes | event_pending.3            | No   |      |       |      | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| bufferevent_base_set           | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_disable            | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_enable             | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_free               | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_new                | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_priority_set       | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_read               | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_read_pressure_cb   | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_setcb              | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_setfd              | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_settimeout         | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_setwatermark       | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_write              | Yes |                            | No   |      |       |      |     |                                         |
| bufferevent_write_buffer       | Yes |                            | No   |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| encode_int                     | Yes |                            |      |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| evbuffer_add                   | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_add_buffer            | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_add_printf            | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_add_vprintf           | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_drain                 | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_expand                | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_find                  | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_free                  | Yes | evbuffer_new.3             | No   |      |       |      | TTD |                                         |
| evbuffer_new                   | Yes | evbuffer_new.3             | No   |      |       |      | TTD |  Rewrite History                        |
| evbuffer_read                  | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_readline              | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_readln                | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_remove                | Yes |                            | No   |      |       |      |     |                                         |
| evbuffer_setcb                 | Yes | evbuffer_new.3             | No   |      |       |      | TTD |                                         |
| evbuffer_write                 | Yes |                            | No   |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_asr_abort                | Yes |                            | No   |      |       |      |     |                                         |
| event_asr_run                  | Yes |                            | No   |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_base_loopbreak           | Yes | event_base_loopbreak.3     | No   |      |       |      | TTD | Rewrite History                         |
| event_base_loopexit            | Yes | event_base_loopbreak.3     | No   |      |       |      | TTD |                                         |
| event_loopbreak                | Yes | event_base_loopbreak.3     | No   |      |       |      | TTD |                                         |
| event_loopexit                 | Yes | event_base_loopbreak.3     | No   |      |       |      | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| event_priority_init            | Yes | event_base_priority_init.3 | No   |      |       |      | TTD | Rewrite History                         |
| event_priority_set             | Yes | event_base_priority_init.3 | No   |      |       |      | TTD |                                         |
| event_base_priority_init       | Yes | event_base_priority_init.3 | No   |      |       |      | TTD |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| evsignal_add                   | Yes |                            | No   |      |       |      |     |                                         |
| evsignal_dealloc               | Yes |                            | No   |      |       |      |     |                                         |
| evsignal_del                   | Yes |                            | No   |      |       |      |     |                                         |
| evsignal_init                  | Yes |                            | No   |      |       |      |     |                                         |
| evsignal_process               | Yes |                            | No   |      |       |      |     |                                         |
| \_evsignal_restore_handler     | Yes |                            | No   |      |       |      |     |                                         |
| \_evsignal_set_handler         | Yes |                            | No   |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|
| evtag_consume                  | Yes |                            | No   |      |       |      |     |                                         |
| evtag_decode_int               | Yes |                            | No   |      |       |      |     |                                         |
| evtag_decode_tag               | Yes |                            | No   |      |       |      |     |                                         |
| evtag_encode_tag               | Yes |                            | No   |      |       |      |     |                                         |
| evtag_init                     | Yes |                            | No   |      |       |      |     |                                         |
| evtag_marshal                  | Yes |                            | No   |      |       |      |     |                                         |
| evtag_marshal_int              | Yes |                            | No   |      |       |      |     |                                         |
| evtag_marshal_string           | Yes |                            | No   |      |       |      |     |                                         |
| evtag_marshal_timeval          | Yes |                            | No   |      |       |      |     |                                         |
| evtag_payload_length           | Yes |                            | No   |      |       |      |     |                                         |
| evtag_peek                     | Yes |                            | No   |      |       |      |     |                                         |
| evtag_peek_length              | Yes |                            | No   |      |       |      |     |                                         |
| evtag_unmarshal                | Yes |                            | No   |      |       |      |     |                                         |
| evtag_unmarshal_fixed          | Yes |                            | No   |      |       |      |     |                                         |
| evtag_unmarshal_int            | Yes |                            | No   |      |       |      |     |                                         |
| evtag_unmarshal_string         | Yes |                            | No   |      |       |      |     |                                         |
| evtag_unmarshal_timeval        | Yes |                            | No   |      |       |      |     |                                         |
|--------------------------------|-----|----------------------------|------|------|-------|------|-----|-----------------------------------------|

