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

Refer to the file worktable for a breakdown of project status.
