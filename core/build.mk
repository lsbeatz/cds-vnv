ifeq ($(TEST_SUITE), stack)
	-include $(CORE_PATH)/stack/build.mk
endif

ifeq ($(TEST_SUITE), queue)
	-include $(CORE_PATH)/queue/build.mk
endif
