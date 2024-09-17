core-srcs += $(addprefix $(CORE_PATH)/queue/,	\
	queue.c										\
)

INCLUDES += -I$(CORE_PATH)/queue
