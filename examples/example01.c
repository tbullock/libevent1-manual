/*
 * Copyright (c) 2023 Ted Bullock <tbullock@comlore.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <event.h>
#include <stdio.h>
#include <stdlib.h>

static void	 cb(int, const char *);

/*
 * Example01
 * This program demonstrates how to use libevent to set up an event loop and
 * handle diagnostic messages. The cb() callback is used to handle diagnostic
 * messages, and the event_loopexit() function is used to schedule a timer to
 * terminate the event loop after a certain period of time.
 *
 * This example targets libevent-1.4 on OpenBSD.
 */
int
main(int argc, char *argv[])
{
	/* 5 second timeout to close the program */
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	/* Direct diagnostic messages to `cb` callback */
	event_set_log_callback(cb);

	/* Tell event_init to report the kernel notification method */
	setenv("EVENT_SHOW_METHOD", "", 1);
	
	/* Initialize library; failures won't return */
	event_init();

	/* Schedule a timer to terminate event loop after 5 seconds */
	event_loopexit(&tv);

	printf("Event Example 01: Quitting in 5 seconds\n");
	printf("libevent-%s (%s)\n", event_get_version(), event_get_method());
	/* Start the loop, this is equivalent to event_dispatch() */
	event_loop(0);
	printf("All done.\n");

	/* Deallocate memory */
	event_base_free(NULL);
	return 0;
}

/*
 * The cb() function is a callback function that is called by libevent to
 * handle diagnostic messages. The function takes two arguments: an integer
 * indicating the severity of the message and a string containing the message
 * text. The function switches on the severity to determine how to handle
 * the message, and in this case it simply prints the message to standard
 * output with an appropriate prefix.
 *
 * DEBUG messages require libevent to be compiled with USE_DEBUG.
 */
static void
cb(int sev, const char *msg)
{
	switch (sev) {
	case _EVENT_LOG_DEBUG:
		printf("DEBUG: %s\n", msg);
		break;
	case _EVENT_LOG_MSG:
		printf("INFO: %s\n", msg);
		break;
	case _EVENT_LOG_WARN:
		printf("WARNING: %s\n", msg);
		break;
	case _EVENT_LOG_ERR:
		printf("ERROR: %s\n", msg);
		break;
	}
}
