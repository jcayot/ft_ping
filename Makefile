CC					:= cc
NAME                := ft_ping
CFLAGS              := -Wextra -Wall -Werror

HEADERS             := -I ./include

SRCS_DIR            := srcs
SRCS                := $(SRCS_DIR)/ft_ping.c \
						$(SRCS_DIR)/parse_args.c \
						$(SRCS_DIR)/help_ft_ping.c \
						$(SRCS_DIR)/ping_addr.c \
						$(SRCS_DIR)/calculate_checksum.c \
						$(SRCS_DIR)/ping_stats.c \
						$(SRCS_DIR)/ping_error.c \
						$(SRCS_DIR)/icmp_packet.c \
						$(SRCS_DIR)/strict_atoi.c \
						$(SRCS_DIR)/get_mst.c \
						$(SRCS_DIR)/play_alert_sound.c

BUILD_PATH          := build
OBJS                := $(patsubst %.c,$(BUILD_PATH)/%.o,$(SRCS))

all: $(BUILD_PATH) $(NAME)

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH) $(dir $(OBJS))

$(BUILD_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(BUILD_PATH)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re
