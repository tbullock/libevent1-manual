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

#include <sys/socket.h>
#include <event.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	 logcb(int, const char *);
static void	 eventcb(int, short, void *);

/*
 * Example02
 *
 * This example targets libevent-1.4 on OpenBSD.
 *
 * The program creates a pair of connected sockets and uses them to
 * communicate between a parent and a child process. After initializing the
 * libevent library, the program forks to create a child process, and each
 * process writes a message to its corresponding socket, which the other
 * process will read. The parent and child processes both set up an event
 * listener for the socket they will read from and wait for the other process
 * to write its message. When a message is received, the eventcb function is
 * called, which prints the message to the console
 */
int
main(int argc, char *argv[])
{
	int			 p[2];
	pid_t			 pid;
	const char 		*message;
	int			 len;
	struct event		*e;
	struct event_base	*base;

	/* Direct diagnostic messages to `cb` callback. */
	event_set_log_callback(logcb);

	/* Tell event_init to report the kernel notification method. */
	setenv("EVENT_SHOW_METHOD", "", 1);
	
	/* Initialize library; failures won't return. */
	base = event_init();

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, p) == -1) {
		perror("socketpair");
		return 1;
	}
	if ((e = calloc(1, sizeof(struct event))) == NULL) {
		perror("calloc");
		return 1;
	}

	printf("Event Example 02: Talking between a parent and its child.\n");
	printf("libevent-%s (%s)\n", event_get_version(), event_get_method());

	pid = fork();
	if (pid == -1) {
		perror("fork");
		return 1;
	} else if (pid == 0) { /* Child Process */
		/* The child will be reading from fd 1 */
		close(p[0]);
		event_set(e, p[1], EV_READ, eventcb, &pid);

		/* We forked so reinit is necessary in the child process */
		event_reinit(base);

		/* Send a message to the child */
		message = "Hello parent!";
		len = write(p[1], message, strlen(message));
	} else {               /* Parent Process */
		/* The parent will be reading and writing to fd 0 */
		close(p[1]);
		event_set(e, p[0], EV_READ, eventcb, &pid);

		/* Send a message to the child */
		message = "Hello child!";
		len = write(p[0], message, strlen(message));
	}
	if (len == -1)
		perror("write");

	/*
	 * From this point on the remainder of the program logic is identical
	 * between the parent and the child programs. The differences are
	 * handled in the event callbacks we already set.
	 */

	/* Tell the event loop to monitor our events; there is no timeout. */
	event_add(e, NULL);

	/* Start the loop, this is equivalent to event_dispatch(). */
	if (event_loop(0) == -1)
		printf("PID:%d had a problem in event_loop()\n", pid);

	printf("All done.\n");

	/* Deallocate memory */
	event_del(e);
	event_base_free(NULL);
	return 0;
}

/*
 * The logcb() function is a callback function that is called by libevent to
 * handle diagnostic messages. The function takes two arguments: an integer
 * indicating the severity of the message and a string containing the message
 * text. The function switches on the severity to determine how to handle
 * the message, and in this case it simply prints the message to standard
 * output with an appropriate prefix.
 *
 * DEBUG messages require libevent to be compiled with USE_DEBUG.
 */
static void
logcb(int sev, const char *msg)
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

/*
 * The eventcb() function is a callback function that is executed when either
 * the parent or the child process has received a message from their partner.
 * The callback takes three arguments: an integer file descriptor, a short
 * integer comprised of event flags, in this case we are expecting EV_READ
 * and void pointer representing data provided by the call to event_set().
 *
 * This function determines whether the process is the parent or the child
 * and prints the corresponding message.
 */
static void
eventcb(int fd, short events, void *arg)
{
	int		 len;
	int		 pid;
	const char	*msg;

	pid = *(int*)arg;
	if (pid == 0)
		msg = "Parent received message: %s\n";
	else
		msg = "Child received message: %s\n";

	if (events & EV_READ) {
		/* Read what the other process said */
		char buf[1024];
		len = read(fd, buf, sizeof(buf) - 1);
		if (len > 0) {
			buf[len] = '\0';
			printf(msg, buf);
		} else if (len == -1) {
			perror("read");
		}
	}
}
