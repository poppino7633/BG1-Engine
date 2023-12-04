let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
let Taboo_tabs = "2	Engine\n3	Mesh\n"
let NetrwMenuPriority =  80 
let NetrwTopLvlMenu = "Netrw."
silent only
silent tabonly
cd D:/Work/OpenGL\ stuff/BG1/Engine
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +15 CMakeLists.txt
badd +7 engine.cpp
badd +1 engine.h
badd +1 include/engine.h
badd +1 include/config.h
badd +1 include/config.h.in
badd +108 src/engine.cpp
badd +1 include/includes.h
badd +10 src/include/engine.h
badd +2 src/include/includes.h
badd +167 term://D:/Work/OpenGL\ stuff/BG1/Engine//24412:C:/Windows/system32/cmd.exe
badd +1 includes.h
badd +4 src/includes.h
badd +35 src/include/mesh.h
badd +14 src/mesh.cpp
badd +7 src/include/types.h
badd +1 src/include/ty
argglobal
%argdel
$argadd CMakeLists.txt
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit CMakeLists.txt
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 27 + 27) / 54)
exe 'vert 1resize ' . ((&columns * 59 + 104) / 209)
exe '2resize ' . ((&lines * 27 + 27) / 54)
exe 'vert 2resize ' . ((&columns * 89 + 104) / 209)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 15 - ((14 * winheight(0) + 13) / 27)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 15
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/includes.h", ":p")) | buffer src/includes.h | else | edit src/includes.h | endif
if &buftype ==# 'terminal'
  silent file src/includes.h
endif
balt includes.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 4 - ((3 * winheight(0) + 13) / 27)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 4
normal! 0
wincmd w
exe '1resize ' . ((&lines * 27 + 27) / 54)
exe 'vert 1resize ' . ((&columns * 59 + 104) / 209)
exe '2resize ' . ((&lines * 27 + 27) / 54)
exe 'vert 2resize ' . ((&columns * 89 + 104) / 209)
tabnext
edit src/include/engine.h
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 63 + 104) / 209)
exe 'vert 2resize ' . ((&columns * 145 + 104) / 209)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 38 - ((28 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 38
normal! 0
lcd D:/Work/OpenGL\ stuff/BG1/Engine
wincmd w
argglobal
if bufexists(fnamemodify("D:/Work/OpenGL\ stuff/BG1/Engine/src/engine.cpp", ":p")) | buffer D:/Work/OpenGL\ stuff/BG1/Engine/src/engine.cpp | else | edit D:/Work/OpenGL\ stuff/BG1/Engine/src/engine.cpp | endif
if &buftype ==# 'terminal'
  silent file D:/Work/OpenGL\ stuff/BG1/Engine/src/engine.cpp
endif
balt D:/Work/OpenGL\ stuff/BG1/Engine/engine.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 108 - ((42 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 108
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 63 + 104) / 209)
exe 'vert 2resize ' . ((&columns * 145 + 104) / 209)
tabnext
edit D:/Work/OpenGL\ stuff/BG1/Engine/src/include/mesh.h
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 123 + 104) / 209)
exe 'vert 2resize ' . ((&columns * 85 + 104) / 209)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 35 - ((26 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 35
normal! 02|
wincmd w
argglobal
if bufexists(fnamemodify("D:/Work/OpenGL\ stuff/BG1/Engine/src/mesh.cpp", ":p")) | buffer D:/Work/OpenGL\ stuff/BG1/Engine/src/mesh.cpp | else | edit D:/Work/OpenGL\ stuff/BG1/Engine/src/mesh.cpp | endif
if &buftype ==# 'terminal'
  silent file D:/Work/OpenGL\ stuff/BG1/Engine/src/mesh.cpp
endif
balt D:/Work/OpenGL\ stuff/BG1/Engine/src/include/mesh.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 14 - ((13 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 024|
wincmd w
exe 'vert 1resize ' . ((&columns * 123 + 104) / 209)
exe 'vert 2resize ' . ((&columns * 85 + 104) / 209)
tabnext 3
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
