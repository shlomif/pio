# Detect OS
ifeq ($(PLATFORM), Darwin)
CFLAGS += -Idns/ares/config_darwin 	
#LINKFLAGS+=-framework CoreServices
endif

ifeq ($(PLATFORM), Darwin)
CFLAGS += -Isrc/ares/config_linux	
#LINKFLAGS+=-lrt	
endif

CARES_OBJS =
CARES_OBJS += dns/ares/ares__close_sockets.o
CARES_OBJS += dns/ares/ares__get_hostent.o
CARES_OBJS += dns/ares/ares__read_line.o
CARES_OBJS += dns/ares/ares__timeval.o
CARES_OBJS += dns/ares/ares_cancel.o
CARES_OBJS += dns/ares/ares_data.o
CARES_OBJS += dns/ares/ares_destroy.o
CARES_OBJS += dns/ares/ares_expand_name.o
CARES_OBJS += dns/ares/ares_expand_string.o
CARES_OBJS += dns/ares/ares_fds.o
CARES_OBJS += dns/ares/ares_free_hostent.o
CARES_OBJS += dns/ares/ares_free_string.o
CARES_OBJS += dns/ares/ares_gethostbyaddr.o
CARES_OBJS += dns/ares/ares_gethostbyname.o
CARES_OBJS += dns/ares/ares_getnameinfo.o
CARES_OBJS += dns/ares/ares_getopt.o
CARES_OBJS += dns/ares/ares_getsock.o
CARES_OBJS += dns/ares/ares_init.o
CARES_OBJS += dns/ares/ares_library_init.o
CARES_OBJS += dns/ares/ares_llist.o
CARES_OBJS += dns/ares/ares_mkquery.o
CARES_OBJS += dns/ares/ares_nowarn.o
CARES_OBJS += dns/ares/ares_options.o
CARES_OBJS += dns/ares/ares_parse_a_reply.o
CARES_OBJS += dns/ares/ares_parse_aaaa_reply.o
CARES_OBJS += dns/ares/ares_parse_mx_reply.o
CARES_OBJS += dns/ares/ares_parse_ns_reply.o
CARES_OBJS += dns/ares/ares_parse_ptr_reply.o
CARES_OBJS += dns/ares/ares_parse_srv_reply.o
CARES_OBJS += dns/ares/ares_parse_txt_reply.o
CARES_OBJS += dns/ares/ares_process.o
CARES_OBJS += dns/ares/ares_query.o
CARES_OBJS += dns/ares/ares_search.o
CARES_OBJS += dns/ares/ares_send.o
CARES_OBJS += dns/ares/ares_strcasecmp.o
CARES_OBJS += dns/ares/ares_strdup.o
CARES_OBJS += dns/ares/ares_strerror.o
CARES_OBJS += dns/ares/ares_timeout.o
CARES_OBJS += dns/ares/ares_version.o
CARES_OBJS += dns/ares/ares_writev.o
CARES_OBJS += dns/ares/bitncmp.o
CARES_OBJS += dns/ares/inet_net_pton.o
CARES_OBJS += dns/ares/inet_ntop.o

