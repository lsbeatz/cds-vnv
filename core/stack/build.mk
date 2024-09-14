core-srcs += $(addprefix $(CORE_PATH)/stack/,	\
	stack.c										\
)

INCLUDES += -I$(CORE_PATH)/stack
