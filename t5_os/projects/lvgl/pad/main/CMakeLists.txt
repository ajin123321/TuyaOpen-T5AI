set(incs
	.
	./common
	./fonts
	./images
	./screens)

set(srcs
	pad_main.c
)

if (CONFIG_LV_USE_DEMO_86BOX)
list(APPEND srcs
	ui.c
	page_load_ctrol.c
	common/ui_helpers.c
	fonts/ui_font_OppoSanMid96.c
	fonts/ui_font_Number.c
	fonts/ui_font_OppoCN24.c
	fonts/ui_font_PingFangCN32.c
	images/ui_img_air_page_png.c
	images/ui_img_anime_lin2_png.c
	images/ui_img_anime_line1_png.c
	images/ui_img_arrow1_png.c
	images/ui_img_bg_img_png.c
	images/ui_img_cloud1_png.c
	images/ui_img_cold_symbol_png.c
	images/ui_img_common_switch1_png.c
	images/ui_img_curtain_off_png.c
	images/ui_img_curtain_on_png.c
	images/ui_img_curtain_page_png.c
	images/ui_img_curtain_stop_png.c
	images/ui_img_display_symbol_png.c
	images/ui_img_fan_symbol_png.c
	images/ui_img_first_page_png.c
	images/ui_img_info_symbol_png.c
	images/ui_img_light_page_png.c
	images/ui_img_light_symbol_off_png.c
	images/ui_img_light_symbol_on_png.c
	images/ui_img_mode_page_png.c
	images/ui_img_set_page_png.c
	images/ui_img_sun_png.c
	images/ui_img_switch_symbol_png.c
	images/ui_img_updata_symbol_png.c
	images/ui_img_voice_symbol_png.c
	images/ui_img_wifi_symbol_png.c
	images/ui_img_kongtiao_bg_png.c
	screens/ui_UiArcPage.c
	screens/ui_UiPage1.c
	screens/ui_UiPage2.c
	screens/ui_UiPage3.c
	screens/ui_UiPage4.c
	screens/ui_UiPage5.c
	screens/ui_UiPage6.c
)
endif()

if (CONFIG_OVERRIDE_FLASH_PARTITION)
    list(APPEND srcs
        vendor_flash.c
    )
endif()

if(CONFIG_SYS_CPU0 AND CONFIG_BT)
    list(APPEND incs
        a2dp_source
    )

    list(APPEND srcs
        a2dp_source/ring_buffer_particle.c
        a2dp_source/a2dp_source_demo.c
        a2dp_source/a2dp_source_demo_cli.c
        a2dp_source/a2dp_source_demo_avrcp.c
    )
endif()

armino_component_register(
	SRCS "${srcs}"
	INCLUDE_DIRS "${incs}"
	#REQUIRES
	PRIV_REQUIRES media bk_init bk_cli lvgl bk_bluetooth media_service
)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-variable -O3)
