LCD mcu 8080
==========================

:link_to_translation:`zh_CN:[中文]`

1 Overview
---------------------------------------
	demo of 8080 api usages.

2 Code Path
---------------------------------------
	The path of demos: ``\components\demos\media\lcd\lcd_8080\lcd_8080_demo.c``, 



3 Client command
---------------------------------------
The commands support by 8080 lcd

+-----------------------------------------+----------------------------------+
|lcd fill full color cmd                  |Description                       |
+=========================================+==================================+
|lcd_8080=dma2d_fill,0x60000000,0xf800    |fill addr 0x60000000 red          |
+-----------------------------------------+----------------------------------+
|lcd_8080=init,4                          |init lcd                          |
+-----------------------------------------+----------------------------------+
|lcd_8080=frame_disp,0x60000000           |start lcd display                 |
+-----------------------------------------+----------------------------------+

+------------------------------------------------------------+-----------------------------------------------------------+
|lcd fill partical color cmd                                 |Description                                                |
+============================================================+===========================================================+
|lcd_8080=init,4                                             |init lcd                                                   |
+------------------------------------------------------------+-----------------------------------------------------------+
|lcd_8080=lcd_fill_color,0x001f,10,10,200,200,0x60000000     |fill start coordinate(x,y) with (width,height) red color   |
+------------------------------------------------------------+-----------------------------------------------------------+


+------------------------------------------------------------+-----------------------------------------------------------+
|lcd fill partical data cmd                                  |Description                                                |
+============================================================+===========================================================+
|lcd_8080=init,4                                             |init lcd                                                   |
+------------------------------------------------------------+-----------------------------------------------------------+
|lcd_8080=10,10,200,200,0x60000000                           |fill start coordinate(x,y) with (width,height) data        |
+------------------------------------------------------------+-----------------------------------------------------------+

+-----------------------------------------+----------------------------------+
|lcd close                                |Description                       |
+=========================================+==================================+
|lcd_8080=close                           |close lcd                         |
+-----------------------------------------+----------------------------------+


The macro configuration that the demo runs depends on:

+--------------------------------------+------------------------+--------------------------------------------+---------+
|                 NAME                 |      Description       |                  File                      |  value  |
+======================================+========================+============================================+=========+
|CONFIG_LCD                            |lcd function enable     |``middleware\soc\bk7286\bk7286.defconfig``  |    y    |
+--------------------------------------+------------------------+--------------------------------------------+---------+
|CONFIG_LCD_TEST                       |DEMO enable             |``middleware\soc\bk7286\bk7286.defconfig``  |    y    |
+--------------------------------------+------------------------+--------------------------------------------+---------+
