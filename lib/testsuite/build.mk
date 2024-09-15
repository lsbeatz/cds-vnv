lib-srcs += $(addprefix $(LIB_PATH)/testsuite/,	\
	testsuite.c									\
)

INCLUDES += -I$(LIB_PATH)/testsuite
