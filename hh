hadowp left redzone: byte legend (one shadow byte represents 8 application bytes):
ddressablep region:
heeeereeee =====> 10261541
tack left redzone:
tack mid redzone:
=================================================================
tack right redzone:
READ of size 4 at 0x0001142220f8 thread Tn draw_textured_line render_walls2.c:29
tack after return:
tack use after scope:
n render_frame raycasting2.c:54
18 in __CFRUNLOOP_IS_CALLING_OUT_TO_A_TIMER_CALLBACK_FUNCTION__+0x13 (CoreFoundation:x86_64h+0x9ea18)
n __CFRunLoopDoTimer+0x35a (CoreFoundation:x86_64h+0x9e57e)
n __CFRunLoopDoTimers+0x141 (CoreFoundation:x86_64h+0x9e066)
n __CFRunLoopRun+0x74e (CoreFoundation:x86_64h+0x82e29)
 CFRunLoopRunSpecific+00aac in RunCurrentEventLoopInMode+007c4 in ReceiveNextEventCommon+0x247 (0568 in _BlockUntilNextEventMatchingListInModeWithFilter+0x3f (HIToolbox:x86_64+0x2f568)
HIToolbox:x86_64+0x2f7c4)
123 (HIToolbox:x86_64+0x2faac)
1cd (CoreFoundation:x86_64h+0x8207d)
in _DPSNextEvent+0x372 (AppKit:x86_64+0x413c8)
f in -[NSApplication(NSEvent) _nextEventMatchingEventMask:untilDate:inMode:dequeue:]+0x547 (AppKit:x86_64+0x3fc0f)
n -[NSApplication run]+0x291 (AppKit:x86_64+0x3191d)
n mlx_loop+0x85 (cub3D:x86_64+0x1000065b5)
n main main.c:63
n start+0x0 (libdyld.dylib:x86_64+0x1acc8)

0x0001142220f8 is located 5896 bytes to the left of 7228704-byte region [0x000114223800,0x000114908520)
allocated by thread T0 here:
n wrap_malloc+0x9d (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x4917d)
f in mlx_new_image+0x8f (cub3D:x86_64+0x1000069af)
n mlx_int_parse_xpm+0x2ae (cub3D:x86_64+0x10000734e)
n mlx_xpm_file_to_image+0x9e (cub3D:x86_64+0x1000076ee)
85 in textures creating_win_tex.c:24
85 in textures creating_win_tex.c:24
85 in textures creating_win_tex.c:24
85 in textures creating_win_tex.c:24
85 in textures creating_win_tex.c:24
85 in textures creating_win_tex.c:24
n load_and_check_textures creating_win_tex.c:56
n main main.c:57
n start+0x0 (libdyld.dylib:x86_64+0x1acc8)

SUMMARY: AddressSanitizer: heap-buffer-overflow render_walls2.c:29 in draw_textured_line
Shadow bytes around the buggy address:
: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

bal redzone:
n render_column render_walls2.c:44
isoned by user:
ontainer overflow:rray cookie:c
ntra object lloca redzone:ight alloca 

==84454==ABORTING

==84454==ABORTING
zsh: aborttaai@e3r3p3 wolfepstein %

