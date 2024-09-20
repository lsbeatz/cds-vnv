ifeq ($(TEST_SUITE), stack)
	-include $(TESTS_PATH)/stack/build.mk
endif

ifeq ($(TEST_SUITE), queue)
	-include $(TESTS_PATH)/queue/build.mk
endif
