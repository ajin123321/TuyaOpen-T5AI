if (CONFIG_AUDIO_AGC_TEST)

set (incs .)

set(srcs
	agc_demo.c
	)

endif()

armino_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" PRIV_REQUIRES bk_common)