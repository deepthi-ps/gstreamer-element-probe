CC = gcc
GST_CFLAGS = `pkg-config --cflags --libs gstreamer-1.0`
EXTRA_CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -Wstrict-prototypes -Wmissing-prototypes -fvisibility=hidden -O2 -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed

all:
	$(CC) $(EXTRA_CFLAGS) gst-element-probe.c -o gst-element-probe $(GST_CFLAGS)

clean:
	rm gst-element-probe


